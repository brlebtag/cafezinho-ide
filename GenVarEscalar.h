#ifndef GENVARESCALAR_H
#define GENVARESCALAR_H

#include "GenVar.h"
#include <QTreeWidgetItem>
#include <QStringList>

class GenVarEscalar : public GenVar
{
public:
    GenVarEscalar();
    ~GenVarEscalar();
    void inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget* widget);
    void remover(MaquinaVirtual &vm, No *no, QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm, QTreeWidget* widget);
    void adicionar(MaquinaVirtual &vm, QTreeWidget* widget);
    int inicio_variavel;
    NDeclVarEscalar *no;
    QTreeWidgetItem* item;
};

#endif // GENVARESCALAR_H
