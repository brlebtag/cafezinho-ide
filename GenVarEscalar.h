#ifndef GENVARESCALAR_H
#define GENVARESCALAR_H

#include "GenVar.h"
#include <QTreeWidgetItem>
#include <QStringList>

class GenVarEscalar : public GenVar
{
public:
    GenVarEscalar(No *no, int inicio_variavel);
    ~GenVarEscalar();
    void inserir(MaquinaVirtual &vm, QTreeWidget* widget);
    void remover(MaquinaVirtual &vm, QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm);
private:
    int inicio_variavel;
    NDeclVarEscalar *no;
    QTreeWidgetItem* item;
};

#endif // GENVARESCALAR_H
