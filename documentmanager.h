#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QList>
#include "documento.h"

class IDE;

class DocumentManager
{
public:
    static const int NOT_FOUND;
    DocumentManager();
    Documento *search(QString fileId);
    Documento *search(int position);
    int position(Documento* document);
    int position(QString fileId);
    void insert(Documento* document);
    void insert(int position, Documento* document);
    void remove(QString fileName);
    void remove(int position);
    void remove(Documento* document);
    QList<Documento*>::iterator begin();
    QList<Documento*>::iterator end();
private:
    QList<Documento*> documents;
};

#endif // DOCUMENTMANAGER_H
