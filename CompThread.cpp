#include "CompThread.h"
#include "arvore_abstrata.h"

extern int yyparse(NBloco * bloco);
extern void yyrestart( FILE *file );
extern bool erro_compilador;
extern bool erro_lexico;
extern int yylineno;

CompThread::CompThread(QObject *parent) :
    QThread(parent), texto("")
{
}

void CompThread::run()
{

    FILE *file = fopen(CompInfo::inst()->arquivo.toLocal8Bit().constData(), "r");

    if (!file)
    {
        emit mensagem(tr("[CAFEZINHO] Não foi possivel abrir o arquivo!\n"));
        return;
    }

    yyrestart(file);

    yylineno = 1;
    erro_compilador = 0;
    erro_lexico = 0;

    CompInfo::setOut(this);

    NBloco *bloco;
    do
    {
        bloco = new NBloco(0);
        yyparse(bloco);
    } while (!feof(file));

    if(!erro_compilador)
    {
        TabelaSimbolo tabela;
        analise_semantica(tabela, bloco, 0, 0);
    }

    if(!erro_compilador)
        *this<<"[CAFEZINHO] Compilado com sucesso!\n";

    delete bloco;

    fclose(file);
}

void CompThread::appendMsg(QString msg)
{
    texto += msg;
    if(texto[texto.size()-1]=='\n')
    {
        emit mensagem("<b><span style=\"color:#B40404;\">"+texto+"</span><b/>");
        texto = "";
    }
}

CompThread &operator<<(CompThread &out, const int text)
{
    out.appendMsg(QString::number(text));
    return out;
}

CompThread &operator<<(CompThread &out, const char *text)
{
    out.appendMsg(QString(text));
    return out;
}

CompThread &operator<<(CompThread &out, const QString *text)
{
    out.appendMsg(*text);
    return out;
}

CompThread &operator<<(CompThread& out, const QString text)
{
    out.appendMsg(text);
    return out;
}
