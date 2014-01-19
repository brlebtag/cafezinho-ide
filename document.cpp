#include "document.h"

Document::Document(int id, QPlainTextEdit *edit, bool dirty)
    :id(id), edit(edit), dirty(dirty)
{
    opened = false;
}

Document::Document(QString fileId, int id, QPlainTextEdit *edit, bool dirty)
    :id(id), edit(edit), dirty(dirty)
{
    this->fileId =  QCryptographicHash::hash(fileId.toUtf8(),QCryptographicHash::Md5).toHex();
    opened = true;
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

QString Document::getText()
{
    return this->edit->toPlainText();
}

void Document::setFileId(QString fileId)
{
    this->fileId =  QCryptographicHash::hash(fileId.toUtf8(),QCryptographicHash::Md5).toHex();
    opened = true;
}

void Document::setText(QString &text)
{
    this->edit->setPlainText(text);
}

void Document::appendText(QString &text)
{
    this->edit->appendPlainText(text);
}

int Document::getID()
{
    return this->id;
}

QString Document::getFileId()
{
    return this->fileId;
}


