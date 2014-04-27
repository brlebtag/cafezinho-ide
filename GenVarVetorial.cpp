#include "GenVarVetorial.h"

GenVarVetorial::GenVarVetorial(No *no, int inicio_variavel) : GenVar(inicio_variavel)
{
    tipoVar = GenVar::tipoParaString(this->no->tipo);
    this->no = dynamic_cast<NDeclVarVetorial*>(no);
    QStringList coluna;
    coluna<<gerar_nome_vetor(this->no)<<tipoVar<<"";
    QTreeWidgetItem* item = new QTreeWidgetItem(coluna);
    itens.push_back(item);
    int posicao = inicio_variavel;
    gerar_nos(item, 0, dynamic_cast<NInteiro*>(this->no->dimensoes->at(0))->valor, this->no->dimensoes->size(), posicao);
}

GenVarVetorial::~GenVarVetorial()
{
    //testar ... pode ser q precisa só remover o primeiro ...
    foreach(QTreeWidgetItem* item, itens)
    {
        delete item;
    }

    itens.clear();
}

void GenVarVetorial::inserir(MaquinaVirtual &vm, QTreeWidget *widget)
{
    widget->addTopLevelItem(itens[0]);
    atualizar(vm);
}

void GenVarVetorial::remover(MaquinaVirtual &vm, QTreeWidget *widget)
{
    //testar...
    widget->removeItemWidget(itens[0], 0); //remove apenas o primeiro item...
    widget->removeItemWidget(itens[0], 1);
    widget->removeItemWidget(itens[0], 2);
}

void GenVarVetorial::atualizar(MaquinaVirtual &vm)
{
    int posicao = inicio_variavel;
    atualizar_nos(vm, itens[0], 0, dynamic_cast<NInteiro*>(no->dimensoes->at(0))->valor, no->dimensoes->size(), posicao);
}

void GenVarVetorial::gerar_nos(QTreeWidgetItem *pai, int indice, int dim, int tam, int &pos)
{
    QTreeWidgetItem* item;
    QStringList coluna;

    if(tam>1)
    {
        for(int i=0; i<dim; ++i)
        {
            QString nome = (*this->no->nome);
            nome +="["+QString::number(i)+"]";
            coluna<<nome<<tipoVar<<"";
            item = new QTreeWidgetItem(pai, coluna);
            itens.push_back(item);
            pai->addChild(item);
            gerar_nos(item, indice + 1, dynamic_cast<NInteiro*>(this->no->dimensoes->at(indice+1))->valor, tam-1, pos);
        }
    }
    else
    {
        for(int i=0; i<dim; ++i)
        {
            QString nome = (*this->no->nome);
            nome +="["+QString::number(i)+"]";
            item = new QTreeWidgetItem(pai, coluna);
            itens.push_back(item);
            pai->addChild(item);
            coluna<<nome<<tipoVar<<"";
            ++pos;
        }
    }
}

void GenVarVetorial::atualizar_nos(MaquinaVirtual &vm, QTreeWidgetItem *pai, int indice, int dim, int tam, int &pos)
{
    if(tam>1)
    {
        for(int i=0; i<dim; ++i)
        {
            atualizar_nos(vm, pai->child(i), indice + 1, dynamic_cast<NInteiro*>(this->no->dimensoes->at(indice+1))->valor, tam-1, pos);
        }
    }
    else
    {
        for(int i=0; i<dim; ++i)
        {
             pai->child(i)->setText(2, GenVar::memParaStr(vm, pos, no->tipo));
            ++pos;
        }
    }
}

QString GenVarVetorial::gerar_nome_vetor(NDeclVarVetorial *no)
{
    QString nome = (*no->nome) + "[";

    for(int i=0; i<no->dimensoes->size(); ++i)
    {
        nome+=QString::number(dynamic_cast<NInteiro*>(no->dimensoes->at(i))->valor)+"][";
    }

    return (nome + "]");
}
