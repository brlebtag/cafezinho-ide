#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QList>
#include "document.h"
#include "ide.h"

class DocumentManager
{
public:
    static const int NOT_FOUND;
    DocumentManager();
    Document *search(QString fileId);
    Document *search(int position);
    int position(Document* document);
    int position(QString fileId);
    void insert(Document* document);
    void insert(int position, Document* document);
    void remove(QString fileName);
    void remove(int position);
    void remove(Document* document);
    QList<Document*>::iterator begin();
    QList<Document*>::iterator end();
private:
    QList<Document*> documents;
};

#endif // DOCUMENTMANAGER_H
