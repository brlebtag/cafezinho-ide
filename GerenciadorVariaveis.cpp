#include "GerenciadorVariaveis.h"

GerenciadorVariaveis::GerenciadorVariaveis(QTreeWidget *widget, QObject *parent) :
    QObject(parent), widget(widget)
{
}

void GerenciadorVariaveis::adicionar(MaquinaVirtual &vm, No *no, int inicio_variavel)
{
    GenVar *var;

    switch(no->tipoNo())
    {
        case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
        {
            var = new GenVarEscalar();
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
        {
            var = new GenVarVetorial();
        }
        break;
    }

    var->inserir(vm, no, inicio_variavel, widget);
    variaveis.insert(no, var);
}

void GerenciadorVariaveis::remover(MaquinaVirtual &vm, No *no)
{
    GenVar* var = variaveis.value(no);
    var->remover(vm, no, widget);
    variaveis.remove(no);
    delete var;
}

void GerenciadorVariaveis::atualizar(MaquinaVirtual &vm)
{
    foreach(GenVar* var, variaveis)
    {
        var->atualizar(vm, widget);
    }
}
