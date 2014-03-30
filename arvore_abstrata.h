#ifndef ARVORE_ABSTRATA_H
#define ARVORE_ABSTRATA_H

#include <QList>
#include <QString>

class NInstrucao;
class NExpressao;
class NDeclaracaoVariavel;

#ifndef __LISTA__
#define __LISTA__
typedef QList<NInstrucao*> ListaInstrucao;
typedef QList<NExpressao*> ListaExpressao;
typedef QList<NDeclaracaoVariavel*> ListaVariavel;
#endif


namespace TipoVariavel
{
    enum TipoVariavel
    {
        TIPO_ERRO,
        TIPO_CAR,
        TIPO_INT,
        TIPO_REAL,
        TIPO_PALAVRA,
        TIPO_NULO,
        TIPO_NOVALINHA
    };
}

namespace Operador
{
    enum Operador
    {
        ERR_OP,
        EQ_OP,
        OU_OP,
        E_OP,
        OU_BIT_OP,
        E_BIT_OP,
        XOR_BIT_OP,
        NE_OP,
        BT_OP,
        LT_OP,
        SOM_OP,
        SUB_OP,
        MULT_OP,
        DIV_OP,
        REST_OP,
        LE_OP,
        GE_OP,
        ESQ_OP,
        DIR_OP,
        POT_OP,
        INC_POS_OP,
        DEC_POS_OP,
        INC_PRE_OP,
        DEC_PRE_OP,
        MULT_ATRIBUICAO,
        DIV_ATRIBUICAO,
        MOD_ATRIBUICAO,
        ADICAO_ATRIBUICAO,
        SUBTRACAO_ATRIBUICAO,
        ESQ_ATRIBUICAO,
        DIR_ATRIBUICAO,
        E_ATRIBUICAO,
        XOR_ATRIBUICAO,
        OU_ATRIBUICAO,
        POT_ATRIBUICAO,
        ATRIBUICAO_OP,
        MIN_OP, // SINAL DE SUBSTRACAO -
        NEG_OP //SINAL ! OU ~

    };
}

namespace TipoNo
{
    enum TipoNo
    {
        NO,
        EXPRESSAO,
        INSTRUCAO,
        INTEIRO,
        CARACTER,
        REAL,
        PALAVRA_LITERAL,
        IDENTIFICADOR,
        IDENTIFICADOR_ESCALAR,
        IDENTIFICADOR_VETORIAL,
        DECLARACAO_VARIAVEL,
        DECLARACAO_VARIAVEL_ESCALAR,
        DECLARACAO_VARIAVEL_VETORIAL,
        BLOCO,
        CHAMADA_FUNCAO,
        DECLARACAO_FUNCAO,
        INSTRUCAO_EXPRESSAO,
        ATRIBUICAO,
        OPERACAO_BINARIA,
        OPERACAO_UNARIA,
        OPERACAO_TERCIARIA,
        RETORNE,
        LEIA,
        ESCREVA,
        NOVA_LINHA,
        SE,
        SE_SENAO,
        ENQUANTO,
        CAST,
        LISTA_EXPRESSOES,
        INICIALIZADOR_VETOR,
        LISTA_INICIALIZADOR,
        TERMINAR,
        LIMPAR
    };
}

class No
{
public:
    int linha;
    No(int linha = 0);
    virtual ~No();
    virtual TipoNo::TipoNo tipoNo();
};


class NExpressao : public No
{
public:
    TipoVariavel::TipoVariavel tipo;
    NExpressao(int linha = 0);
    NExpressao(TipoVariavel::TipoVariavel tipo, int linha = 0);
    virtual ~NExpressao();
    virtual TipoNo::TipoNo tipoNo();
};

class NInstrucao : public No
{
public:
    NInstrucao(int linha = 0);
    virtual ~NInstrucao();
    virtual TipoNo::TipoNo tipoNo();
};

