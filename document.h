#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "codeeditor.h"

class Document
{
public:
    Document(int id, CodeEditor *edit, bool dirty = false );
    Document (QString fileName, int id, CodeEditor *edit, bool dirty = false );
    bool isEmpty();
    bool isDirty();
    bool isOpened();
    void gotDirty();
    void gotCleaned();
    void gotOpened();
    void closed();
    QString getText();
    void setFileName(QString fileName);
    void setText(QString &text);
    void appendText(QString &text);
    int getID();
    QString getFileId();
    QString getPath();
    void setFocus();
    void repaintEdit();
private:
    bool dirty;
    int id;
    CodeEditor *edit;
    QString fileId;
    QString path;
    bool opened;
};

#endif // DOCUMENT_H
