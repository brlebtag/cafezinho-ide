#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>

class Document
{
public:
    Document(int id, QPlainTextEdit *edit, bool dirty = false );
    Document(QString fileId, int id, QPlainTextEdit *edit, bool dirty = false );
    bool isEmpty();
    bool isDirty();
    bool isOpened();
    void gotDirty();
    void gotCleaned();
    QString getText();
    void setFileId(QString fileId);
    void setText(QString &text);
    void appendText(QString &text);
    int getID();
    QString getFileId();
private:
    bool dirty;
    int id;
    QPlainTextEdit *edit;
    QString fileId;
    bool opened;
};

#endif // DOCUMENT_H
