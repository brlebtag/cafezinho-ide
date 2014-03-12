#include "Instrucao.h"
#include "MaquinaVirtual.h"

Instrucao::Instrucao(MaquinaVirtual &vm)
    :vm(vm)
{

}

Instrucao::~Instrucao()
{
}

IMove::IMove(MaquinaVirtual &vm, int &para, int &de)
    : Instrucao(vm),registrador1(para), registrador2(de)
{
}

void IMove::execute()
{
    registrador1 = registrador2;
    ++vm.pc;
}


ISalto::ISalto(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISalto::execute()
{
    vm.pc = offset;
}


IAdi::IAdi(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IAdi::execute()
{
    registrador = operando1 + operando2;
    ++vm.pc;
}

ISub::ISub(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void ISub::execute()
{
    registrador = operando1 - operando2;
    ++vm.pc;
}


IMult::IMult(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IMult::execute()
{
    registrador = operando1 * operando2;
    ++vm.pc;
}


IDiv::IDiv(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IDiv::execute()
{
    registrador = operando1 / operando2;
    ++vm.pc;
}


IPot::IPot(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IPot::execute()
{
    registrador = operando1.pot(operando2);
    ++vm.pc;
}


ICmp::ICmp(MaquinaVirtual &vm, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), operando1(operando1), operando2(operando2)
{
}

void ICmp::execute()
{
    if(operando1 > operando1)
    {
        vm.bf = true;
        vm.sf = false;
        vm.ef = false;
    }
    else if(operando1 < operando1)
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
}


ISaltoEq::ISaltoEq(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISaltoEq::execute()
{
    if(vm.ef)
        vm.pc = offset;
    else
        ++vm.pc;
}

ISaltoMaior::ISaltoMaior(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISaltoMaior::execute()
{
    if(vm.bf)
        vm.pc = offset;
    else
        ++vm.pc;
}


ISaltoMaiorEq::ISaltoMaiorEq(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISaltoMaiorEq::execute()
{
    if(vm.bf||vm.ef)
        vm.pc = offset;
    else
        ++vm.pc;
}


ISaltoMenor::ISaltoMenor(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISaltoMenor::execute()
{
    if(vm.sf)
        vm.pc = offset;
    else
        ++vm.pc;
}

ISaltoMenorEq::ISaltoMenorEq(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void ISaltoMenorEq::execute()
{
    if(vm.sf||vm.ef)
        vm.pc = offset;
    else
        ++vm.pc;
}


IAloca::IAloca(MaquinaVirtual &vm, int quantidade)
    : Instrucao(vm)
{
    this->quantidade = quantidade;
}

void IAloca::execute()
{
    vm.aloca(quantidade);
    ++vm.pc;
}


IEmpilha::IEmpilha(MaquinaVirtual &vm, CelulaMemoria m)
    : Instrucao(vm)
{

}

void IEmpilha::execute()
{
    vm.empilhar(m);
    ++vm.sp;
    ++vm.pc;
}


IDesempilha::IDesempilha(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}

void IDesempilha::execute()
{
    vm.desempilhar();
    --vm.sp;
    ++vm.pc;
}


IParar::IParar(MaquinaVirtual &vm)
    : Instrucao(vm)
{

}

void IParar::execute()
{
    vm.parar();
}


IChamada::IChamada(MaquinaVirtual &vm, int offset)
    : Instrucao(vm)
{
    this->offset = offset;
}

void IChamada::execute()
{
    vm.ra = vm.pc + 1;
    vm.pc = offset;
}


IEscrita::IEscrita(MaquinaVirtual &vm, CelulaMemoria m)
    : Instrucao(vm)
{
    this->m = m;
}

void IEscrita::execute()
{
    vm.escreva(m.toString());
    ++vm.pc;
}

ILeituraInt::ILeituraInt(MaquinaVirtual &vm, CelulaMemoria &m)
    : Instrucao(vm), m(m)
{
}

void ILeituraInt::execute()
{
    m = vm.lerInt();
    ++vm.pc;
}


ILeituraCar::ILeituraCar(MaquinaVirtual &vm, CelulaMemoria &m)
    : Instrucao(vm), m(m)
{
}

void ILeituraCar::execute()
{
    m = vm.lerCar();
    ++vm.pc;
}


ILeituraReal::ILeituraReal(MaquinaVirtual &vm, CelulaMemoria &m)
    : Instrucao(vm), m(m)
{
}

void ILeituraReal::execute()
{
    m = vm.lerReal();
    ++vm.pc;
}


ICarrega::ICarrega(MaquinaVirtual &vm, CelulaMemoria &registrador, int offset)
    : Instrucao(vm), registrador(registrador), offset(offset)
{
}

void ICarrega::execute()
{
    registrador = vm.getCelula(offset);
    ++vm.pc;
}


ISalva::ISalva(MaquinaVirtual &vm, CelulaMemoria &registrador, int offset)
    : Instrucao(vm), registrador(registrador), offset(offset)
{
}

void ISalva::execute()
{
    vm.setCelula(registrador, offset);
    ++vm.pc;
}


IE::IE(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IE::execute()
{
    registrador = operando1.eLogico(operando2);
}


IEBit::IEBit(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IEBit::execute()
{
    registrador = operando1 & operando2;
}


IOu::IOu(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IOu::execute()
{
    registrador = operando1.ouLogico(operando2);
}


IOuBit::IOuBit(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IOuBit::execute()
{
    registrador = operando1 | operando2;
}


IXorBit::IXorBit(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IXorBit::execute()
{
    registrador = operando1 ^ operando2;
}


IShiftDir::IShiftDir(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftDir::execute()
{
    registrador = operando1 >> operando2;
}


IShiftEsq::IShiftEsq(MaquinaVirtual &vm, CelulaMemoria &registrador, CelulaMemoria &operando1, CelulaMemoria &operando2)
    : Instrucao(vm), registrador(registrador), operando1(operando1), operando2(operando2)
{
}

void IShiftEsq::execute()
{
    registrador = operando1 << operando2;
}