class NInteiro : public NExpressao
{
public:
    int valor;
    NInteiro(int valor, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NInteiro();
};

class NCaracter : public NExpressao
{
public:
    int valor;
    NCaracter(int valor, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NCaracter();
};

class NReal : public NExpressao
{
public:
    double valor;
    NReal(double valor, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NReal();
};

class NPalavraLiteral : public NExpressao
{
public:
    QString *valor;
    NPalavraLiteral(QString* valor = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NPalavraLiteral();
};

class NIdentificador : public NExpressao
{
public:
    QString *nome;
    NIdentificador(QString *nome = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NIdentificador();
};

class NIdentificadorEscalar : public NIdentificador
{
public:
    NIdentificadorEscalar(QString *nome = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NIdentificadorEscalar();
};

class NIdentificadorVetorial : public NIdentificador
{
public:
    ListaExpressao* indice;
    NIdentificadorVetorial(QString *nome = 0, ListaExpressao *indice = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NIdentificadorVetorial ();
};

class NDeclaracaoVariavel : public NInstrucao
{
public:
    TipoVariavel::TipoVariavel tipo;
    QString* nome;
    NDeclaracaoVariavel(TipoVariavel::TipoVariavel tipo, QString* nome = 0, int linha = 0);
    NDeclaracaoVariavel(QString* nome = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NDeclaracaoVariavel();
};

class NDeclVarEscalar : public NDeclaracaoVariavel
{
public:
    NDeclVarEscalar(TipoVariavel::TipoVariavel tipo, QString* nome = 0, int linha = 0);
    NDeclVarEscalar(QString* nome = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NDeclVarEscalar();
};

class NDeclVarVetorial : public NDeclaracaoVariavel
{
public:
    ListaExpressao *dimensoes;
    bool eParametro;
    NDeclVarVetorial(TipoVariavel::TipoVariavel tipo, QString* nome = 0, int linha = 0, bool eParametro = false);
    NDeclVarVetorial(TipoVariavel::TipoVariavel tipo, QString* nome = 0, ListaExpressao *dimensoes = 0, int linha = 0, bool eParametro = false);
    NDeclVarVetorial(QString* nome = 0, ListaExpressao *dimensoes = 0, int linha = 0, bool eParametro = false);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NDeclVarVetorial();
};


class NBloco : public NInstrucao
{
public:
    ListaInstrucao* instrucoes;
    NBloco(int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NBloco();
};

class NChamadaFuncao : public NExpressao
{
public:
    QString* nome;
    ListaExpressao* argumentos;
    NChamadaFuncao( QString* nome = 0, ListaExpressao* argumentos = 0, int linha = 0);
    NChamadaFuncao( QString* nome = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NChamadaFuncao();
};

class NDeclaracaoFuncao : public NInstrucao
{
public:
    TipoVariavel::TipoVariavel tipo;
    QString* nome;
    ListaVariavel* parametros;
    NBloco* bloco;
    bool possuiRetorno;
    NDeclaracaoFuncao(TipoVariavel::TipoVariavel tipo, QString* nome = 0, ListaVariavel* parametros = 0, NBloco* bloco = 0, int linha = 0);
    NDeclaracaoFuncao(ListaVariavel* parametros = 0, NBloco* bloco = 0, int linha = 0);
    NDeclaracaoFuncao(QString* nome = 0, ListaVariavel* parametros = 0, int linha = 0);
    virtual ~NDeclaracaoFuncao();
    virtual TipoNo::TipoNo tipoNo();
};


class NInstrucaoExpressao : public NInstrucao
{
public:
    NExpressao* expressao;
    NInstrucaoExpressao(NExpressao* expressao = 0, int linha = 0);
    virtual ~NInstrucaoExpressao();
    virtual TipoNo::TipoNo tipoNo();
};

class NAtribuicao : public NExpressao
{
public:
    NExpressao* lhs;
    NExpressao* rhs;
    Operador::Operador op;
    NAtribuicao(NExpressao* lhs = 0, Operador::Operador op = Operador::ERR_OP, NExpressao* rhs = 0, int linha = 0);
    virtual ~NAtribuicao();
    virtual TipoNo::TipoNo tipoNo();
};

class NOperacaoBinaria : public NExpressao
{
public:
    Operador::Operador op;
    NExpressao* lhs;
    NExpressao* rhs;
    NOperacaoBinaria(NExpressao* lhs = 0, Operador::Operador op = Operador::ERR_OP, NExpressao* rhs = 0, int linha = 0);
    virtual ~NOperacaoBinaria();
    virtual TipoNo::TipoNo tipoNo();
};

class NOperacaoUnaria : public NExpressao
{
public:
    Operador::Operador op;
    NExpressao* rhs;
    NOperacaoUnaria(NExpressao* rhs = 0, Operador::Operador op = Operador::ERR_OP, int linha = 0);
    virtual ~NOperacaoUnaria();
    virtual TipoNo::TipoNo tipoNo();
};

class NOperacaoTerciaria : public NExpressao
{
public:
    NExpressao* expressao;
    NExpressao* ifExpr;
    NExpressao* elsExpr;
    NOperacaoTerciaria(NExpressao* expressao = 0, NExpressao* ifExpr = 0, NExpressao* elsExpr = 0, int linha = 0);
    virtual ~NOperacaoTerciaria();
    virtual TipoNo::TipoNo tipoNo();
};


class NCast : public NExpressao
{
public:
    NExpressao* expressao;
    TipoVariavel::TipoVariavel tipo;
    NCast(NExpressao* expressao = 0, TipoVariavel::TipoVariavel tipo = TipoVariavel::TIPO_ERRO, int linha = 0);
    virtual ~NCast();
    virtual TipoNo::TipoNo tipoNo();
};

class NListaExpressoes : public NExpressao
{
public:
    ListaExpressao* expressoes;
    NListaExpressoes(ListaExpressao* expressoes = 0, int linha = 0);
    virtual ~NListaExpressoes();
    virtual TipoNo::TipoNo tipoNo();
};

class NRetorne : public NInstrucao
{
public:
    NExpressao* expressao;
    NRetorne(NExpressao* expressao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NRetorne ();
};

class NLeia : public NInstrucao
{
public:
    NExpressao* expressao;
    NLeia(NExpressao* expressao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NLeia ();
};

class NEscreva : public NInstrucao
{
public:
    NExpressao* expressao;
    NEscreva(NExpressao* expressao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NEscreva ();
};

class NNovaLinha : public NExpressao
{
public:
    QString *valor;
    NNovaLinha(int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NNovaLinha();
};

class NSe : public NInstrucao
{
public:
    NExpressao* expressao;
    NInstrucao *instrucao;
    NSe(NExpressao* expressao = 0, NInstrucao * instrucao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NSe();
};

class NSeSenao : public NInstrucao
{
public:
    NExpressao* expressao;
    NInstrucao *instrucaoSe;
    NInstrucao *instrucaoSenao;
    NSeSenao(NExpressao* expressao = 0, NInstrucao * instrucaoSe = 0, NInstrucao *instrucaoSenao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NSeSenao();
};

class NEnquanto : public NInstrucao
{
public:
    NExpressao* expressao;
    NInstrucao* instrucao;
    NEnquanto(NExpressao* expressao = 0, NInstrucao* instrucao = 0, int linha = 0);
    virtual TipoNo::TipoNo tipoNo();
    virtual ~NEnquanto();
};


class NInicializadorVetor : public NInstrucao
{
public:
    QString *nome;
    ListaExpressao *init;
    NInicializadorVetor(QString *nome = 0, ListaExpressao *init = 0, int linha = 0);
    virtual ~NInicializadorVetor();
    virtual TipoNo::TipoNo tipoNo();
};

class NListaInicializador : public NExpressao
{
public:
    ListaExpressao* expressoes;
    NListaInicializador(ListaExpressao* expressoes = 0, int linha = 0);
    virtual ~NListaInicializador();
    virtual TipoNo::TipoNo tipoNo();
};

class NTerminar : public NInstrucao
{
public:
    NTerminar(int linha = 0);
    virtual ~NTerminar();
    virtual TipoNo::TipoNo tipoNo();
};

class NLimpar : public NInstrucao
{
public:
    NLimpar(int linha = 0);
    virtual ~NLimpar();
    virtual TipoNo::TipoNo tipoNo();
};

#endif // ARVORE_ABSTRATA_H
