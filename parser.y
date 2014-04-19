%code requires
{
#include <cstdio>
#include <iostream>
#include "arvore_abstrata.h"
#include <QString>
#include <QList>
#include <QDebug>
#include "CompInfo.h"
#include "CompThread.h"
}

%{
#include <cstdio>
#include "arvore_abstrata.h"
#include <QString>
#include <QList>
#include <QDebug>
#include "CompThread.h"
#include "CompInfo.h"

extern "C" int yylex();
extern "C" FILE *yyin;
extern int yylineno;
extern QString ultimo_token;
bool erro_compilador = false;
bool erro_lexico = false;

using namespace std;

void yyerror(NBloco * bloco, const char *s);
bool checa_vetor(ListaExpressao *dimensao, ListaExpressao *lista, int indice, int dim, int tam);
%}

%union
{
    int ival;
    QString *sval;
    double dval;
    No* no;
    NBloco *bloco;
    NExpressao *expr;
    NInstrucao *inst;
    NIdentificador *ident;
    NOperacaoUnaria *uni;
    NDeclaracaoVariavel *declVar;
    QList<NDeclaracaoVariavel*> *listVar;
    QList<NExpressao*> *listExpr;
    QList<NInstrucao*> *listInstr;
    NDeclaracaoFuncao *declFunc;
    TipoVariavel::TipoVariavel tipoVar;
    QList<int>* vetDim;
    Operador::Operador op;
    NListaExpressoes *nlistExpr;
}

%destructor{ delete $$; $$ = 0; } <sval>
%destructor{ delete $$; $$ = 0; } <bloco>
%destructor{ delete $$; $$ = 0; } <expr>
%destructor{ delete $$; $$ = 0; } <ident>
%destructor{ delete $$; $$ = 0; } <inst>
%destructor{ delete $$; $$ = 0; } <uni>
%destructor{ delete $$; $$ = 0; } <declVar>
%destructor{ delete $$; $$ = 0; } <declFunc>
%destructor{ delete $$; $$ = 0; } <nlistExpr>
%destructor{ delete $$; $$ = 0; } <vetDim>
%destructor{
        for(ListaVariavel::iterator it = $$->begin(); it!= $$->end(); ++it)
        {
                delete (*it);
        }
        delete $$;
        $$ = 0;
 } <listVar>
%destructor{
        for(ListaExpressao::iterator it = $$->begin(); it!= $$->end(); ++it)
        {
                delete (*it);
        }
        delete $$;
        $$ = 0;
 } <listExpr>

%destructor{
        for(ListaInstrucao::iterator it = $$->begin(); it!= $$->end(); ++it)
        {
                delete (*it);
        }
        delete $$;
        $$ = 0;
 } <listInstr>

%parse-param { NBloco *bloco }
%error-verbose

%token CAR INT REAL NULO

%token<sval> IDENTIFICADOR
%token<sval> PALAVRA_LITERAL
%token<ival> INT_CONST
%token<dval> REAL_CONST
%token<ival> CAR_CONST

%token<ival> SE
%token<ival> ENQUANTO
%token<ival> LEIA
%token<ival> ESCREVA
%token<ival> RETORNE
%token<ival> NOVA_LINHA
%token<ival> '('
%token<ival> '{'
%token<ival> '['
%token<ival> INC_OP
%token<ival> DEC_OP
%token<ival> TERMINAR
%token<ival> LIMPAR
%token ENTAO EXECUTE SENAO

%token MULT_ATRIBUICAO DIV_ATRIBUICAO MOD_ATRIBUICAO ADICAO_ATRIBUICAO SUBTRACAO_ATRIBUICAO
%token ESQ_ATRIBUICAO DIR_ATRIBUICAO E_ATRIBUICAO XOR_ATRIBUICAO OU_ATRIBUICAO POT_ATRIBUICAO

%token OU_OP E_OP EQ_OP NE_OP LE_OP GE_OP ESQ_OP DIR_OP POT_OP BT_OP LT_OP

%start programa

