#ifndef GENVAR_H
#define GENVAR_H

#include "arvore_abstrata.h"
#include <QTreeWidget>
#include "MaquinaVirtual.h"

class GenVar
{
public:
    GenVar();
    virtual ~GenVar() = 0;
    virtual void inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget* widget)  = 0;
    virtual void remover(MaquinaVirtual &vm, No *no, QTreeWidget* widget)  = 0;
    virtual void atualizar(MaquinaVirtual &vm, QTreeWidget* widget) = 0;
    static QString tipoParaString(TipoVariavel::TipoVariavel variavel);
};

#endif // GENVAR_H
