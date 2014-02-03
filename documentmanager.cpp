#include "documentmanager.h"

const int DocumentManager::NOT_FOUND = -1;

DocumentManager::DocumentManager()
{

}

Documento *DocumentManager::search(QString fileId)
{
    int pos = position(fileId);

    if(pos!=DocumentManager::NOT_FOUND)
        return NULL;
    return search(pos);
}

Documento *DocumentManager::search(int position)
{
    return documents.at(position);
}

int DocumentManager::position(Documento *document)
{
    int i=0;

    for(QList<Documento*>::iterator it = documents.begin(); it!= documents.end(); it++,i++)
    {
        Documento* doc = (*it);

        if(doc == document)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

int DocumentManager::position(QString fileId)
{
    int i=0;

    for(QList<Documento*>::iterator it = documents.begin(); it!= documents.end(); it++,i++)
    {
        Documento* doc = (*it);

        if(doc->getDocumentoId() == fileId)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

void DocumentManager::insert(Documento *document)
{
    documents.append(document);
}

void DocumentManager::insert(int position, Documento *document)
{
    documents.insert(position, document);
}

void DocumentManager::remove(QString fileName)
{
    int pos = position(fileName);

    if(pos!=DocumentManager::NOT_FOUND)
        remove(pos);
}

void DocumentManager::remove(int position)
{
    documents.removeAt(position);
}

void DocumentManager::remove(Documento *document)
{
    int pos = position(document);

    if(pos!=DocumentManager::NOT_FOUND)
        remove(pos);
}

QList<Documento*>::iterator DocumentManager::begin()
{
    return documents.begin();
}

QList<Documento*>::iterator DocumentManager::end()
{
    return documents.end();
}
