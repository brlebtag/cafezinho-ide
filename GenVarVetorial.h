#ifndef GENVARVETORIAL_H
#define GENVARVETORIAL_H

#include "GenVar.h"

class GenVarVetorial : public GenVar
{
public:
    GenVarVetorial();
    void inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget* widget);
    void remover(MaquinaVirtual &vm, No *no, QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm, QTreeWidget* widget);
    int inicio_variavel;
};

#endif // GENVARVETORIAL_H
