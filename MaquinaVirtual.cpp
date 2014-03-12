#include "MaquinaVirtual.h"
#include "Instrucao.h"

MaquinaVirtual::MaquinaVirtual(QObject *parent) :
    QObject(parent)
{
    pc = 0;
    sp = 0;
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    bp = 0;
    ra = 0;
    bf = false;
    sf = false;
    ef = false;
    erf = false;
}

MaquinaVirtual::~MaquinaVirtual()
{
    //remove todas as instruções criadas...
    for(int i=0; i<codigo.size(); i++)
        delete codigo[i];
}

void MaquinaVirtual::executar()
{
    execute = true;
}

void MaquinaVirtual::parar()
{
    execute = false;
}

void MaquinaVirtual::rodar()
{
    while(execute&&(!erf))
    {
        codigo[pc]->execute();
        if(erf)
            break;
    }
}

void MaquinaVirtual::passo()
{
    if(execute&&(!erf))
        codigo[pc]->execute();
}

void MaquinaVirtual::inserirInstrucao(Instrucao *i)
{
    codigo.push_back(i);
}

void MaquinaVirtual::empilhar(CelulaMemoria m)
{
    memoria.push_back(m);
}

void MaquinaVirtual::desempilhar()
{
    memoria.pop_back();
}

void MaquinaVirtual::escreva(QString texto)
{

}

int MaquinaVirtual::lerInt()
{
    return 0;
}

double MaquinaVirtual::lerReal()
{
    return 0.0;
}

char MaquinaVirtual::lerCar()
{
    return '\0';
}

CelulaMemoria &MaquinaVirtual::getCelula(int offset)
{
    if(offset>=0 && offset<memoria.size())
        return memoria[offset];
    //senao emite erro de segmentacao...
    erf = true;
}

void MaquinaVirtual::setCelula(CelulaMemoria &registrador, int offset)
{
    if(offset>=0 && offset<memoria.size())
        memoria[offset] = registrador;
    //senao emite erro de segmentacao...
    erf = true;
}

int MaquinaVirtual::aloca(int quantidade)
{
    int atual = memoria.size();
    memoria.reserve(quantidade+1);

    //inicializa memeoria

    for(int i=0; i<quantidade; i++)
    {
        memoria[atual + i] = 0;
    }

    return atual;
}
