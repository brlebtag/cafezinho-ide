#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <QString>
#include "CelulaMemoria.h"
#include "arvore_abstrata.h"
#include "CompInfo.h"

namespace Sistema
{
    enum Comando
    {
        LIMPAR,
        NOVA_LINHA
    };
};

namespace TipoInstrucao
{
    enum TipoInstrucao
    {
        MOVE,
        MOVE_IM,
        ADC,
        ADC_IM,
        SUB,
        SUB_IM,
        MULT,
        MULT_IM,
        DIV,
        DIV_IM,
        CMP,
        CMP_IM,
        SALTO,
        SALTO_EQ,
        SALTO_MAIOR,
        SALTO_NAO_EQ,
        SALTO_MAIOR_EQ,
        SALTO_MENOR,
        SALTO_MENOR_EQ,
        PARAR,
        CHAMADA,
        LEITURA_INT,
        LEITURA_CAR,
        LEITURA_REAL,
        CARREGA,
        SALVA,
        E_BIT,
        E_BIT_IM,
        OU_BIT,
        OU_BIT_IM,
        XOR_BIT,
        XOR_BIT_IM,
        SHIFT_DIR,
        SHIFT_ESQ,
        LIG_MAIOR_QUE,
        LIG_MAIOR_QUE_IM,
        LIG_MENOR_QUE,
        LIG_MENOR_QUE_IM,
        LIG_MAIOR_EQ,
        LIG_MAIOR_EQ_IM,
        LIG_MENOR_EQ,
        LIG_MENOR_EQ_IM,
        LIG_EQ,
        LIG_EQ_IM,
        LIG_NAO_EQ,
        LIG_NAO_EQ_IM,
        NAO_BIT,
        NAO_BIT_IM,
        NADA,
        ESCRITA_PALAVRA,
        ESCRITA_CHAR,
        ESCRITA_CHAR_IM,
        ESCRITA_INT,
        ESCRITA_INT_IM,
        ESCRITA_DOUBLE,
        ESCRITA_DOUBLE_IM,
        RET,
        TROCA,
        RESTO,
        RESTO_IM,
        NEG,
        NEG_IM,
        BOOLEAN,
        POTENCIA,
        POTENCIA_IM,
        CAST,
        SISTEMA,
        DEBUG_PASSO,
        DEBUG_EMPILHA,
        DEBUG_DESEMPILHA,
        DEBUG_VAR_EMPILHA,
        DEBUG_VAR_DESEMPILHA
    };
};

using namespace std;

class MaquinaVirtual;

typedef CelulaMemoria Celula;

class Instrucao
{
public:
    Instrucao();
    virtual ~Instrucao();
    virtual void execute(MaquinaVirtual &vm) = 0;
    virtual TipoInstrucao::TipoInstrucao tipoInstucao()=0;
};

class IMove : public Instrucao
{
public:
    IMove(Celula &para, Celula &de);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula &registrador2;
};

class IMoveIm : public Instrucao
{
public:
    IMoveIm(Celula &para, Celula de);
    IMoveIm(Celula &para, char de);
    IMoveIm(Celula &para, int de);
    IMoveIm(Celula &para, double de);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula registrador2;
};

class ISalto : public Instrucao
{
public:
    ISalto(int &offset);
    virtual ~ISalto();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int &offset;
};

