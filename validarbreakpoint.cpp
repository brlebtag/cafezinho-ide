#include "validarbreakpoint.h"

ValidarBreakPoint::ValidarBreakPoint()
{
}

void ValidarBreakPoint::inserirParada(int linha)
{
    if(!breakpoints.contains(linha))
        breakpoints.insert(linha, false);
}

bool ValidarBreakPoint::isBreakPoint(int linha)
{
    return this->breakpoints.lowerBound(linha).value();
}

void ValidarBreakPoint::validarBreakPoints(QSet<int> &breakpoints)
{
    //marca os breakpoints como falso
    reiniciar_breakpoints();

    //remarca os breakpoints
    foreach(int indice, breakpoints)
    {
        this->breakpoints[indice] = true;
    }
}

void ValidarBreakPoint::reiniciar_breakpoints()
{
    for(QMap<int, bool>::iterator it = breakpoints.begin(); it!=breakpoints.end(); ++it)
    {
        breakpoints[it.key()] = false;
    }
}
