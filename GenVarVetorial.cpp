#include "GenVarVetorial.h"

GenVarVetorial::GenVarVetorial()
{
}

GenVarVetorial::~GenVarVetorial()
{
    foreach(QTreeWidgetItem* item, itens)
    {
        delete item;
    }

    itens.clear();
}

void GenVarVetorial::inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget *widget)
{
    this->inicio_variavel = inicio_variavel;
    tipoVar = GenVar::tipoParaString(this->no->tipo);
    this->no = dynamic_cast<NDeclVarVetorial*>(no);
    QStringList coluna;
    coluna<<gerar_nome_vetor()<<tipoVar<<"";
    QTreeWidgetItem* item = new QTreeWidgetItem(widget, coluna);
    int posicao = inicio_variavel;
    gerar_nos(vm, item, 0, dynamic_cast<NInteiro*>(this->no->dimensoes->at(0))->valor, this->no->dimensoes->size(), posicao);
    widget->addTopLevelItem(item);
}

void GenVarVetorial::remover(MaquinaVirtual &vm, No *no, QTreeWidget *widget)
{
    //testar...
    widget->removeItemWidget(itens[0], 0); //remove apenas o primeiro item...
    widget->removeItemWidget(itens[0], 1);
    widget->removeItemWidget(itens[0], 2);
}

void GenVarVetorial::adicionar(MaquinaVirtual &vm, QTreeWidget *widget)
{
    widget->addTopLevelItem(itens[0]);
    atualizar(vm, wiget);
}

void GenVarVetorial::atualizar(MaquinaVirtual &vm, QTreeWidget *widget)
{
    int posicao = inicio_variavel;
    atualizar_nos(vm, itens[0], 0, dynamic_cast<NInteiro*>(no->dimensoes->at(0))->valor, no->dimensoes->size(), posicao);
}

void GenVarVetorial::gerar_nos(MaquinaVirtual &vm, QTreeWidgetItem *pai, int indice, int dim, int tam, int &pos)
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
            gerar_nos(vm, item, indice + 1, dynamic_cast<NInteiro*>(this->no->dimensoes->at(indice+1))->valor, tam-1, pos);
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
            coluna<<nome<<tipoVar<<GenVar::memParaStr(vm, pos, no->tipo);
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
            gerar_nos(vm, pai->child(i), indice + 1, dynamic_cast<NInteiro*>(this->no->dimensoes->at(indice+1))->valor, tam-1, pos);
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

QString GenVarVetorial::gerar_nome_vetor()
{
    QString nome = (*no->nome) + "[";

    for(int i=0; i<no->dimensoes->size(); ++i)
    {
        nome+=QString::number(dynamic_cast<NInteiro*>(no->dimensoes->at(i))->valor)+"][";
    }

    return (nome + "]");
}
