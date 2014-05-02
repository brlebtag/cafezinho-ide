#include "GenQuadro.h"

GenQuadro::GenQuadro()
{
}

GenQuadro::~GenQuadro()
{
    for(QHash< QString, QStack< GenVar* > >::iterator it = variaveis.begin(); it != variaveis.end(); ++it)
    {
        QStack<GenVar*> &p = it.value();

        while(!p.isEmpty())
        {
            delete p.pop();
        }
    }
}


void GenQuadro::adicionar(QTreeWidget *widget, MaquinaVirtual &vm, NDeclaracaoVariavel *no, int inicio_variavel, bool visivel, NDeclaracaoVariavel *pno)
{
    GenVar *var;

    switch(no->tipoNo())
    {
        case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
        {
            if(pno==NULL)
                var = new GenVarEscalar(no, inicio_variavel);
            else
                var = new GenVarVetPonteiro(no, inicio_variavel, pno);
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
        {
            var = new GenVarVetorial(no, inicio_variavel);
        }
        break;
    }

    //Inseri na Hash
    if(variaveis.contains(*no->nome))
    {
        //Pego a pilha..
        QStack<GenVar*> &p = variaveis[*no->nome];

        //Esconde agora o que estava no topo...
        p.top()->remover(widget);

        //inseri ele na pilha...
        p.push(var);

    }
    else
    {
        //Crio um novo stack
        QStack<GenVar*> p;

        //empilho var
        p.push(var);

        //insero a pilha
        variaveis.insert(*no->nome, p);
    }

    if(visivel)
    {
        //já insere ele na ide...
        var->inserir(vm, widget);
    }
}

void GenQuadro::remover(QTreeWidget *widget, MaquinaVirtual &vm, NDeclaracaoVariavel *no, bool visivel)
{
    //Não preciso verificar se já contem pq isso já foi feito na analise semantica!!!
    QStack<GenVar*> &p = variaveis[*no->nome];

    //Remove o elemento do topo
    GenVar* var = p.pop();

    //Já remove da IDE...
    var->remover(widget);

    //Se a pilha ficou vazia então remove a pilha...
    if(p.isEmpty())
    {
        variaveis.remove(*no->nome);
    }
    else
    {
        if(visivel)
        {
            //restaura o antigo elemento que estava no topo..
            p.top()->inserir(vm, widget);
        }
    }

    //deleto
    delete var;
}

void GenQuadro::atualizar(MaquinaVirtual &vm)
{
    for(QHash< QString, QStack<GenVar*> >::iterator it = variaveis.begin(); it!= variaveis.end(); ++it)
    {
        it.value().top()->atualizar(vm);
    }
}

void GenQuadro::esconder(QTreeWidget* widget)
{
    for(QHash< QString, QStack<GenVar*> >::iterator it = variaveis.begin(); it!= variaveis.end(); ++it)
    {
        it.value().top()->remover(widget);
    }
}

void GenQuadro::mostrar(MaquinaVirtual &vm, QTreeWidget *widget)
{
    for(QHash< QString, QStack<GenVar*> >::iterator it = variaveis.begin(); it!= variaveis.end(); ++it)
    {
        GenVar * var = it.value().top();
        var->inserir(vm, widget);
    }
}
