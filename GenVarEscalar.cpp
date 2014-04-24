#include "GenVarEscalar.h"

GenVarEscalar::GenVarEscalar(No *no, int inicio_variavel)
{
    this->inicio_variavel = inicio_variavel;
    this->no = dynamic_cast<NDeclVarEscalar*>(no);
    QStringList coluna;
    coluna<<(*this->no->nome)<<GenVar::tipoParaString(this->no->tipo)<<GenVar::memParaStr(vm, inicio_variavel, this->no->tipo);
    item = new QTreeWidgetItem(coluna);
}

GenVarEscalar::~GenVarEscalar()
{
    delete item;
}

void GenVarEscalar::inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget *widget)
{
    widget->addTopLevelItem(item);
    atualizar(vm, widget);
}

void GenVarEscalar::remover(MaquinaVirtual &vm, QTreeWidget *widget)
{
    widget->removeItemWidget(item, 0);
    widget->removeItemWidget(item, 1);
    widget->removeItemWidget(item, 2);
}

void GenVarEscalar::atualizar(MaquinaVirtual &vm, QTreeWidget *widget)
{
    item->setText(2, GenVar::tipoParaString(no->tipo));
}
