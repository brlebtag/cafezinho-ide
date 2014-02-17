#include "MaquinaVirtual.h"
#include "Instrucao.h"

MaquinaVirtual::MaquinaVirtual(QObject *parent) :
    QObject(parent)
{
    pc =0;
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
    while(execute&&pc>=0&&pc<codigo.size())
        codigo[pc]->execute();
}

void MaquinaVirtual::passo()
{
    if(execute&&pc>=0&&pc<codigo.size())
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

CelulaMemoria MaquinaVirtual::acessarMemoria(int offset)
{
    if(offset>=0 && offset<memoria.size())
        return memoria[offset];
    //senao emite erro de segmentacao...
}

int MaquinaVirtual::aloca(int quantidade)
{
    int atual = memoria.size();
    memoria.reserve(quantidade);

    //inicializa memeoria

    for(int i=0; i<quantidade; i++)
    {
        memoria[atual + i] = 0;
    }

    return atual;
}
