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
#include <QHash>
#include "MaquinaVirtual.h"



class GerenciadorVariaveis : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorVariaveis(QTreeWidget* widget, QObject *parent = 0);
    virtual ~GerenciadorVariaveis();
    void adicionar(MaquinaVirtual &vm, NDeclaracaoVariavel* no, int inicio_variavel, NDeclaracaoVariavel *pno = NULL);
    void remover(MaquinaVirtual &vm, NDeclaracaoVariavel* no);
    void atualizar(MaquinaVirtual &vm);

private:
    QTreeWidget* widget;
    QHash< QString, QStack< GenVar* > > variaveis;

signals:

public slots:

};

#endif // GERENCIADORVARIAVEIS_H
