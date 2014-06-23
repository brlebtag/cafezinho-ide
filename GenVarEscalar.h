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
    void remover(QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm);
    int tipoGenVar();
private:
    NDeclVarEscalar *no;
    QTreeWidgetItem* item;
};

#endif // GENVARESCALAR_H
