#include "GenVarVetPonteiro.h"

GenVarVetPonteiro::GenVarVetPonteiro(No *no, int inicio_variavel, No *pno)
    : GenVarVetorial(no, inicio_variavel)
{
    this->pno = dynamic_cast<NDeclVarVetorial*>(pno);
    QStringList coluna;
    coluna<<GenVarVetorial::gerar_nome_vetor(this->pno)<<tipoVar<<"";
    item = new QTreeWidgetItem(coluna);
    item->addChild(itens[0]);
}

GenVarVetPonteiro::~GenVarVetPonteiro()
{
    //remove o primeiro pq vai ser chamado o descontrutor do pai ~GenVarVetorial() e ele vai remover itens[0]
    // e itens[0] vai remover os outros (funcionalidade do Qt)...
    item->removeChild(itens[0]);
    delete item;
}

void GenVarVetPonteiro::inserir(MaquinaVirtual &vm, QTreeWidget *widget)
{
    widget->addTopLevelItem(item);
    GenVarVetorial::atualizar(vm);
}

void GenVarVetPonteiro::remover(MaquinaVirtual &vm, QTreeWidget *widget)
{
    widget->removeItemWidget(item, 0); //remove apenas o primeiro item...
    widget->removeItemWidget(item, 1);
    widget->removeItemWidget(item, 2);
}

void GenVarVetPonteiro::atualizar(MaquinaVirtual &vm)
{
    GenVarVetorial::atualizar(vm);
}
