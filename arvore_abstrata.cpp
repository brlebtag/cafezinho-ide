#include "arvore_abstrata.h"

/********************* NO *************************/
No::No(int linha)
    : linha(linha) {}

No::~No() {}

TipoNo::TipoNo No::tipoNo()
{
    return TipoNo::NO;
}

/******************** Expressao **********************/

NExpressao::NExpressao(int linha)
    : No(linha) {}

NExpressao::NExpressao(TipoVariavel::TipoVariavel tipo, int linha)
    : No(linha), tipo(tipo) {}

NExpressao::~NExpressao() {}

TipoNo::TipoNo NExpressao::tipoNo()
{
    return TipoNo::EXPRESSAO;
}

/******************** Expressao **********************/

NInstrucao::NInstrucao(int linha)
    : No(linha) {}

NInstrucao::~NInstrucao() {}

TipoNo::TipoNo NInstrucao::tipoNo()
{
    return TipoNo::INSTRUCAO;
}

/******************** Inteiro ***********************/

NInteiro::NInteiro(int valor, int linha)
    : NExpressao(TipoVariavel::TIPO_INT, linha), valor(valor) {}

TipoNo::TipoNo NInteiro::tipoNo()
{
    return TipoNo::INTEIRO;
}

NInteiro::~NInteiro() {}

/****************** Caracter ************************/
NCaracter::NCaracter(int valor, int linha)
    : NExpressao(TipoVariavel::TIPO_CAR, linha), valor(valor) {}

TipoNo::TipoNo NCaracter::tipoNo()
{
    return TipoNo::CARACTER;
}

NCaracter::~NCaracter() {}

/******************* Palavra Literal *****************/
NPalavraLiteral::NPalavraLiteral(QString* valor, int linha)
    : NExpressao(TipoVariavel::TIPO_PALAVRA, linha), valor(valor) {}

TipoNo::TipoNo NPalavraLiteral::tipoNo()
{
    return TipoNo::PALAVRA_LITERAL;
}

NPalavraLiteral::~NPalavraLiteral() {}
/*************** Identificador **************************/

NIdentificador::NIdentificador(QString *nome, int linha)
    : NExpressao(linha), nome(nome) {}

TipoNo::TipoNo NIdentificador::tipoNo()
{
    return TipoNo::IDENTIFICADOR;
}

NIdentificador::~NIdentificador()
{
    if(nome!=0)
        delete nome;
}

/******************* Identificador Escalar ***************/
NIdentificadorEscalar::NIdentificadorEscalar(QString *nome, int linha)
    : NIdentificador(nome, linha) {}

TipoNo::TipoNo NIdentificadorEscalar::tipoNo()
{
    return TipoNo::IDENTIFICADOR_ESCALAR;
}

NIdentificadorEscalar::~NIdentificadorEscalar() {}

/******************* Identificador Vetorial ***************/
NIdentificadorVetorial::NIdentificadorVetorial(QString *nome, ListaExpressao *indice, int linha)
    : NIdentificador(nome, linha), indice(indice) {}

TipoNo::TipoNo NIdentificadorVetorial::tipoNo()
{
    return TipoNo::IDENTIFICADOR_VETORIAL;
}

NIdentificadorVetorial::~NIdentificadorVetorial()
{
    if(indice!=0)
    {
        for(ListaExpressao::iterator it = indice->begin(); it!= indice->end(); ++it)
            delete (*it);
        delete indice;
    }

}

/*************** Declaracao Variavel ************************/
NDeclaracaoVariavel::NDeclaracaoVariavel(TipoVariavel::TipoVariavel tipo, QString* nome, int linha)
    : NInstrucao(linha), tipo(tipo), nome(nome) { }

NDeclaracaoVariavel::NDeclaracaoVariavel(QString* nome, int linha)
    : NInstrucao(linha), nome(nome) { }

TipoNo::TipoNo NDeclaracaoVariavel::tipoNo()
{
    return TipoNo::DECLARACAO_VARIAVEL;
}

NDeclaracaoVariavel::~NDeclaracaoVariavel()
{
    if(nome!=0)
        delete nome;
}

/*************** Declaracao Variavel Escalar ******************/

NDeclVarEscalar::NDeclVarEscalar(TipoVariavel::TipoVariavel tipo, QString* nome, int linha)
    : NDeclaracaoVariavel(tipo, nome, linha) {}

