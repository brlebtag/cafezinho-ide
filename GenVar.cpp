#include "GenVar.h"

GenVar::GenVar()
{
}

GenVar::~GenVar()
{

}

QString GenVar::tipoParaString(TipoVariavel::TipoVariavel variavel)
{
    switch(variavel)
    {
        case TipoVariavel::TIPO_CAR:
        {
            return "car";
        }
        break;
        case TipoVariavel::TIPO_INT:
        {
            return "int";
        }
        break;
        case TipoVariavel::TIPO_REAL:
        {
            return "real";
        }
        break;
    }
}

QString GenVar::memParaStr(MaquinaVirtual &vm, int posicao, TipoVariavel::TipoVariavel variavel)
{
    switch(variavel)
    {
        case TipoVariavel::TIPO_CAR:
        {
            return QString(vm.memoria[posicao].toChar());
        }
        break;
        case TipoVariavel::TIPO_INT:
        {
            return QString::number(vm.memoria[posicao].toInt());
        }
        break;
        case TipoVariavel::TIPO_REAL:
        {
            return QString::number(vm.memoria[posicao].toDouble());
        }
        break;
    }
}
