#ifndef GENVARVETORIAL_H
#define GENVARVETORIAL_H

#include "GenVar.h"
#include <QList>

class GenVarVetorial : public GenVar
{
public:
    GenVarVetorial(No *no, int inicio_variavel);
    ~GenVarVetorial();
    void inserir(MaquinaVirtual &vm, QTreeWidget* widget);
    void remover(MaquinaVirtual &vm, QTreeWidget* widget);
    void atualizar(MaquinaVirtual &vm);
private:
    NDeclVarVetorial *no;
    void gerar_nos(QTreeWidgetItem *pai, int indice, int dim, int tam, int &pos);
    void atualizar_nos(MaquinaVirtual &vm, QTreeWidgetItem *pai, int indice, int dim, int tam, int &pos);
    QString gerar_nome_vetor();
    QString tipoVar;
    QList<QTreeWidgetItem*> itens;
};

#endif // GENVARVETORIAL_H
