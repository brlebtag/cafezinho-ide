#include "CompInfo.h"
#include "CompThread.h"

CompInfo* CompInfo::cmpInfo = NULL;

CompInfo *CompInfo::inst()
{
    if(cmpInfo==NULL)
        cmpInfo = new CompInfo();
    return cmpInfo;
}

Output &CompInfo::out()
{
    return (*CompInfo::inst()->_out);
}

Error &CompInfo::err()
{
    return (*CompInfo::inst()->_err);
}

void CompInfo::setOut(CompThread* thread)
{
    CompInfo::inst()->thread = thread;
}

void CompInfo::modoEntrada()
{
    CompInfo::inst()->thread->modoEntrada();
}

void CompInfo::appendTexto(QString texto)
{
    CompInfo::inst()->thread->appendMsg(texto);
}

CompInfo::CompInfo(QObject *parent) :
    QObject(parent), _out(new Output()),_err(new Error())
{

}

CompInfo::~CompInfo()
{
    delete _err;
    delete _out;
}


Output::Output()
{
}

void Output::setTexto(QString texto)
{
    CompInfo::inst()->thread->appendTexto(texto);
}

Output &operator<<(Output &out, double text)
{
    out.setTexto(QString::number(text));
    return out;
}

Output &operator<<(Output &out, char text)
{
    out.setTexto(QString(text));
    return out;
}

Output &operator<<(Output &out, const char *text)
{
    out.setTexto(QString(text));
    return out;
}

Output &operator<<(Output &out, const int text)
{
    out.setTexto(QString::number(text));
    return out;
}

Output &operator<<(Output &out, const QString *text)
{
    out.setTexto(*text);
    return out;
}

Output &operator<<(Output &out, const QString text)
{
    out.setTexto(text);
    return out;
}


Error::Error()
    : texto("")
{
}

void Error::appendTexto(QString texto)
{
    this->texto += texto;
}

void Error::appendTexto(const char *texto)
{
    this->texto += texto;
}

QString &Error::getTexto()
{
    return this->texto;
}

bool Error::isFimLinha()
{
    return this->texto[this->texto.size()-1]=='\n';
}

void Error::limpar()
{
    this->texto = "";
}

void Error::descarga(QString &texto)
{
    CompInfo::inst()->thread->appendMsg("<b><span style=\"color:#B40404;\">"+texto+"</span><b/>");
}

Error &operator<<(Error &err, const char *text)
{
    err.appendTexto(text);
    if(err.isFimLinha())
    {
        err.descarga(err.getTexto());
        err.limpar();
    }
    return err;
}

Error &operator<<(Error &err, const int text)
{
    err.appendTexto(QString::number(text));
    if(err.isFimLinha())
    {
        err.descarga(err.getTexto());
        err.limpar();
    }
    return err;
}

Error &operator<<(Error &err, const QString *text)
{
    err.appendTexto(*text);
    if(err.isFimLinha())
    {
        err.descarga(err.getTexto());
        err.limpar();
    }
    return err;
}

Error &operator<<(Error &err, const QString text)
{
    err.appendTexto(text);
    if(err.isFimLinha())
    {
        err.descarga(err.getTexto());
        err.limpar();
    }
    return err;
}