NDeclVarEscalar::NDeclVarEscalar(QString* nome, int linha)
    : NDeclaracaoVariavel(nome, linha) {}

TipoNo::TipoNo NDeclVarEscalar::tipoNo()
{
    return TipoNo::DECLARACAO_VARIAVEL_ESCALAR;
}

NDeclVarEscalar::~NDeclVarEscalar() {}

/*************** Declaracao Variavel Vetorial *****************/

NDeclVarVetorial::NDeclVarVetorial(TipoVariavel::TipoVariavel tipo, QString* nome, int linha, bool eParametro)
    : NDeclaracaoVariavel(tipo, nome, linha), eParametro(eParametro) {}

NDeclVarVetorial::NDeclVarVetorial(TipoVariavel::TipoVariavel tipo, QString* nome, ListaExpressao *dimensoes, int linha, bool eParametro)
    : NDeclaracaoVariavel(tipo, nome, linha), dimensoes(dimensoes), eParametro(eParametro) {}

NDeclVarVetorial::NDeclVarVetorial(QString* nome, ListaExpressao *dimensoes, int linha, bool eParametro)
    : NDeclaracaoVariavel(nome, linha), dimensoes(dimensoes), eParametro(eParametro) {}

TipoNo::TipoNo NDeclVarVetorial::tipoNo()
{
    return TipoNo::DECLARACAO_VARIAVEL_VETORIAL;
}

NDeclVarVetorial::~NDeclVarVetorial()
{
    if(dimensoes!=0)
    {
        for(ListaExpressao::iterator it = dimensoes->begin(); it!= dimensoes->end(); ++it)
            delete (*it);
        delete dimensoes;
    }

}

/*************** Bloco *****************/
NBloco::NBloco(int linha)
    :NInstrucao(linha), instrucoes(0) {}

TipoNo::TipoNo NBloco::tipoNo()
{
    return TipoNo::BLOCO;
}

NBloco::~NBloco()
{
    if(instrucoes!=0)
    {
        for(ListaInstrucao::iterator it = instrucoes->begin(); it!= instrucoes->end(); ++it)
            delete (*it);
        delete instrucoes;
    }
}

/*************** Chamada Funcao *****************/
NChamadaFuncao::NChamadaFuncao( QString* nome, ListaExpressao* argumentos, int linha)
    : NExpressao(linha), nome(nome), argumentos(argumentos) {}

NChamadaFuncao::NChamadaFuncao( QString* nome, int linha)
    : NExpressao(linha), nome(nome) {}

TipoNo::TipoNo NChamadaFuncao::tipoNo()
{
    return TipoNo::CHAMADA_FUNCAO;
}

NChamadaFuncao::~NChamadaFuncao()
{
    if(nome!=0)
        delete nome;

    if(argumentos)
    {
        for(ListaExpressao::iterator it = argumentos->begin(); it!= argumentos->end(); ++it)
            delete (*it);
        delete argumentos;
    }

}

/************** Declaracao de Funcao ****************/
NDeclaracaoFuncao::NDeclaracaoFuncao()
    : NInstrucao(0), nome(0), parametros(0), bloco(0),possuiRetorno(false) { }
NDeclaracaoFuncao::NDeclaracaoFuncao(TipoVariavel::TipoVariavel tipo, QString* nome, ListaVariavel* parametros, NBloco* bloco, int linha)
    : NInstrucao(linha), nome(nome), parametros(parametros), bloco(bloco),possuiRetorno(false) { }
NDeclaracaoFuncao::NDeclaracaoFuncao(ListaVariavel* parametros, NBloco* bloco, int linha)
    : NInstrucao(linha), parametros(parametros), bloco(bloco),possuiRetorno(false) { }
NDeclaracaoFuncao::NDeclaracaoFuncao(QString * nome, ListaVariavel * parametros, int linha)
    : NInstrucao(linha), nome(nome), parametros(parametros),possuiRetorno(false) { }
NDeclaracaoFuncao::~NDeclaracaoFuncao()
{
    if(nome!=0)
        delete nome;
    if(parametros!=0)
    {
        for(ListaVariavel::iterator it = parametros->begin(); it!= parametros->end(); ++it)
            delete (*it);
        delete parametros;
    }
    if(bloco!=0)
        delete bloco;
}
TipoNo::TipoNo NDeclaracaoFuncao::tipoNo()
{
    return TipoNo::DECLARACAO_FUNCAO;
}

