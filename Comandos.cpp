#include "GerarCodigo.h"

void inc_pp(MaquinaVirtual &vm, int qtd)
{
    vm.codigo.push_back(new IAdcIm(vm.pp, vm.pp, CelulaMemoria(qtd)));
}

void dec_pp(MaquinaVirtual &vm, int qtd)
{
    vm.codigo.push_back(new ISubIm(vm.pp, vm.pp, CelulaMemoria(qtd)));
}

void empilha(MaquinaVirtual &vm , CelulaMemoria &op)
{
    //empilha op
    vm.codigo.push_back(new ISalva(op, vm.pp));

    //incrementa o ponteiro de pilha
    inc_pp(vm, 1);
}

void desempilha(MaquinaVirtual &vm, CelulaMemoria &op)
{
    //decrementa o ponteiro de pilha
    dec_pp(vm, 1);

    //desempilha eax
    vm.codigo.push_back(new ICarrega(op, vm.pp));
}

void cmp(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
    vm.codigo.push_back(new ICmp(op1, op2));
}

void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria op2)
{
    vm.codigo.push_back(new ICmpIm(op1, op2));
}

void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, int op2)
{
    vm.codigo.push_back(new ICmpIm(op1, op2));
}

void seq(MaquinaVirtual &vm, int &offset)
{
    vm.codigo.push_back(new ISaltoEq(offset));
}

void si(MaquinaVirtual &vm, int &offset)
{
    vm.codigo.push_back(new ISalto(offset));
}

void invoca(MaquinaVirtual &vm, int &offset)
{
    vm.codigo.push_back(new IChamada(offset));
}

void troca(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
    vm.codigo.push_back(new ITroca(op1, op2));
}

void move(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
    vm.codigo.push_back(new IMove(op1, op2));
}

void carrega(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2)
{
    vm.codigo.push_back(new ICarrega(op1, op2));
}

void ret(MaquinaVirtual &vm)
{
    vm.codigo.push_back(new IRet(vm.er));
}
