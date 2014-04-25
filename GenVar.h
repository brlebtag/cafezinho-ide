#ifndef GENVAR_H
#define GENVAR_H

#include "arvore_abstrata.h"
#include <QTreeWidget>
#include "MaquinaVirtual.h"

class GenVar
{
public:
    GenVar(int inicio_variavel);
    virtual ~GenVar();
    virtual void inserir(MaquinaVirtual &vm, QTreeWidget* widget)  = 0;
    virtual void remover(MaquinaVirtual &vm, QTreeWidget* widget)  = 0;
    virtual void atualizar(MaquinaVirtual &vm) = 0;
    static QString tipoParaString(TipoVariavel::TipoVariavel variavel);
    static QString memParaStr(MaquinaVirtual &vm, int posicao, TipoVariavel::TipoVariavel variavel);
    int inicio_variavel;
};

#endif // GENVAR_H
