#ifndef GENQUADRO_H
#define GENQUADRO_H

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

class GenQuadro
{
public:
    GenQuadro();
    ~GenQuadro();
    void adicionar(QTreeWidget *widget, MaquinaVirtual &vm, NDeclaracaoVariavel* no, int inicio_variavel, bool visivel, NDeclaracaoVariavel *pno = NULL);
    void remover(QTreeWidget *widget, MaquinaVirtual &vm, NDeclaracaoVariavel* no, bool visivel);
    void atualizar(MaquinaVirtual &vm);
    void esconder(QTreeWidget* widget);
    void mostrar(MaquinaVirtual &vm, QTreeWidget* widget);
private:
    QHash< QString, QStack< GenVar* > > variaveis;
};

#endif // GENQUADRO_H
