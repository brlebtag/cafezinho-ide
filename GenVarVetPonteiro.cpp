#include "GenVarVetPonteiro.h"

GenVarVetPonteiro::GenVarVetPonteiro(No *no, int inicio_variavel, No *pno)
    : GenVarVetorial(pno, inicio_variavel)
{
    this->ponteiro = dynamic_cast<NDeclVarVetorial*>(no);
    //guarda o nó que é o ponteiro (NDeclVarVetorial que é ponteiro para outro vetor)
    QStringList coluna;
    coluna<<GenVarVetorial::gerar_nome_vetor(this->ponteiro)<<tipoVar<<"";
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

void GenVarVetPonteiro::remover(QTreeWidget *widget)
{
    widget->takeTopLevelItem(widget->indexOfTopLevelItem(item));
}

void GenVarVetPonteiro::atualizar(MaquinaVirtual &vm)
{
    GenVarVetorial::atualizar(vm);
}

int GenVarVetPonteiro::tipoGenVar()
{
    return TipoGenVar::PONTEIRO;
}
