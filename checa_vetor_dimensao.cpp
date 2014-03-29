#include "semantico.h"

extern int erro_compilador;

bool checa_vetor_dimensao(bool parametro, NDeclVarVetorial *var)
{
    int comeco;
    if(parametro)
        comeco = 1;
    else
        comeco = 0;
    bool result = true;
    for(int i=comeco; i<var->dimensoes->size(); ++i)
    {
        result &= var->dimensoes->at(i)->tipoNo()==INTEIRO;
    }
    return result;
}
