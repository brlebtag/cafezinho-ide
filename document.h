#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>

class Document
{
public:
    Document(int id, QPlainTextEdit *edit, bool dirty = false );
    Document (QString fileName, int id, QPlainTextEdit *edit, bool dirty = false );
    bool isEmpty();
    bool isDirty();
    bool isOpened();
    void gotDirty();
    void gotCleaned();
    QString getText();
    void setFileName(QString fileName);
    void setText(QString &text);
    void appendText(QString &text);
    int getID();
    QString getFileId();
    QString getPath();
private:
    bool dirty;
    int id;
    QPlainTextEdit *edit;
    QString fileId;
    QString path;
    bool opened;
};

#endif // DOCUMENT_H