%type<listInstr> unidade_traducao lista_instrucao declaracao_externa lista_declaracao inicio_declarador inicio_lista_declaracao declaracao
%type<inst> instrucao instrucao_expressao instrucao_sistema
%type<inst> instrucao_decisao instrucao_iteracao instrucao_entrada_saida instrucao_salto
%type<tipoVar> tipo_especificador
%type<declFunc> declarador_funcao
%type<declVar> declaracao_parametro declarador
%type<listVar> lista_parametro
%type<bloco> instrucao_composta
%type<listExpr> lista_ponteiro_vetor inicializador lista_inicializador lista_expr_vetor lista_expressao
%type<op> operador_atribuicao
%type<expr> expressao_atribuicao expressao_condicional expressao_logico_ou expressao_logico_e expressao_inclusivo_ou
%type<expr> expressao_exclusivo_ou expressao_e expressao_igualdade expressao_relacional expressao_shift expressao_aditiva
%type<expr> expressao_multiplicativa expressao_cast expressao_unaria expressao_posfix expressao_primaria
%type<uni> operador_unario
%type<nlistExpr> expressao

%%

programa
        : unidade_traducao { bloco->instrucoes = $1; }
        ;

unidade_traducao
        : declaracao_externa {  $$ = $1; }
        | unidade_traducao declaracao_externa
        {
                $$ = $1;

                for(ListaInstrucao::iterator it = $2->begin(); it!=$2->end(); ++it)
                {
                        $$->push_back((*it));
                }

                delete $2;
        }
        ;

declaracao_externa
        : tipo_especificador declarador_funcao instrucao_composta
        {
                $2->tipo = $1;
                $2->bloco = $3;
                $$ = new ListaInstrucao();
                $$->push_back($2);
        }
        | tipo_especificador inicio_lista_declaracao ';'
        {
                for(ListaInstrucao::iterator it = $2->begin(); it!= $2->end(); ++it)
                {
                        No* no = dynamic_cast<No*>(*it);
                        if(no->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_ESCALAR||no->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_VETORIAL)
                        {
                                NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);
                                var->tipo = $1;
                        }
                }
                $$ = $2;
        }
        ;

tipo_especificador
        : NULO { $$ = TipoVariavel::TIPO_NULO; }
        | CAR { $$ = TipoVariavel::TIPO_CAR;  }
        | INT { $$ = TipoVariavel::TIPO_INT;  }
        | REAL { $$ = TipoVariavel::TIPO_REAL; }
        ;

declarador_funcao
        : IDENTIFICADOR '(' lista_parametro ')'
        {
                $$ = new NDeclaracaoFuncao($1, $3, yylineno);
                for(ListaVariavel::iterator it = $3->begin(); it!= $3->end(); ++it)
                {
                        if(dynamic_cast<No*>((*it))->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_VETORIAL)
                        {
                                //Seta que essas variaveis são parametro de funcao...
                                dynamic_cast<NDeclVarVetorial*>((*it))->eParametro = true;
                        }
                }
        }
        | IDENTIFICADOR '(' ')' { $$ = new NDeclaracaoFuncao($1, new ListaVariavel() , yylineno); }
        ;

lista_parametro
        : declaracao_parametro { $$ = new ListaVariavel();  $$->push_back($1); }
        | lista_parametro ',' declaracao_parametro { $1->push_back($3); $$ = $1; }
        ;

declaracao_parametro
        : tipo_especificador declarador { $2->tipo = $1; $$ = $2;}
        ;

declarador
        : IDENTIFICADOR lista_ponteiro_vetor { $$ = new NDeclVarVetorial($1, $2, yylineno); }
        | IDENTIFICADOR { $$ = new NDeclVarEscalar($1, yylineno); }
        ;

lista_ponteiro_vetor
        : '[' ']' { $$ = new ListaExpressao(); $$->push_back(new NExpressao($1)); }
        | '[' INT_CONST ']' { $$ = new ListaExpressao(); $$->push_back(new NInteiro($2, $1));}
        | lista_ponteiro_vetor '[' INT_CONST ']' { $1->push_back(new NInteiro($3, $2)); $$ = $1; }
        ;

instrucao_composta
        : '{' '}' { $$ = new NBloco($1); $$->instrucoes = new ListaInstrucao(); }
        | '{' lista_instrucao'}' { $$ = new NBloco($1); $$->instrucoes = $2; }
        | '{' lista_declaracao '}' { $$ = new NBloco($1); $$->instrucoes = $2; }
        | '{' lista_declaracao lista_instrucao '}'
        {
                $$ = new NBloco($1);
                $$->instrucoes = $2;

                for(ListaInstrucao::iterator it = $3->begin(); it!=$3->end(); ++it)
                {
                        $$->instrucoes->push_back((*it));
                }

                delete $3;
        }
        ;