class IAdc: public Instrucao
{
public:
    IAdc(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ISub: public Instrucao
{
public:
    ISub(Celula &registrador, Celula  &operando1, Celula  &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IMult: public Instrucao
{
public:
    IMult(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IDiv: public Instrucao
{
public:
    IDiv(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ICmp: public Instrucao
{
public:
    ICmp(Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &operando1;
    Celula &operando2;
};

class ICmpIm: public Instrucao
{
public:
    ICmpIm(Celula &operando1, Celula operando2);
    ICmpIm(Celula &operando1, int operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &operando1;
    Celula operando2;
};

//Salto Igual
class ISaltoEq : public ISalto
{
public:
    ISaltoEq(int &offset);
    virtual ~ISaltoEq();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};
//Salto Nao Igual
class ISaltoNaoEq : public ISalto
{
public:
    ISaltoNaoEq(int &offset);
    virtual ~ISaltoNaoEq();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMaior : public ISalto
{
public:
    ISaltoMaior(int &offset);
    virtual ~ISaltoMaior();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMaiorEq : public ISalto
{
public:
    ISaltoMaiorEq(int &offset);
    virtual ~ISaltoMaiorEq();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMenor : public ISalto
{
public:
    ISaltoMenor(int &offset);
    virtual ~ISaltoMenor();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ISaltoMenorEq : public ISalto
{
public:
    ISaltoMenorEq(int &offset);
    virtual ~ISaltoMenorEq();
    virtual void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IParar : public Instrucao
{
public:
    IParar();
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IChamada : public ISalto
{
public:
    IChamada(int &offset);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class ILeituraInt : public Instrucao
{
public:
    ILeituraInt(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;

};

class ILeituraCar : public Instrucao
{
public:
    ILeituraCar(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class ILeituraReal : public Instrucao
{
public:
    ILeituraReal(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class ICarrega : public Instrucao
{
public:
    ICarrega(Celula &registrador, Celula &offset, int desl = 0);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class ISalva : public Instrucao
{
public:
    ISalva(Celula &registrador , Celula &offset, int desl = 0);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &offset;
    int desl;
};

class IEBit: public Instrucao
{
public:
    IEBit(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IEBitIm: public Instrucao
{
public:
    IEBitIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};


class IOuBit: public Instrucao
{
public:
    IOuBit(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IOuBitIm: public Instrucao
{
public:
    IOuBitIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IXorBit: public Instrucao
{
public:
    IXorBit(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IXorBitIm: public Instrucao
{
public:
    IXorBitIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IShiftDir: public Instrucao
{
public:
    IShiftDir(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IShiftEsq: public Instrucao
{
public:
    IShiftEsq(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class INaoBit: public Instrucao
{
public:
    INaoBit(Celula &registrador, Celula &operando1);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
};

class INaoBitIm: public Instrucao
{
public:
    INaoBitIm(Celula &registrador, Celula operando1);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula operando1;
};

class ILigMaiorQ: public Instrucao
{
public:
    ILigMaiorQ(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorQIm: public Instrucao
{
public:
    ILigMaiorQIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorQ: public Instrucao
{
public:
    ILigMenorQ(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorQIm: public Instrucao
{
public:
    ILigMenorQIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMaiorEq: public Instrucao
{
public:
    ILigMaiorEq(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMaiorEqIm: public Instrucao
{
public:
    ILigMaiorEqIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigMenorEq: public Instrucao
{
public:
    ILigMenorEq(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigMenorEqIm: public Instrucao
{
public:
    ILigMenorEqIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigEq: public Instrucao
{
public:
    ILigEq(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigEqIm: public Instrucao
{
public:
    ILigEqIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ILigNaoEq: public Instrucao
{
public:
    ILigNaoEq(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class ILigNaoEqIm: public Instrucao
{
public:
    ILigNaoEqIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INada: public Instrucao
{
public:
    INada();
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IEscritaPalavraIm : public Instrucao
{
public:
    IEscritaPalavraIm(QString *palavra);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    QString *palavra;
};

class IEscritaChar : public Instrucao
{
public:
    IEscritaChar(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaCharIm : public Instrucao
{
public:
    IEscritaCharIm(int m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int m;
};

class IEscritaInt : public Instrucao
{
public:
    IEscritaInt(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaIntIm : public Instrucao
{
public:
    IEscritaIntIm(int m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int m;
};

class IEscritaDouble : public Instrucao
{
public:
    IEscritaDouble(Celula &m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &m;
};

class IEscritaDoubleIm : public Instrucao
{
public:
    IEscritaDoubleIm(double m);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    double m;
};

class IAdcIm: public Instrucao
{
public:
    IAdcIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ISubIm: public Instrucao
{
public:
    ISubIm(Celula &registrador, Celula  &operando1, Celula  operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IMultIm: public Instrucao
{
public:
    IMultIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IDivIm: public Instrucao
{
public:
    IDivIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class IRet: public Instrucao
{
public:
    IRet(Celula &registrador);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
};

class ITroca: public Instrucao
{
public:
    ITroca(Celula &registrador1, Celula &registrador2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador1;
    Celula &registrador2;
};

class IResto: public Instrucao
{
public:
    IResto(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IRestoIm: public Instrucao
{
public:
    IRestoIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class INeg: public Instrucao
{
public:
    INeg(Celula &registrador, Celula &operando1);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
};

class INegIm: public Instrucao
{
public:
    INegIm(Celula &registrador, Celula operando1);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula operando1;
};

class IBoolean : public Instrucao
{
public:
    IBoolean(Celula &registrador);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
};

class IPotencia : public Instrucao
{
public:
    IPotencia(Celula &registrador, Celula &operando1, Celula &operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula &operando2;
};

class IPotenciaIm : public Instrucao
{
public:
    IPotenciaIm(Celula &registrador, Celula &operando1, Celula operando2);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Celula &registrador;
    Celula &operando1;
    Celula operando2;
};

class ICast : public Instrucao
{
public:
    ICast(Celula &registrador, TipoVariavel::TipoVariavel tipo);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    TipoVariavel::TipoVariavel tipo;
    Celula &registrador;
};

class ISistema: public Instrucao
{
public:
    ISistema(Sistema::Comando comando);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    Sistema::Comando comando;
};

//Instruções para Debug

class IDebugPasso : public Instrucao
{
public:
    IDebugPasso(int linha);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    int linha;
};

class IDebugEmpilhaExec : public Instrucao
{
public:
    IDebugEmpilhaExec();
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IDebugDesempilhaExec : public Instrucao
{
public:
    IDebugDesempilhaExec();
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
};

class IDebugVariavelEmpilha : public Instrucao
{
public:
    IDebugVariavelEmpilha(No* no, int offset, int profundidade, No* pno = NULL);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    No* no; //Nó que guarda a declaracao da variavel (pode ser local ou parametro)
    No* pno; //Declaracao da variavel vetorial que o parametro aponta...
    int offset;
    int profundidade;
};


class IDebugVariavelDesempilha : public Instrucao
{
public:
    IDebugVariavelDesempilha(No* no);
    void execute(MaquinaVirtual &vm);
    TipoInstrucao::TipoInstrucao tipoInstucao();
    No* no;
};

#endif // INSTRUCAO_H
