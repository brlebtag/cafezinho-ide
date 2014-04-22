#include "GenVar.h"

GenVar::GenVar()
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
