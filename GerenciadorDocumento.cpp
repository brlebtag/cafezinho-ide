#include "GerenciadorDocumento.h"

const int GerenciadorDocumento::NAO_ACHADO = -1;

GerenciadorDocumento::GerenciadorDocumento()
{

}

Documento *GerenciadorDocumento::procurar(QString fileId)
{
    int pos = posicao(fileId);

    if(pos!=GerenciadorDocumento::NAO_ACHADO)
        return NULL;
    return procurar(pos);
}

Documento *GerenciadorDocumento::procurar(int position)
{
    if(position >=0 && position < documentos.size())
        return documentos.at(position);
    else
        return NULL;
}

int GerenciadorDocumento::posicao(Documento *document)
{
    int i=0;

    for(QList<Documento*>::iterator it = documentos.begin(); it!= documentos.end(); it++,i++)
    {
        Documento* doc = (*it);

        if(doc == document)
            return i;
    }

    return GerenciadorDocumento::NAO_ACHADO;
}

int GerenciadorDocumento::posicao(QString fileId)
{
    int i=0;

    for(QList<Documento*>::iterator it = documentos.begin(); it!= documentos.end(); it++,i++)
    {
        Documento* doc = (*it);
        QString id = doc->getDocumentoId() ;
        if(id == fileId)
            return i;
    }

    return GerenciadorDocumento::NAO_ACHADO;
}

void GerenciadorDocumento::inserir(Documento *document)
{
    documentos.append(document);
}

void GerenciadorDocumento::inserir(int position, Documento *document)
{
    documentos.insert(position, document);
}

void GerenciadorDocumento::remover(QString fileName)
{
    int pos = posicao(fileName);

    if(pos!=GerenciadorDocumento::NAO_ACHADO)
        remover(pos);
}

void GerenciadorDocumento::remover(int position)
{
    documentos.removeAt(position);
}

void GerenciadorDocumento::remover(Documento *document)
{
    int pos = posicao(document);

    if(pos!=GerenciadorDocumento::NAO_ACHADO)
        remover(pos);
}

QList<Documento*>::iterator GerenciadorDocumento::begin()
{
    return documentos.begin();
}

QList<Documento*>::iterator GerenciadorDocumento::end()
{
    return documentos.end();
}

int GerenciadorDocumento::tamanho()
{
    return documentos.size();
}