lista_instrucao
        : instrucao { $$ = new ListaInstrucao(); $$->push_back($1); }
        | lista_instrucao instrucao { $1->push_back($2); $$ = $1; }
        ;

instrucao
        : instrucao_composta { $$ = $1; }
        | instrucao_expressao { $$ = $1; }
        | instrucao_decisao { $$ = $1; }
        | instrucao_iteracao { $$ = $1; }
        | instrucao_entrada_saida { $$ = $1; }
        | instrucao_salto { $$ = $1; }
        | instrucao_sistema { $$ = $1; }
        ;

instrucao_expressao
        : ';' { $$ = new NInstrucaoExpressao(new NExpressao(yylineno)); }
        | expressao ';' { $$ = new NInstrucaoExpressao($1, $1->linha); }
        ;

instrucao_decisao
        : SE '(' expressao ')' ENTAO instrucao { $$ = new NSe($3, $6, $1); }
        | SE '(' expressao ')' ENTAO instrucao SENAO instrucao { $$ = new NSeSenao($3, $6, $8, $1); }
        ;

instrucao_iteracao
        : ENQUANTO '(' expressao ')' EXECUTE instrucao { $$ = new NEnquanto($3, $6, $1); }
        ;
instrucao_entrada_saida
        : LEIA expressao ';' { $$ = new NLeia( $2, $1); }
        | ESCREVA expressao ';' { $$ = new NEscreva($2, $1); }
        | NOVA_LINHA ';' { $$ = new NInstrucaoExpressao( new NNovaLinha($1), $1); }
        ;

instrucao_salto
        : RETORNE ';' { $$ = new NRetorne(new NExpressao($1), $1); }
        | RETORNE expressao ';' { $$ = new NRetorne($2, $1); }
        ;

instrucao_sistema
        : TERMINAR ';' { $$ = new NTerminar($1); }
        | LIMPAR ';' { $$ = new NLimpar($1); }
        ;


lista_declaracao
        : declaracao  { $$ = $1; }
        | lista_declaracao declaracao
        {
                $$ = $1;

                for(ListaInstrucao::iterator it = $2->begin(); it!= $2->end(); ++it)
                {
                        $$->push_back((*it));
                }

                delete $2;
        }
        ;

declaracao
        : tipo_especificador inicio_lista_declaracao ';'
        {
                for(ListaInstrucao::iterator it = $2->begin(); it!= $2->end(); ++it)
                {
                        No* no = dynamic_cast<No*>(*it);
                        if(no->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_ESCALAR||no->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_VETORIAL)
                        {
                                NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);
                                var->tipo = $1;
                        }
                }
                $$ = $2;
        }
        ;

inicio_lista_declaracao
        : inicio_declarador { $$ = $1; }
        | inicio_lista_declaracao ',' inicio_declarador
        {
            /*
             * PARTE MUITO IMPORTANTE:
             * se eu tiver uma coisa assim: int a,b,c,d,...; sendo q cada um está numa linha diferente
             * eu vou fazer com que todos estejam na mesma linha para no debug eu executar está instrucão como
             * uma só!!!!! o lado mais a esquerda da arvore possui o primeiro a ser inserido (a linguagem deriva
             * a esquerda) dai eu pego o mais a esquerda e faço com que todos os outros tenham a mesma linha
             * apesar de terem sido declaradas em outras linhas.....
             */
                $$ = $1;
                //pega o primeiro que é mais a esquerda e tem a linha correta da primeira declaração!!!!
                int linha = $$->at(0)->linha;

                for(ListaInstrucao::iterator it = $3->begin(); it!= $3->end(); ++it)
                {
                    //seta para todos ficarem com a mesma linha
                    (*it)->linha = linha;
                    $$->push_back((*it));

                }

                delete $3;
        }
        ;

