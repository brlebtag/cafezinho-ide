#include "Instrucao.h"
#include "MaquinaVirtual.h"

Instrucao::Instrucao() { }

Instrucao::~Instrucao() { }

IMove::IMove(Celula& para, Celula & de)
    : registrador1(para), registrador2(de)
{
}

void IMove::execute(MaquinaVirtual &vm)
{
    registrador1 = registrador2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMove::tipoInstucao()
{
    return TipoInstrucao::MOVE;
}

IMoveIm::IMoveIm(Celula &para, Celula de)
    : registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(Celula &para, char de)
    : registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(Celula &para, int de)
    : registrador1(para), registrador2(de) { }

IMoveIm::IMoveIm(Celula &para, double de)
    : registrador1(para), registrador2(de) { }

void IMoveIm::execute(MaquinaVirtual &vm)
{
    registrador1 = registrador2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMoveIm::tipoInstucao()
{
    return TipoInstrucao::MOVE_IM;
}

ISalto::ISalto(int &offset)
    : offset(offset) { }


ISalto::~ISalto()
{

}

void ISalto::execute(MaquinaVirtual &vm)
{
    vm.pc = offset;
}

TipoInstrucao::TipoInstrucao ISalto::tipoInstucao()
{
    return TipoInstrucao::SALTO;
}

IAdc::IAdc(Celula& registrador, Celula& operando1, Celula& operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IAdc::execute(MaquinaVirtual &vm)
{
    registrador = operando1 + operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IAdc::tipoInstucao()
{
    return TipoInstrucao::ADC;
}

ISub::ISub(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void ISub::execute(MaquinaVirtual &vm)
{
    registrador = operando1 - operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISub::tipoInstucao()
{
    return TipoInstrucao::SUB;
}


IMult::IMult(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IMult::execute(MaquinaVirtual &vm)
{
    registrador = operando1 * operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMult::tipoInstucao()
{
    return TipoInstrucao::MULT;
}


IDiv::IDiv(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IDiv::execute(MaquinaVirtual &vm)
{
    if(operando2==0)
    {
        vm.msgErro("ERRO DIVISAO POR ZERO\n");
        vm.erf = true;
        return;
    }
    registrador = operando1 / operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDiv::tipoInstucao()
{
    return TipoInstrucao::DIV;
}


ICmp::ICmp(Celula &operando1, Celula &operando2)
    : operando1(operando1), operando2(operando2)
{
}

void ICmp::execute(MaquinaVirtual &vm)
{
    if(operando1 > operando2)
    {
        vm.bf = true;
        vm.sf = false;
        vm.ef = false;
    }
    else if(operando1 < operando2)
    {
        vm.bf = false;
        vm.sf = true;
        vm.ef = false;
    }
    else
    {
        vm.bf = false;
        vm.sf = false;
        vm.ef = true;
    }
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICmp::tipoInstucao()
{
    return TipoInstrucao::CMP;
}

ICmpIm::ICmpIm(Celula &operando1, Celula operando2)
    : operando1(operando1), operando2(operando2) { }
ICmpIm::ICmpIm(Celula &operando1, int operando2)
    : operando1(operando1), operando2(operando2) { }

void ICmpIm::execute(MaquinaVirtual &vm)
{
    if(operando1 > operando2)
    {
        vm.bf = true;
        vm.sf = false;
        vm.ef = false;
    }
    else if(operando1 < operando2)
    {
        vm.bf = false;
        vm.sf = true;
        vm.ef = false;
    }
    else
    {
        vm.bf = false;
        vm.sf = false;
        vm.ef = true;
    }
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICmpIm::tipoInstucao()
{
    return TipoInstrucao::CMP_IM;
}

ISaltoEq::ISaltoEq(int &offset)
    : ISalto(offset) { }

ISaltoEq::~ISaltoEq() { }

void ISaltoEq::execute(MaquinaVirtual &vm)
{
    if(vm.ef)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_EQ;
}

ISaltoMaior::ISaltoMaior(int &offset)
    : ISalto(offset)
{
}

ISaltoMaior::~ISaltoMaior()
{
}

void ISaltoMaior::execute(MaquinaVirtual &vm)
{
    if(vm.bf)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoMaior::tipoInstucao()
{
    return TipoInstrucao::SALTO_MAIOR;
}

ISaltoNaoEq::ISaltoNaoEq(int &offset)
    : ISalto(offset)
{

}
ISaltoNaoEq::~ISaltoNaoEq()
{

}
void ISaltoNaoEq::execute(MaquinaVirtual &vm)
{
    if(!vm.ef)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoNaoEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_NAO_EQ;
}

ISaltoMaiorEq::ISaltoMaiorEq(int &offset)
    : ISalto(offset)
{
}

ISaltoMaiorEq::~ISaltoMaiorEq()
{
}

void ISaltoMaiorEq::execute(MaquinaVirtual &vm)
{
    if(vm.bf||vm.ef)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoMaiorEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_MAIOR_EQ;
}

ISaltoMenor::ISaltoMenor(int &offset)
    : ISalto(offset)
{
}

ISaltoMenor::~ISaltoMenor()
{
}


void ISaltoMenor::execute(MaquinaVirtual &vm)
{
    if(vm.sf)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoMenor::tipoInstucao()
{
    return TipoInstrucao::SALTO_MENOR;
}

ISaltoMenorEq::ISaltoMenorEq(int &offset)
    : ISalto(offset)
{
}

ISaltoMenorEq::~ISaltoMenorEq()
{
}

void ISaltoMenorEq::execute(MaquinaVirtual &vm)
{
    if(vm.sf||vm.ef)
        ISalto::execute(vm);
    else
        ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISaltoMenorEq::tipoInstucao()
{
    return TipoInstrucao::SALTO_MENOR_EQ;
}

IParar::IParar() { }

void IParar::execute(MaquinaVirtual &vm)
{
    vm.parar();
}

TipoInstrucao::TipoInstrucao IParar::tipoInstucao()
{
    return TipoInstrucao::PARAR;
}

IChamada::IChamada(int &offset)
    : ISalto(offset) {}

void IChamada::execute(MaquinaVirtual &vm)
{
    vm.er = vm.pc + 1;
    ISalto::execute(vm);
}

TipoInstrucao::TipoInstrucao IChamada::tipoInstucao()
{
    return TipoInstrucao::CHAMADA;
}

ILeituraInt::ILeituraInt(Celula &m)
    : m(m)
{
}

void ILeituraInt::execute(MaquinaVirtual &vm)
{
    m = vm.leInt();
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILeituraInt::tipoInstucao()
{
    return TipoInstrucao::LEITURA_INT;
}

ILeituraCar::ILeituraCar(Celula &m)
    : m(m)
{
}

void ILeituraCar::execute(MaquinaVirtual &vm)
{

    m = vm.leChar();
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILeituraCar::tipoInstucao()
{
    return TipoInstrucao::LEITURA_CAR;
}

ILeituraReal::ILeituraReal(Celula &m)
    : m(m)
{

}

void ILeituraReal::execute(MaquinaVirtual &vm)
{
    m = vm.leDouble();
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILeituraReal::tipoInstucao()
{
    return TipoInstrucao::LEITURA_REAL;
}

ICarrega::ICarrega(Celula &registrador, Celula &offset, int desl)
    : registrador(registrador), offset(offset), desl(desl)
{
}

void ICarrega::execute(MaquinaVirtual &vm)
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<=acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+100);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        vm.msgErro("ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "+QString::number(acessa.toInt())+"\n");
    }
    try
    {
        registrador = vm.memoria[acessa.toInt()];
    }
    catch(exception &e)
    {
        vm.erf = true;
        vm.msgErro("ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "+QString::number(acessa.toInt())+"\n");
    }

    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICarrega::tipoInstucao()
{
    return TipoInstrucao::CARREGA;
}

ISalva::ISalva(Celula &registrador, Celula &offset, int desl)
    : registrador(registrador), offset(offset), desl(desl)
{
}

void ISalva::execute(MaquinaVirtual &vm)
{
    Celula acessa = offset+desl;
    if(vm.memoria.capacity()<=acessa.toInt())
        vm.memoria.reserve(acessa.toInt()+100);
    if(acessa.toInt()<0)
    {
        vm.erf = true;
        vm.msgErro("ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "+QString::number(acessa.toInt())+"\n");
    }
    try
    {
        vm.memoria[acessa.toInt()] = registrador;
    }
    catch(exception &e)
    {
        vm.erf = true;
        vm.msgErro("ACESSO INDEVIDO DE MEMORIA: ERRO DE SEGMENTACAO\nENDERECO MEMORIA: "+QString::number(acessa.toInt())+"\n");
    }
    ++vm.pc;

    if(CompInfo::isDebug())
    {
        vm.atualizarVariaveis();
    }
}

TipoInstrucao::TipoInstrucao ISalva::tipoInstucao()
{
    return TipoInstrucao::SALVA;
}

IEBit::IEBit(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IEBit::execute(MaquinaVirtual &vm)
{
    registrador = operando1 & operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEBit::tipoInstucao()
{
    return TipoInstrucao::E_BIT;
}

IEBitIm::IEBitIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IEBitIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 & operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEBitIm::tipoInstucao()
{
    return TipoInstrucao::E_BIT_IM;
}

IOuBit::IOuBit(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IOuBit::execute(MaquinaVirtual &vm)
{
    registrador = operando1 | operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IOuBit::tipoInstucao()
{
    return TipoInstrucao::OU_BIT;
}

IOuBitIm::IOuBitIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IOuBitIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 | operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IOuBitIm::tipoInstucao()
{
    return TipoInstrucao::OU_BIT_IM;
}

IXorBit::IXorBit(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IXorBit::execute(MaquinaVirtual &vm)
{
    registrador = operando1 ^ operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IXorBit::tipoInstucao()
{
    return TipoInstrucao::XOR_BIT;
}

IXorBitIm::IXorBitIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IXorBitIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 ^ operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IXorBitIm::tipoInstucao()
{
    return TipoInstrucao::XOR_BIT_IM;
}

IShiftDir::IShiftDir(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftDir::execute(MaquinaVirtual &vm)
{
    registrador = operando1 >> operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IShiftDir::tipoInstucao()
{
    return TipoInstrucao::SHIFT_DIR;
}

IShiftEsq::IShiftEsq(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftEsq::execute(MaquinaVirtual &vm)
{
    registrador = operando1 << operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IShiftEsq::tipoInstucao()
{
    return TipoInstrucao::SHIFT_ESQ;
}

ILigMaiorQ::ILigMaiorQ(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorQ::execute(MaquinaVirtual &vm)
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorQ::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_QUE;
}

ILigMaiorQIm::ILigMaiorQIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorQIm::execute(MaquinaVirtual &vm)
{
    if(operando1 > operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorQIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_QUE_IM;
}

ILigMenorQ::ILigMenorQ(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMenorQ::execute(MaquinaVirtual &vm)
{
    if(operando1 < operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorQ::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_QUE;
}

ILigMenorQIm::ILigMenorQIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void ILigMenorQIm::execute(MaquinaVirtual &vm)
{
    if(operando1 < operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorQIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_QUE_IM;
}

ILigMaiorEq::ILigMaiorEq(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMaiorEq::execute(MaquinaVirtual &vm)
{
    if(operando1 >= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorEq::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_EQ;
}

ILigMaiorEqIm::ILigMaiorEqIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMaiorEqIm::execute(MaquinaVirtual &vm)
{
    if(operando1 >= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMaiorEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MAIOR_EQ_IM;
}


ILigMenorEq::ILigMenorEq(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ILigMenorEq::execute(MaquinaVirtual &vm)
{
    if(operando1 <= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorEq::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_EQ;
}

ILigMenorEqIm::ILigMenorEqIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigMenorEqIm::execute(MaquinaVirtual &vm)
{
    if(operando1 <= operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigMenorEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_MENOR_EQ_IM;
}

ILigEq::ILigEq(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigEq::execute(MaquinaVirtual &vm)
{
    if(operando1 == operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigEq::tipoInstucao()
{
    return TipoInstrucao::LIG_EQ;
}

ILigEqIm::ILigEqIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigEqIm::execute(MaquinaVirtual &vm)
{
    if(operando1 == operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_EQ_IM;
}

ILigNaoEq::ILigNaoEq(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigNaoEq::execute(MaquinaVirtual &vm)
{
    if(operando1 != operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigNaoEq::tipoInstucao()
{
    return TipoInstrucao::LIG_NAO_EQ;
}

ILigNaoEqIm::ILigNaoEqIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void ILigNaoEqIm::execute(MaquinaVirtual &vm)
{
    if(operando1 != operando2)
        registrador = 1;
    else
        registrador = 0;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ILigNaoEqIm::tipoInstucao()
{
    return TipoInstrucao::LIG_NAO_EQ_IM;
}

INaoBit::INaoBit(Celula &registrador, Celula &operando1)
    : registrador(registrador), operando1(operando1)
{

}
void INaoBit::execute(MaquinaVirtual &vm)
{
    registrador = ~ operando1;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao INaoBit::tipoInstucao()
{
    return TipoInstrucao::NAO_BIT;
}

INaoBitIm::INaoBitIm(Celula &registrador, Celula operando1)
    : registrador(registrador), operando1(operando1)
{

}
void INaoBitIm::execute(MaquinaVirtual &vm)
{
    registrador = ~ operando1;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao INaoBitIm::tipoInstucao()
{
    return TipoInstrucao::NAO_BIT_IM;
}

INada::INada() { }

void INada::execute(MaquinaVirtual &vm)
{
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao INada::tipoInstucao()
{
    return TipoInstrucao::NADA;
}

IEscritaPalavraIm::IEscritaPalavraIm(QString *palavra)
    :palavra(palavra) { }

void IEscritaPalavraIm::execute(MaquinaVirtual &vm)
{
    vm.escrevePalavra(palavra);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaPalavraIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_PALAVRA;
}

IEscritaChar::IEscritaChar(Celula &m)
    : m(m) { }

void IEscritaChar::execute(MaquinaVirtual &vm)
{
     vm.escreveChar(m.toChar());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaChar::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_CHAR;
}

IEscritaCharIm::IEscritaCharIm(int m)
    : m(m) { }

void IEscritaCharIm::execute(MaquinaVirtual &vm)
{
    vm.escreveChar((char)m);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaCharIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_CHAR_IM;
}

IEscritaInt::IEscritaInt(Celula &m)
    : m(m) { }

void IEscritaInt::execute(MaquinaVirtual &vm)
{
    vm.escreveInt(m.toInt());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaInt::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_INT;
}

IEscritaIntIm::IEscritaIntIm(int m)
    : m(m) { }

void IEscritaIntIm::execute(MaquinaVirtual &vm)
{
    vm.escreveInt(m);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaIntIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_INT_IM;
}

IEscritaDouble::IEscritaDouble(Celula &m)
   : m(m) { }

void IEscritaDouble::execute(MaquinaVirtual &vm)
{
    vm.escreveDouble(m.toDouble());
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IEscritaDouble::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_DOUBLE;
}

IEscritaDoubleIm::IEscritaDoubleIm(double m)
   : m(m) { }

void IEscritaDoubleIm::execute(MaquinaVirtual &vm)
{
    vm.escreveDouble(m);
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao IEscritaDoubleIm::tipoInstucao()
{
    return TipoInstrucao::ESCRITA_DOUBLE_IM;
}

IAdcIm::IAdcIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void IAdcIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 + operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IAdcIm::tipoInstucao()
{
    return TipoInstrucao::ADC_IM;
}

ISubIm::ISubIm(Celula &registrador, Celula &operando1, Celula  operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void ISubIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 - operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISubIm::tipoInstucao()
{
    return TipoInstrucao::SUB_IM;
}

IMultIm::IMultIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void IMultIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1 * operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IMultIm::tipoInstucao()
{
    return TipoInstrucao::MULT_IM;
}

IDivIm::IDivIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2) { }

void IDivIm::execute(MaquinaVirtual &vm)
{
    if(operando2==0)
    {
        vm.msgErro("ERRO DIVISAO POR ZERO\n");
        vm.erf = true;
        return;
    }
    registrador = operando1 / operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDivIm::tipoInstucao()
{
    return TipoInstrucao::DIV_IM;
}

IRet::IRet(Celula &registrador)
    : registrador(registrador) { }

void IRet::execute(MaquinaVirtual &vm)
{
    vm.pc = registrador.toInt();
}

TipoInstrucao::TipoInstrucao IRet::tipoInstucao()
{
    return TipoInstrucao::RET;
}

ITroca::ITroca(Celula &registrador1, Celula &registrador2)
    :registrador1(registrador1), registrador2(registrador2)
{

}

void ITroca::execute(MaquinaVirtual &vm)
{
    Celula temp = registrador2;
    registrador2 = registrador1;
    registrador1 = temp;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ITroca::tipoInstucao()
{
    return TipoInstrucao::TROCA;
}

IResto::IResto(Celula &registrador, Celula &operando1, Celula &operando2)
    :registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IResto::execute(MaquinaVirtual &vm)
{
    if(operando2==0)
    {
        vm.msgErro("ERRO DIVISAO POR ZERO\n");
        vm.erf = true;
        return;
    }
    registrador = operando1 % operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IResto::tipoInstucao()
{
    return TipoInstrucao::RESTO;
}

IRestoIm::IRestoIm(Celula &registrador, Celula &operando1, Celula operando2)
    :registrador(registrador), operando1(operando1), operando2(operando2) {}
void IRestoIm::execute(MaquinaVirtual &vm)
{
    if(operando2==0)
    {
        vm.msgErro("ERRO DIVISAO POR ZERO\n");
        vm.erf = true;
        return;
    }
    registrador = operando1 % operando2;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IRestoIm::tipoInstucao()
{
    return TipoInstrucao::RESTO_IM;
}

INeg::INeg(Celula &registrador, Celula &operando1)
    :registrador(registrador), operando1(operando1)
{

}
void INeg::execute(MaquinaVirtual &vm)
{
    registrador = (-(operando1));
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao INeg::tipoInstucao()
{
    return TipoInstrucao::NEG;
}

INegIm::INegIm(Celula &registrador, Celula operando1)
    :registrador(registrador), operando1(operando1)
{

}
void INegIm::execute(MaquinaVirtual &vm)
{
    registrador = - operando1;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao INegIm::tipoInstucao()
{
    return TipoInstrucao::NEG_IM;
}

IBoolean::IBoolean(Celula &registrador)
    : registrador(registrador) { }
void IBoolean::execute(MaquinaVirtual &vm)
{
    registrador.convToInt();
    if(registrador!= 0)
        registrador = 1;
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IBoolean::tipoInstucao()
{
    return TipoInstrucao::BOOLEAN;
}

IPotencia::IPotencia(Celula &registrador, Celula &operando1, Celula &operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}
void IPotencia::execute(MaquinaVirtual &vm)
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}


TipoInstrucao::TipoInstrucao IPotencia::tipoInstucao()
{
    return TipoInstrucao::POTENCIA;
}


IPotenciaIm::IPotenciaIm(Celula &registrador, Celula &operando1, Celula operando2)
    : registrador(registrador), operando1(operando1), operando2(operando2)
{

}

void IPotenciaIm::execute(MaquinaVirtual &vm)
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IPotenciaIm::tipoInstucao()
{
    return TipoInstrucao::POTENCIA_IM;
}

ICast::ICast(Celula &registrador, TipoVariavel::TipoVariavel tipo)
    : registrador(registrador), tipo(tipo) { }
void ICast::execute(MaquinaVirtual &vm)
{
    if(tipo == TipoVariavel::TIPO_INT)
    {
        registrador.convToInt();
    }
    else if(tipo == TipoVariavel::TIPO_CAR)
    {
        registrador.convToChar();
    }
    else
    {
        registrador.convToDouble();
    }
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ICast::tipoInstucao()
{
    return TipoInstrucao::CAST;
}

ISistema::ISistema(Sistema::Comando comando)
    : comando(comando) { }

void ISistema::execute(MaquinaVirtual &vm)
{
    vm.sistema(comando);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao ISistema::tipoInstucao()
{
    return TipoInstrucao::SISTEMA;
}


IDebugPasso::IDebugPasso(int linha)
    :linha(linha){ }

void IDebugPasso::execute(MaquinaVirtual &vm)
{
    vm.sincronizar_passo(this->linha);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDebugPasso::tipoInstucao()
{
    return TipoInstrucao::DEBUG_PASSO;
}


IDebugEmpilhaExec::IDebugEmpilhaExec() { }

void IDebugEmpilhaExec::execute(MaquinaVirtual &vm)
{
    vm.empilha_chamada();
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDebugEmpilhaExec::tipoInstucao()
{
    return TipoInstrucao::DEBUG_EMPILHA;
}


IDebugDesempilhaExec::IDebugDesempilhaExec() { }

void IDebugDesempilhaExec::execute(MaquinaVirtual &vm)
{
    vm.desempilha_chamada();
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDebugDesempilhaExec::tipoInstucao()
{
    return TipoInstrucao::DEBUG_DESEMPILHA;
}


IDebugVariavelEmpilha::IDebugVariavelEmpilha(No *no, int offset, int profundidade, No *pno)
    : no(no), offset(offset), profundidade(profundidade), pno(pno) { }

void IDebugVariavelEmpilha::execute(MaquinaVirtual &vm)
{
    vm.empilha_variavel(no, offset, profundidade, pno);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDebugVariavelEmpilha::tipoInstucao()
{
    return TipoInstrucao::DEBUG_VAR_EMPILHA;
}


IDebugVariavelDesempilha::IDebugVariavelDesempilha(No* no)
    : no(no) { }

void IDebugVariavelDesempilha::execute(MaquinaVirtual &vm)
{
    vm.desempilha_variavel(no);
    ++vm.pc;
}

TipoInstrucao::TipoInstrucao IDebugVariavelDesempilha::tipoInstucao()
{
    return TipoInstrucao::DEBUG_VAR_DESEMPILHA;
}
