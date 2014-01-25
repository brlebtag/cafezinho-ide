#include "documentmanager.h"

const int DocumentManager::NOT_FOUND = 1;

DocumentManager::DocumentManager()
{

}

Document *DocumentManager::search(QString fileName)
{
    int pos = position(fileName);
    if(pos!=DocumentManager::NOT_FOUND)
        return IDE::null;
    return documents.at(pos).first;
}

int DocumentManager::position(Document *document)
{
    int i=0;
    for(QList<QPair<Document*,QString> >it = documents.begin(); it!= documents.end(); it++,i++)
    {
        QPair<Document*,QString> &obj = (*it);

        if(obj.first == document)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

int DocumentManager::position(QString fileName)
{
    int i=0;
    for(QList<QPair<Document*,QString> >it = documents.begin(); it!= documents.end(); it++,i++)
    {
        QPair<Document*,QString> &obj = (*it);

        if(obj.second == fileName)
            return i;
    }

    return DocumentManager::NOT_FOUND;
}

void DocumentManager::insert(Document *document, QString fileName)
{
    documents.append(qMakePair(document,fileName));
}

void DocumentManager::insert(Document *document)
{
    insert(document,"");
}

void DocumentManager::insert(int position, Document *document, QString fileName)
{
    documents.insert(position,qMakePair(document,fileName));
}

void DocumentManager::remove(QString fileName)
{
    remove(position(fileName));
}

void DocumentManager::remove(int position)
{
    documents.removeAt(position);
}

void DocumentManager::remove(Document *document)
{
    remove(position(document));
}
