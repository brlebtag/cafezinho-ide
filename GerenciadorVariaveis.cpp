#include "GerenciadorVariaveis.h"

GerenciadorVariaveis::GerenciadorVariaveis(QTreeWidget *widget, QObject *parent) :
    QObject(parent), widget(widget)
{
    //já inicializo com um quadro que são as variaveis globais
    GenQuadro *quadro = new GenQuadro();
    variaveis.push(quadro);
    visivel = true;
}

GerenciadorVariaveis::~GerenciadorVariaveis()
{
}

void GerenciadorVariaveis::empilha_quadro()
{
    //sempre vou ter topo
    variaveis.top()->esconder(widget);
    GenQuadro *quadro = new GenQuadro();
    variaveis.push(quadro);
}

void GerenciadorVariaveis::desempilha_quadro()
{
    //Nunca vou ficar vazio
    MaquinaVirtual *vm = CompInfo::getVM();
    delete variaveis.pop();
    //Se tiver visivel então mostra o ue está agora no topo...
    if(visivel)
        variaveis.top()->mostrar(*vm, widget);
}

void GerenciadorVariaveis::adicionar(NDeclaracaoVariavel *no, int inicio_variavel, NDeclaracaoVariavel *pno)
{
    MaquinaVirtual *vm = CompInfo::getVM();
    variaveis.top()->adicionar(widget, *vm, no, inicio_variavel, visivel, pno);
}

void GerenciadorVariaveis::remover(NDeclaracaoVariavel *no)
{
    MaquinaVirtual *vm = CompInfo::getVM();
    variaveis.top()->remover(widget, *vm, no, visivel);
}

void GerenciadorVariaveis::atualizar()
{
    MaquinaVirtual *vm = CompInfo::getVM();
    variaveis.top()->atualizar(*vm);
}

void GerenciadorVariaveis::setVisibilidade(bool visivel)
{
    MaquinaVirtual *vm = CompInfo::getVM();

    this->visivel = visivel;

    //Se tiver visivel mostrar variaveis senão esconder elas...
    if(visivel)
        variaveis.top()->mostrar(*vm, widget);
    else
        variaveis.top()->esconder(widget);
}
