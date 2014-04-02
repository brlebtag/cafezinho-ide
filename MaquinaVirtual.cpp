#include "MaquinaVirtual.h"
#include "Instrucao.h"

MaquinaVirtual::MaquinaVirtual(QObject *parent) :
    QObject(parent), memoria(100)
{
    reiniciar();
}

MaquinaVirtual::~MaquinaVirtual()
{
    //remove todas as instruções criadas...
    try
    {
        for(int i=0; i<codigo.size(); ++i)
        {
           delete codigo[i];
        }

        for(int i=0; i<rotulo.size(); ++i)
        {
            delete rotulo[i];
        }
    }
    catch(exception &e)
    {

    }
}


void MaquinaVirtual::reiniciar()
{
    pc = 0;
    pp = 0;
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    bp = 0;
    er = 0;
    pg = 0;
    bf = false;
    sf = false;
    ef = false;
    erf = false;
    execute = true;
}

void MaquinaVirtual::msgErro(QString _err)
{
    CompInfo::err()<<_err;
}

void MaquinaVirtual::executar()
{
    while(execute&&(!erf))
    {
        try
        {
            codigo[pc]->execute(*this);
        }
        catch(exception &e)
        {
            CompInfo::err()<<"[SISTEMA] PROGRAMA ACABOU DE FORMA INESPERADA\n";
            erf = true;
        }
        if(pc<0||pc>=codigo.size())
        {
            CompInfo::err()<<"[SISTEMA] PROGRAMA ACABOU DE FORMA INESPERADA\n";
            erf = true;
        }
    }
}

void MaquinaVirtual::parar()
{
    execute = false;
}

void MaquinaVirtual::passo()
{
    if(execute&&(!erf))
    {
        try
        {
            codigo[pc]->execute(*this);
        }
        catch(exception &e)
        {
            CompInfo::err()<<"[SISTEMA] PROGRAMA ACABOU DE FORMA INESPERADA\n";
            erf = true;
        }
    }
}

void MaquinaVirtual::escreveInt(int c)
{
    CompInfo::out()<<c;
}

void MaquinaVirtual::escreveChar(char c)
{
    CompInfo::out()<<c;
}

void MaquinaVirtual::escreveDouble(double c)
{
    CompInfo::out()<<c;
}

void MaquinaVirtual::escrevePalavra(QString *palavra)
{
    CompInfo::out()<<palavra;
}

int MaquinaVirtual::leInt()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada.toInt();
}

char MaquinaVirtual::leChar()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada[0].toLatin1();
}

double MaquinaVirtual::leDouble()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada.toDouble();
}

void MaquinaVirtual::sistema(Sistema::Comando comando)
{
    switch(comando)
    {
        case Sistema::LIMPAR:
        {
            emit limpar_terminal();
        }
        break;
        case Sistema::NOVA_LINHA:
        {
            CompInfo::appendTexto("</br>");
        }
        break;
    }
}