inicio_declarador
        : declarador { $$ = new ListaInstrucao(); $$->push_back($1); }
        | declarador '=' inicializador
        {
                No* no = dynamic_cast<No*>($1);

                if(no->tipoNo()==TipoNo::DECLARACAO_VARIAVEL_ESCALAR)
                {
                        NDeclVarEscalar *decEsc = dynamic_cast<NDeclVarEscalar*>($1);
                        if((dynamic_cast<No*>($3->at(0)))->tipoNo()==TipoNo::LISTA_INICIALIZADOR)
                        {
                                CompInfo::out()<<"[ERRO SEMANTICO] Inicializador não está no formato correto, esperado apenas 1 valor próximo a "<<yylineno<<"\n";
                                erro_compilador = true;
                                YYABORT;
                        }


                        $$ = new ListaInstrucao();

                        NIdentificadorEscalar *ident = new NIdentificadorEscalar(new QString(*decEsc->nome), decEsc->linha);

                        NAtribuicao* atrib = new NAtribuicao(ident, Operador::ATRIBUICAO_OP, $3->at(0), decEsc->linha);
                        atrib->inicializa_variavel = true;

                        $$->push_back($1);
                        $$->push_back((NInstrucao*)atrib);

                        delete $3;
                }
                else
                {
                        NDeclVarVetorial *decVet = dynamic_cast<NDeclVarVetorial*>($1);
                        NExpressao *expr = decVet->dimensoes->at(0);
                        int dim =  (dynamic_cast<NInteiro*>(expr))->valor;

                        $$ = new ListaInstrucao();
                        if((dynamic_cast<No*>($3->at(0)))->tipoNo()!=TipoNo::LISTA_INICIALIZADOR)
                        {
                                CompInfo::out()<<"[ERRO SEMANTICO] Inicializador não está no formato correto próximo a "<<yylineno<<"\n";
                                erro_compilador = true;
                                YYABORT;
                        }
                        else if(!checa_vetor(decVet->dimensoes, (dynamic_cast<NListaInicializador*>($3->at(0)))->expressoes, 0, dim, decVet->dimensoes->size()))
                        {
                                int qtd_dimensao = 1;
                                for(ListaExpressao::iterator it = decVet->dimensoes->begin(); it!= decVet->dimensoes->end(); ++it)
                                {
                                        qtd_dimensao *= dynamic_cast<NInteiro*>(*it)->valor;
                                }
                                CompInfo::out()<<"[ERRO SEMANTICO] Inicializador não está no formato correto, esperado "<<qtd_dimensao<<" valores para ser inicializado próximo a "<<yylineno<<"\n";
                                erro_compilador = true;
                                YYABORT;
                        }
                        $$->push_back($1);
                        $$->push_back(new NInicializadorVetor(new QString(*decVet->nome), $3, decVet->linha));
                }
        }
        ;

inicializador
        : expressao_atribuicao { $$ = new ListaExpressao(); $$->push_back($1); }
        | '{' lista_inicializador '}'  { $$ = new ListaExpressao(); $$->push_back(new NListaInicializador($2, $1)); }
        ;

lista_inicializador
        : inicializador { $$ = $1; }
        | lista_inicializador ',' inicializador
        {
                for(ListaExpressao::iterator it = $3->begin(); it!=$3->end(); ++it)
                {
                        $1->push_back((*it));
                }
                delete $3;
                $$ = $1;
        }
        ;

expressao_atribuicao
        : expressao_condicional { $$ = $1; }
        | expressao_unaria	operador_atribuicao expressao_atribuicao { $$ = new NAtribuicao($1, $2, $3, $1->linha); }
        ;

operador_atribuicao
        : '=' { $$ = Operador::ATRIBUICAO_OP; }
        | MULT_ATRIBUICAO { $$ = Operador::MULT_ATRIBUICAO; }
        | DIV_ATRIBUICAO { $$ = Operador::DIV_ATRIBUICAO; }
        | MOD_ATRIBUICAO { $$ = Operador::MOD_ATRIBUICAO; }
        | ADICAO_ATRIBUICAO { $$ = Operador::ADICAO_ATRIBUICAO; }
        | SUBTRACAO_ATRIBUICAO { $$ = Operador::SUBTRACAO_ATRIBUICAO; }
        | ESQ_ATRIBUICAO { $$ = Operador::ESQ_ATRIBUICAO; }
        | DIR_ATRIBUICAO { $$ = Operador::DIR_ATRIBUICAO; }
        | E_ATRIBUICAO { $$ = Operador::E_ATRIBUICAO; }
        | XOR_ATRIBUICAO { $$ = Operador::XOR_ATRIBUICAO; }
        | OU_ATRIBUICAO { $$ = Operador::OU_ATRIBUICAO; }
        | POT_ATRIBUICAO { $$ = Operador::POT_ATRIBUICAO; }
        ;

