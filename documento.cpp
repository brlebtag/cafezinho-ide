#include "documento.h"

Documento::Documento(QWidget *widget, CodeEditor *edit, bool dirty)
    :widget(widget), edit(edit), sujo(dirty)
{
    aberto = false;
}

bool Documento::isVazio()
{
    return this->edit->toPlainText().isEmpty();
}

bool Documento::isSujo()
{
    return this->sujo;
}

bool Documento::isAberto()
{
    return this->aberto;
}

void Documento::sujou()
{
    this->sujo = true;
}

void Documento::limpou()
{
    this->sujo = false;
}

void Documento::abriu()
{
    this->aberto = true;
}

void Documento::fechou()
{
    this->aberto = false;
}

QString Documento::getTextoDocumento()
{
    return this->edit->toPlainText();
}

void Documento::setNomeDocumento(QString fileName)
{
    this->caminhoCompleto = fileName;
    this->documentoId =  QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

void Documento::setTextoDocumento(QString &text)
{
    this->edit->setPlainText(text);
}

void Documento::setTextoDocumento(QByteArray text)
{
    this->edit->setPlainText(text);
}

void Documento::anexarTextoDocumento(QString &text)
{
    this->edit->appendPlainText(text);
}

QWidget *Documento::getWidget()
{
    return widget;
}

QString Documento::getDocumentoId()
{
    return this->documentoId;
}

QString Documento::getCaminhoCompleto()
{
    return this->caminhoCompleto;
}

void Documento::setFocus()
{
    this->edit->setFocus();
}

void Documento::repaintEdit()
{
    this->edit->forceUpdate();
}


