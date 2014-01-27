#include "documentmanager.h"

const int DocumentManager::NOT_FOUND = -1;

DocumentManager::DocumentManager()
{

}

Document *DocumentManager::search(QString fileId)
{
    int pos = position(fileId);

    if(pos!=DocumentManager::NOT_FOUND)
        return IDE::null;
    return search(pos);
}

Document *DocumentManager::search(int position)
{
    return documents.at(position).first;
}

int DocumentManager::position(Document *document)
{
    int i=0;

    for(QList<Document*>::iterator it = documents.begin(); it!= documents.end(); it++,i++)
    {
        Document* doc = (*it);

        if(doc == document)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

int DocumentManager::position(QString fileId)
{
    int i=0;

    for(QList<Document*>::iterator it = documents.begin(); it!= documents.end(); it++,i++)
    {
        Document* doc = (*it);

        if(doc->getFileId() == fileId)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

void DocumentManager::insert(Document *document)
{
    documents.append(document);
}

void DocumentManager::insert(int position, Document *document)
{
    documents.insert(position, document);
}

void DocumentManager::remove(QString fileName)
{
    int pos = position(fileName);

    if(pos!=DocumentManager::NOT_FOUND)
        remove(position(fileName));
}

void DocumentManager::remove(int position)
{
    documents.removeAt(position);
}

void DocumentManager::remove(Document *document)
{
    int pos = position(document);

    if(pos!=DocumentManager::NOT_FOUND)
        remove(position(fileName));
}

QList::iterator DocumentManager::begin()
{
    return documents.begin();
}

QList::iterator DocumentManager::end()
{
    return documents.end();
}
