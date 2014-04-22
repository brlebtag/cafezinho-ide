#include "GenVarEscalar.h"

GenVarEscalar::GenVarEscalar()
{
}

GenVarEscalar::~GenVarEscalar()
{
    delete item;
}

void GenVarEscalar::inserir(MaquinaVirtual &vm, No *no, int inicio_variavel, QTreeWidget *widget)
{
    this->inicio_variavel = inicio_variavel;
    this->no = dynamic_cast<NDeclVarEscalar*>(no);
    QStringList coluna;
    coluna<<*this->no->nome<<GenVar::tipoParaString(this->no->tipo)<<vm.memoria[inicio_variavel];
    item = new QTreeWidgetItem(widget, coluna);
    widget->addTopLevelItem(item);
}

void GenVarEscalar::remover(MaquinaVirtual &vm, No *no, QTreeWidget *widget)
{
    widget->removeItemWidget(item, 0);
    widget->removeItemWidget(item, 1);
    widget->removeItemWidget(item, 2);
}

void GenVarEscalar::atualizar(MaquinaVirtual &vm, QTreeWidget *widget)
{
    switch(no->tipo)
    {
        case TipoVariavel::TIPO_CAR:
        {
            item->setText(2, QString(vm.memoria[inicio_variavel].toChar()));
        }
        break;
        case TipoVariavel::TIPO_INT:
        {
            item->setText(2, QString::number(vm.memoria[inicio_variavel].toInt()));
        }
        break;
        case TipoVariavel::TIPO_REAL:
        {
            item->setText(2, QString::number(vm.memoria[inicio_variavel].toDouble()));
        }
        break;
    }
}
