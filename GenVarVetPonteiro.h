#ifndef GENVARVETPONTEIRO_H
#define GENVARVETPONTEIRO_H

#include "GenVarVetorial.h"

class GenVarVetPonteiro : public GenVarVetorial
{
public:
    GenVarVetPonteiro(No *no, int inicio_variavel, No *pno);
    ~GenVarVetPonteiro();
    void inserir(MaquinaVirtual &vm, QTreeWidget* widget);
    void remover(MaquinaVirtual &vm, QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm);
private:
    NDeclVarVetorial *pno;
    QTreeWidgetItem* item;

};

#endif // GENVARVETPONTEIRO_H