/***************** Instrucao Expressao ***************/
NInstrucaoExpressao::NInstrucaoExpressao(NExpressao* expressao, int linha)
    : NInstrucao(linha), expressao(expressao) { }
NInstrucaoExpressao::~NInstrucaoExpressao()
{
    if(expressao!=0)
        delete expressao;
}

TipoNo::TipoNo NInstrucaoExpressao::tipoNo()
{
    return TipoNo::INSTRUCAO_EXPRESSAO;
}

/******************** Atribuicao **********************/
NAtribuicao::NAtribuicao(NExpressao* lhs, Operador::Operador op, NExpressao* rhs, int linha)
    : NExpressao(linha), lhs(lhs), op(op), rhs(rhs) { }
NAtribuicao::~NAtribuicao()
{
    if(lhs!=0)
        delete lhs;
    if(rhs!=0)
        delete rhs;
}

TipoNo::TipoNo NAtribuicao::tipoNo()
{
    return TipoNo::ATRIBUICAO;
}

/******************* Operacao Binaria ********************/
NOperacaoBinaria::NOperacaoBinaria(NExpressao* lhs, Operador::Operador op, NExpressao* rhs, int linha)
    : NExpressao(linha), lhs(lhs), rhs(rhs), op(op) {}
NOperacaoBinaria::~NOperacaoBinaria()
{
    if(lhs!=0)
        delete lhs;
    if(rhs!=0)
        delete rhs;
}
TipoNo::TipoNo NOperacaoBinaria::tipoNo()
{
    return TipoNo::OPERACAO_BINARIA;
}

/******************** Operacao Unaria ******************/
NOperacaoUnaria::NOperacaoUnaria(NExpressao* rhs, Operador::Operador op, int linha)
    : NExpressao(linha), rhs(rhs), op(op) { }
NOperacaoUnaria::~NOperacaoUnaria()
{
    if(rhs!=0)
        delete rhs;
}
TipoNo::TipoNo NOperacaoUnaria::tipoNo()
{
    return TipoNo::OPERACAO_UNARIA;
}

/******************* Operacao Terciaria ***************/
NOperacaoTerciaria::NOperacaoTerciaria(NExpressao* expressao, NExpressao* ifExpr, NExpressao* elsExpr, int linha)
    : NExpressao(linha), expressao(expressao), ifExpr(ifExpr), elsExpr(elsExpr) { }
NOperacaoTerciaria::~NOperacaoTerciaria()
{
    if(expressao!=0)
        delete expressao;
    if(ifExpr!=0)
        delete ifExpr;
    if(elsExpr!=0)
        delete elsExpr;
}
TipoNo::TipoNo NOperacaoTerciaria::tipoNo()
{
    return TipoNo::OPERACAO_TERCIARIA;
}

/**************** Cast ************************/
NCast::NCast(NExpressao* expressao, TipoVariavel::TipoVariavel tipo, int linha)
    :NExpressao(linha), expressao(expressao), tipo(tipo) { }
NCast::~NCast()
{
    if(expressao!=0)
        delete expressao;
}
TipoNo::TipoNo NCast::tipoNo()
{
    return TipoNo::CAST;
}

/****************** Retorne*******************/
NRetorne::NRetorne(NExpressao* expressao, int linha)
    : NInstrucao(linha), expressao(expressao) { }
TipoNo::TipoNo NRetorne::tipoNo()
{
    return TipoNo::RETORNE;
}
NRetorne::~NRetorne ()
{
    if(expressao!=0)
        delete expressao;
}

/**************** Leia ***********************/
NLeia::NLeia(NExpressao* expressao, int linha)
    : NInstrucao(linha), expressao(expressao) { }
TipoNo::TipoNo NLeia::tipoNo()
{
    return TipoNo::LEIA;
}
NLeia::~NLeia ()
{
    if(expressao!=0)
        delete expressao;
}

/*************** Escreva *********************/
NEscreva::NEscreva(NExpressao* expressao, int linha)
    : NInstrucao(linha), expressao(expressao) { }
TipoNo::TipoNo NEscreva::tipoNo()
{
    return TipoNo::ESCREVA;
}
NEscreva::~NEscreva ()
{
    if(expressao!=0)
        delete expressao;
}

/************** Nova Linha ******************/
NNovaLinha::NNovaLinha(int linha)
    : NExpressao(TipoVariavel::TIPO_NOVALINHA, linha), valor(new QString("\n")) { }