expressao_condicional
        : expressao_logico_ou { $$ = $1; }
        | expressao_logico_ou '?' expressao ':' expressao_condicional { $$ = new NOperacaoTerciaria($1, $3, $5, $1->linha); }
        ;

expressao_logico_ou
        : expressao_logico_e { $$ = $1; }
        | expressao_logico_ou OU_OP expressao_logico_e { $$ = new NOperacaoBinaria($1, Operador::OU_OP, $3, $1->linha); }
        ;

expressao_logico_e
        : expressao_inclusivo_ou { $$ = $1; }
        | expressao_logico_e E_OP expressao_inclusivo_ou { $$ = new NOperacaoBinaria($1, Operador::E_OP, $3, $1->linha); }
        ;

expressao_inclusivo_ou
        : expressao_exclusivo_ou { $$ = $1; }
        | expressao_inclusivo_ou '|' expressao_exclusivo_ou { $$ = new NOperacaoBinaria($1, Operador::OU_BIT_OP, $3, $1->linha); }
        ;

expressao_exclusivo_ou
        : expressao_e { $$ = $1; }
        | expressao_exclusivo_ou '^' expressao_e { $$ = new NOperacaoBinaria($1, Operador::XOR_BIT_OP, $3, $1->linha); }
        ;

expressao_e
        : expressao_igualdade { $$ = $1; }
        | expressao_e '&' expressao_igualdade { $$ = new NOperacaoBinaria($1, Operador::E_BIT_OP, $3, $1->linha); }
        ;

expressao_igualdade
        : expressao_relacional { $$ = $1; }
        | expressao_igualdade EQ_OP expressao_relacional { $$ = new NOperacaoBinaria($1, Operador::EQ_OP, $3, $1->linha); }
        | expressao_igualdade NE_OP expressao_relacional { $$ = new NOperacaoBinaria($1, Operador::NE_OP, $3, $1->linha); }
        ;

expressao_relacional
        : expressao_shift { $$ = $1; }
        | expressao_relacional LT_OP expressao_shift { $$ = new NOperacaoBinaria($1, Operador::LT_OP, $3, $1->linha); }
        | expressao_relacional BT_OP expressao_shift { $$ = new NOperacaoBinaria($1, Operador::BT_OP, $3, $1->linha); }
        | expressao_relacional LE_OP expressao_shift { $$ = new NOperacaoBinaria($1, Operador::LE_OP, $3, $1->linha); }
        | expressao_relacional GE_OP expressao_shift { $$ = new NOperacaoBinaria($1, Operador::GE_OP, $3, $1->linha); }
        ;

expressao_shift
        : expressao_aditiva { $$ = $1; }
        | expressao_shift ESQ_OP expressao_aditiva { $$ = new NOperacaoBinaria($1, Operador::ESQ_OP, $3, $1->linha); }
        | expressao_shift DIR_OP expressao_aditiva { $$ = new NOperacaoBinaria($1, Operador::DIR_OP, $3, $1->linha); }
        ;

expressao_aditiva
        : expressao_multiplicativa { $$ = $1; }
        | expressao_aditiva '+' expressao_multiplicativa { $$ = new NOperacaoBinaria($1, Operador::SOM_OP, $3, $1->linha); }
        | expressao_aditiva '-' expressao_multiplicativa { $$ = new NOperacaoBinaria($1, Operador::SUB_OP, $3, $1->linha); }
        ;

expressao_multiplicativa
        : expressao_cast { $$ = $1; }
        | expressao_multiplicativa '*' expressao_cast { $$ = new NOperacaoBinaria($1, Operador::MULT_OP, $3, $1->linha); }
        | expressao_multiplicativa '/' expressao_cast { $$ = new NOperacaoBinaria($1, Operador::DIV_OP, $3, $1->linha); }
        | expressao_multiplicativa '%' expressao_cast { $$ = new NOperacaoBinaria($1, Operador::REST_OP, $3, $1->linha); }
        | expressao_multiplicativa POT_OP expressao_cast { $$ = new NOperacaoBinaria($1, Operador::POT_OP, $3, $1->linha); }
        ;

