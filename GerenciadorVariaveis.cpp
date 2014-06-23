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
    if(pno!=NULL)
    {
        //Busca pelo pno atual o pno correto...
        /*
         * seja o seguinte esquema
         *
         * quadro 1: int a[10]; //variavel vetor real
         * quadro 2: c[] //ponteiro para a
         * quadro 3: d[] // ponteiro para d
         *
         * assim:
         *       o pno de a é NULL
         *       o pno de c é a[10]
         *       o pno de d é c[] //mas nós queremos a[10]!!!!
         *por isso a busca em c para retornar o pno de c...
         *dai trocamos o pno c[] para a[10] em d
         *e se tiver outro x[] que aponta para d[] ele vai buscar o pno de d[] que é o pno de c[]
         *e assim por diante....
         */

        //Busca no quadro anterior...
        pno = variaveis[variaveis.size()-2]->buscar(pno);
    }
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

void GerenciadorVariaveis::desempilhar_tudo()
{
    //Removo todos os quadros e de todos os quadros eu removo todas
    // as variáveis.
    while(!variaveis.isEmpty())
    {
        GenQuadro* q = variaveis.pop();
        q->remover_todos(widget);
        delete q;
    }
}
