#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "codeeditor.h"
#include <QWidget>

class Document
{
public:
    Document(QWidget *widget, CodeEditor *edit, bool dirty = false );
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
    QWidget *getWidget();
    QString getFileId();
    QString getPath();
    void setFocus();
    void repaintEdit();
private:
    bool dirty;
    QWidget *widget;
    CodeEditor *edit;
    QString fileId;
    QString path;
    bool opened;
};

#endif // DOCUMENT_H