expressao_cast
        : expressao_unaria { $$ = $1; }
        | '(' tipo_especificador ')' expressao_cast { $$ = new NCast($4, $2, $1); }
        ;

expressao_unaria
        : expressao_posfix { $$ = $1; }
        | INC_OP expressao_unaria { $$ = new NOperacaoUnaria($2, Operador::INC_PRE_OP, $1); }
        | DEC_OP expressao_unaria { $$ = new NOperacaoUnaria($2, Operador::DEC_PRE_OP, $1); }
        | operador_unario expressao_cast { $1->rhs = $2; $$ = $1; }
        ;

operador_unario
        : '-' { $$ = new NOperacaoUnaria(0, Operador::MIN_OP, yylineno); }
        | '!' { $$ = new NOperacaoUnaria(0, Operador::NEG_OP, yylineno); }
        | '~' { $$ = new NOperacaoUnaria(0, Operador::NEG_OP, yylineno); }
        ;

expressao_posfix
        : expressao_primaria  { $$ = $1; }
        | expressao_posfix INC_OP { $$ = new NOperacaoUnaria($1, Operador::INC_POS_OP, $1->linha); }
        | expressao_posfix DEC_OP { $$ = new NOperacaoUnaria($1, Operador::DEC_POS_OP, $1->linha); }
        ;

expressao_primaria
        : IDENTIFICADOR { $$ = new NIdentificadorEscalar($1, yylineno); }
        | IDENTIFICADOR lista_expr_vetor { $$ = new NIdentificadorVetorial($1, $2, yylineno); }
        | IDENTIFICADOR '(' lista_expressao ')' { $$ = new NChamadaFuncao($1, $3, yylineno ); }
        | IDENTIFICADOR '(' ')' { $$ = new NChamadaFuncao($1, new ListaExpressao(), yylineno); }
        | INT_CONST { $$ = new NInteiro($1, yylineno);  }
        | CAR_CONST { $$ = new NCaracter($1, yylineno);  }
        | PALAVRA_LITERAL { $$ = new NPalavraLiteral($1, yylineno);  }
        | REAL_CONST { $$ = new NReal($1, yylineno); }
        | NOVA_LINHA {  $$ = new NNovaLinha(yylineno); }
        | '(' expressao ')' { $$ = $2; $$->linha = $1; }
        ;

lista_expr_vetor
        : '[' expressao ']' { $$ = new ListaExpressao(); $$->push_back($2); }
        | lista_expr_vetor '[' expressao ']' { $1->push_back($3); $$ = $1; }
        ;

expressao
        : lista_expressao  { $$ = new NListaExpressoes($1, yylineno); }
        ;

lista_expressao
        : expressao_atribuicao { $$ = new ListaExpressao(); $$->push_back($1); }
        | lista_expressao ',' expressao_atribuicao { $1->push_back($3); $$ = $1; }
        ;

%%

bool checa_vetor(ListaExpressao *dimensao, ListaExpressao *lista, int indice, int dim, int tam)
{
        if(lista->size()!=dim)
                return false;

        if(tam>1)
        {
                bool result = true;

                for(int i=0; i<dim; ++i)
                {
                        No * no = dynamic_cast<No*>(lista->at(i));
                        if(no->tipoNo()!=TipoNo::LISTA_INICIALIZADOR)
                                return false;
                        int valDim = dynamic_cast<NInteiro*>(dimensao->at(indice+1))->valor;
                        result &= checa_vetor(dimensao, dynamic_cast<NListaInicializador*>(lista->at(i))->expressoes, indice+1, valDim, tam-1);
                }

                return result;
        }

        return true;
}

void yyerror(NBloco * bloco, const char *s)
{
    QString erro;

    if(!erro_lexico)
    {
        CompInfo::err()<<"[ERRO SINTATICO] Erro junto ao token "<<ultimo_token<<" próximo a "<<yylineno<<"\n";
    }
    else
    {
        CompInfo::err()<<"[ERRO LEXICO] Erro junto ao token "<<ultimo_token<<" próximo a "<<yylineno<<"\n";
        erro_lexico = false;
    }
    erro_compilador = true;
}