TipoNo::TipoNo NNovaLinha::tipoNo()
{
    return TipoNo::NOVA_LINHA;
}
NNovaLinha::~NNovaLinha()
{
    delete valor;
}

/************** Se *************************/
NSe::NSe(NExpressao* expressao, NInstrucao * instrucao, int linha)
    : NInstrucao(linha), expressao(expressao), instrucao(instrucao) { }
TipoNo::TipoNo NSe::tipoNo()
{
    return TipoNo::SE;
}
NSe::~NSe()
{
    if(expressao!=0)
        delete expressao;
    if(instrucao!=0)
        delete instrucao;
}

/************** Senao *********************/
NSeSenao::NSeSenao(NExpressao* expressao, NInstrucao * instrucaoSe, NInstrucao *instrucaoSenao, int linha)
    :NInstrucao(linha), expressao(expressao), instrucaoSe(instrucaoSe), instrucaoSenao(instrucaoSenao){ }
TipoNo::TipoNo NSeSenao::tipoNo()
{
    return TipoNo::SE_SENAO;
}
NSeSenao::~NSeSenao()
{
    if(expressao!=0)
        delete expressao;
    if(instrucaoSe!=0)
        delete instrucaoSe;
    if(instrucaoSenao!=0)
        delete instrucaoSenao;
}

/********** Enquanto ****************/
NEnquanto::NEnquanto(NExpressao* expressao, NInstrucao* instrucao, int linha)
    : NInstrucao(linha), expressao(expressao), instrucao(instrucao){ }
TipoNo::TipoNo NEnquanto::tipoNo()
{
    return TipoNo::ENQUANTO;
}
NEnquanto::~NEnquanto()
{
    if(expressao!=0)
        delete expressao;
    if(instrucao!=0)
        delete instrucao;
}
/************* Lista Expressoes **********/
NListaExpressoes::NListaExpressoes(ListaExpressao* expressoes, int linha)
    : NExpressao(linha), expressoes(expressoes) { }
NListaExpressoes::~NListaExpressoes()
{
    if(expressoes!=0)
    {
        for(ListaExpressao::iterator it = expressoes->begin(); it!= expressoes->end(); ++it)
                delete (*it);

        delete expressoes;
    }
}
TipoNo::TipoNo NListaExpressoes::tipoNo()
{
    return TipoNo::LISTA_EXPRESSOES;
}

/**************** Real *****************/
NReal::NReal(double valor, int linha)
    : NExpressao(TipoVariavel::TIPO_REAL, linha), valor(valor) { }
TipoNo::TipoNo NReal::tipoNo()
{
    return TipoNo::REAL;
}
NReal::~NReal() { }

/************** Inicializador Vetor ************/

NInicializadorVetor::NInicializadorVetor(QString *nome, ListaExpressao *init, int linha)
    : NInstrucao (linha), nome(nome), init(init) { }
NInicializadorVetor::~NInicializadorVetor()
{
    if(init!=0)
    {
        for(ListaExpressao::iterator it = init->begin(); it!= init->end(); ++it)
            delete (*it);
        delete init;
    }
    if(nome!=0)
        delete nome;

}
TipoNo::TipoNo NInicializadorVetor::tipoNo()
{
    return TipoNo::INICIALIZADOR_VETOR;
}

/******************** Lista Inicializador *************/
NListaInicializador::NListaInicializador(ListaExpressao* expressoes, int linha)
    : NExpressao(linha), expressoes(expressoes) { }
NListaInicializador::~NListaInicializador()
{
    if(expressoes!=0)
    {
        for(ListaExpressao::iterator it = expressoes->begin(); it!= expressoes->end(); ++it)
            delete (*it);
        delete expressoes;
    }
}
TipoNo::TipoNo NListaInicializador::tipoNo()
{
    return TipoNo::LISTA_INICIALIZADOR;
}

/***************** Terminar ***************/
NTerminar::NTerminar(int linha)
    :NInstrucao(linha) { }

NTerminar::~NTerminar() { }

TipoNo::TipoNo NTerminar::tipoNo()
{
    return TipoNo::TERMINAR;
}

/************** Limpar ********************/
NLimpar::NLimpar(int linha)
    :NInstrucao(linha) { }

NLimpar::~NLimpar() { }

TipoNo::TipoNo NLimpar::tipoNo()
{
    return TipoNo::LIMPAR;
}
