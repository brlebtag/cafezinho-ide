#ifndef GERENCIADORVARIAVEIS_H
#define GERENCIADORVARIAVEIS_H

#include <QObject>
#include "arvore_abstrata.h"
#include "GenVar.h"
#include "GenVarEscalar.h"
#include "GenVarVetorial.h"
#include "GenVarVetPonteiro.h"
#include <QTreeWidget>
#include <QString>
#include <QStack>
#include "MaquinaVirtual.h"
#include "GenQuadro.h"
#include "CompInfo.h"


class GerenciadorVariaveis : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorVariaveis(QTreeWidget* widget, QObject *parent = 0);
    virtual ~GerenciadorVariaveis();
    void empilha_quadro();
    void desempilha_quadro();
    void adicionar(NDeclaracaoVariavel* no, int inicio_variavel, NDeclaracaoVariavel *pno = NULL);
    void remover(NDeclaracaoVariavel* no);
    void atualizar();
    void setVisibilidade(bool visivel);
    void desempilhar_tudo();
private:
    QTreeWidget* widget;
    QStack< GenQuadro* > variaveis;
    bool visivel;

signals:

public slots:

};

#endif // GERENCIADORVARIAVEIS_H
