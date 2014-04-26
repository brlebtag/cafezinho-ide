#include "GerenciadorVariaveis.h"

GerenciadorVariaveis::GerenciadorVariaveis(QTreeWidget *widget, QObject *parent) :
    QObject(parent), widget(widget)
{
}

GerenciadorVariaveis::~GerenciadorVariaveis()
{

}

void GerenciadorVariaveis::adicionar(MaquinaVirtual &vm, NDeclaracaoVariavel *no, int inicio_variavel)
{
    GenVar *var;

    switch(no->tipoNo())
    {
        case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
        {
            var = new GenVarEscalar(no, inicio_variavel);
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
        {
            var = new GenVarVetorial(no, inicio_variavel);
        }
        break;
    }

    memoria[inicio_variavel] = var;

    //Inseri na Hash
    if(variaveis.contains(*no->nome))
    {
        QStack<GenVar*> p;
        p.push(var);
        variaveis.insert(*no->nome, p);
    }
    else
    {
        //Pego a pilha..
        QStack<GenVar*> &p = variaveis[*no->nome];

        //Esconde agora o que estava no topo...
        p.top()->remover(vm, widget);

        //inseri ele na pilha...
        p.push(var);
    }

    //já insere ele na ide...
    var->inserir(vm, widget);
}

void GerenciadorVariaveis::remover(MaquinaVirtual &vm, NDeclaracaoVariavel *no)
{
    //Não preciso verificar se já contem pq isso já foi feito na analise semantica!!!
    QStack<GenVar*> &p = variaveis[*no->nome];

    //Remove o elemento do topo
    GenVar* var = p.pop();

    //Já remove da IDE...
    var->remover(vm, widget);

    //Se a pilha ficou vazia então remove a pilha...
    if(p.isEmpty())
    {
        variaveis.remove(*no->nome);
    }

    memoria.remove(var->inicio_variavel);

    //deleto
    delete var;
}

void GerenciadorVariaveis::atualizar(MaquinaVirtual &vm)
{
    for(QHash< QString, QStack<GenVar*> >::iterator it = variaveis.begin(); it!= variaveis.end(); ++it)
    {
        it.value().top()->atualizar(vm);
    }
}
