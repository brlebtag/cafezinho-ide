#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QList>
#include "Documento.h"
#include <QObject>

class IDE;

class GerenciadorDocumento
{
public:
    GerenciadorDocumento();
    Documento *procurar(QString fileId);
    Documento *procurar(int posicao);
    int posicao(Documento* document);
    int posicao(QString fileId);
    int posicao(QObject *botao);
    void inserir(Documento* document);
    void inserir(int posicao, Documento* document);
    void remover(QString fileName);
    void remover(int posicao);
    void remover(Documento* document);
    QList<Documento*>::iterator begin();
    QList<Documento*>::iterator end();
    Documento* operator[](int i);
    int tamanho();
private:
    static const int NAO_ACHADO;
    QList<Documento*> documentos;
};

#endif // DOCUMENTMANAGER_H
