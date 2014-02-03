#include "document.h"

Document::Document(QWidget *widget, CodeEditor *edit, bool dirty)
    :widget(widget), edit(edit), dirty(dirty)
{
    opened = false;
}

bool Document::isEmpty()
{
    return this->edit->toPlainText().isEmpty();
}

bool Document::isDirty()
{
    return this->dirty;
}

bool Document::isOpened()
{
    return this->opened;
}

void Document::gotDirty()
{
    this->dirty = true;
}

void Document::gotCleaned()
{
    this->dirty = false;
}

void Document::gotOpened()
{
    this->opened = true;
}

void Document::closed()
{
    this->opened = false;
}

QString Document::getText()
{
    return this->edit->toPlainText();
}

void Document::setFileName(QString fileName)
{
    this->path = fileName;
    this->fileId =  QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

void Document::setText(QString &text)
{
    this->edit->setPlainText(text);
}

void Document::setText(QByteArray text)
{
    this->edit->setPlainText(text);
}

void Document::appendText(QString &text)
{
    this->edit->appendPlainText(text);
}

QWidget *Document::getWidget()
{
    return widget;
}

QString Document::getFileId()
{
    return this->fileId;
}

QString Document::getPath()
{
    return this->path;
}

void Document::setFocus()
{
    this->edit->setFocus();
}

void Document::repaintEdit()
{
    this->edit->forceUpdate();
}


