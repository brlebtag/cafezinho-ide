#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <CelulaMemoria.h>
#include <QString>

class MaquinaVirtual;

class Instrucao
{
public:
    Instrucao(MaquinaVirtual &vm);
    virtual ~Instrucao();
    virtual void execute() = 0;
protected:
    MaquinaVirtual &vm;
};

class IMove : public Instrucao
{
public:
    IMove(MaquinaVirtual &vm, int &para, int &de);
    void execute();
    int &registrador1;
    int &registrador2;
};

class ISalto : public Instrucao
{
public:
    ISalto(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class IAdi: public Instrucao
{
public:
    IAdi(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2);
    void execute();
    CelulaMemoria &registrador;
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class ISub: public Instrucao
{
public:
    ISub(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria  &operando1, CelulaMemoria  &operando2);
    void execute();
    CelulaMemoria &registrador;
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class IMult: public Instrucao
{
public:
    IMult(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2);
    void execute();
    CelulaMemoria &registrador;
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class IDiv: public Instrucao
{
public:
    IDiv(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2);
    void execute();
    CelulaMemoria &registrador;
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class IPot: public Instrucao
{
public:
    IPot(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2);
    void execute();
    CelulaMemoria &registrador;
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class ICmp: public Instrucao
{
public:
    ICmp(MaquinaVirtual &vm, CelulaMemoria &operando1, CelulaMemoria &operando2);
    void execute();
    CelulaMemoria &operando1;
    CelulaMemoria &operando2;
};

class ISaltoEq : public Instrucao
{
public:
    ISaltoEq(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class ISaltoMaior : public Instrucao
{
public:
    ISaltoMaior(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class ISaltoMaiorEq : public Instrucao
{
public:
    ISaltoMaiorEq(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class ISaltoMenor : public Instrucao
{
public:
    ISaltoMenor(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class ISaltoMenorEq : public Instrucao
{
public:
    ISaltoMenorEq(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class IAloca : public Instrucao
{
public:
    IAloca(MaquinaVirtual &vm, int quantidade);
    void execute();
    int quantidade;
};

class IEmpilha : public Instrucao
{
public:
    IEmpilha(MaquinaVirtual &vm, CelulaMemoria m);
    void execute();
    CelulaMemoria m;
};

class IDesempilha : public Instrucao
{
public:
    IDesempilha(MaquinaVirtual &vm);
    void execute();
};


class IParar : public Instrucao
{
public:
    IParar(MaquinaVirtual &vm);
    void execute();
};

class IChamada : public Instrucao
{
public:
    IChamada(MaquinaVirtual &vm, int offset);
    void execute();
    int offset;
};

class IEscrita : public Instrucao
{
public:
    IEscrita(MaquinaVirtual &vm, CelulaMemoria m);
    void execute();
    CelulaMemoria m;
};

class ILeituraInt : public Instrucao
{
public:
    ILeituraInt(MaquinaVirtual &vm, CelulaMemoria &m);
    void execute();
    CelulaMemoria &m;
};

class ILeituraCar : public Instrucao
{
public:
    ILeituraCar(MaquinaVirtual &vm, CelulaMemoria &m);
    void execute();
    CelulaMemoria &m;
};

class ILeituraReal : public Instrucao
{
public:
    ILeituraReal(MaquinaVirtual &vm, CelulaMemoria& m);
    void execute();
    CelulaMemoria &m;
};


#endif // INSTRUCAO_H
