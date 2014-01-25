#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QList>
#include <QPair>
#include "document.h"
#include "ide.h"

class DocumentManager
{
public:
    static const int NOT_FOUND;
    DocumentManager();
    Document *search(QString fileName);
    int position(Document* document);
    int position(QString fileName);
    void insert(Document* document, QString fileName);
    void insert(Document* document);
    void insert(int position, Document* document, QString fileName);
    void remove(QString fileName);
    void remove(int position);
    void remove(Document* document);
private:
    QList<QPair<Document,QString>> documents;
};

#endif // DOCUMENTMANAGER_H
