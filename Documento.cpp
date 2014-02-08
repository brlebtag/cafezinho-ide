#include "Documento.h"

Documento::Documento(QWidget *widget, EditorCodigo *edit, bool dirty)
    :widget(widget), edit(edit), sujo(dirty)
{
    aberto = false;
    edit->setWordWrapMode(QTextOption::NoWrap);
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
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

void Documento::repintarEditor()
{
    this->edit->forceUpdate();
}

void Documento::copiar()
{
    this->edit->copy();
}

void Documento::colar()
{
    this->edit->paste();
}

void Documento::recortar()
{
    this->edit->cut();
}

void Documento::desfazer()
{
    this->edit->undo();
}

void Documento::refazer()
{
    this->edit->redo();
}

bool Documento::isTextoSelecionado()
{
    return this->edit->isTextoSelecionado();
}

bool Documento::isColarDisponivel()
{
    return this->edit->canPaste(); //temporariamente...
}

bool Documento::isDesfazerDisponivel()
{
    return this->edit->document()->isUndoAvailable();
}

bool Documento::isRefazerDisponivel()
{
    return this->edit->document()->isRedoAvailable();
}

void Documento::setFonte(QString familia, int tamanho)
{
    this->edit->setFont(QFont(familia,tamanho));
}


