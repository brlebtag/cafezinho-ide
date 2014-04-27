#ifndef GERENCIADORVARIAVEIS_H
#define GERENCIADORVARIAVEIS_H

#include <QObject>
#include "arvore_abstrata.h"
#include "GenVar.h"
#include "GenVarEscalar.h"
#include "GenVarVetorial.h"
#include "GenVarVetPonteiro.h"
#include <QTreeWidget>
#include <QHash>
#include "MaquinaVirtual.h"
#include <QStack>

class GerenciadorVariaveis : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorVariaveis(QTreeWidget* widget, QObject *parent = 0);
    ~GerenciadorVariaveis();
    void adicionar(MaquinaVirtual &vm, NDeclaracaoVariavel* no, int inicio_variavel, NDeclaracaoVariavel *pno = NULL);
    void remover(MaquinaVirtual &vm, NDeclaracaoVariavel* no);

private:
    QHash< QString, QStack<GenVar*> > variaveis;
    QTreeWidget* widget;

signals:

public slots:
    void atualizar(MaquinaVirtual &vm);

};

#endif // GERENCIADORVARIAVEIS_H
