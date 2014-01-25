#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "codeeditor.h"
#include <QWidget>
#include "documentmanager.h"

class Document
{
public:
    Document(DocumentManager *docMan, CodeEditor *edit, bool dirty = false );
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
    void setText(QByteArray text);
    void appendText(QString &text);
    int getID();
    QString getFileId();
    QString getPath();
    void setFocus();
    void repaintEdit();
    QWidget *widget();
private:
    QWidget* tab;
    bool dirty;
    DocumentManager *docMan;
    CodeEditor *edit;
    QString fileId;
    QString path;
    bool opened;
};

#endif // DOCUMENT_H
