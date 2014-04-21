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
    return breakpoints.value(linha);
}

void ValidarBreakPoint::validarBreakPoints(QSet<int> &breakpoints)
{
    //marca os breakpoints como falso
    reiniciar_breakpoints();

    //remarca os breakpoints
    foreach(int a, breakpoints)
    {
        QMap<int, bool>::iterator it = this->breakpoints.lowerBound(a);
        this->breakpoints[it.key()] = true;
    }
}

void ValidarBreakPoint::reiniciar_breakpoints()
{
    for(QMap<int, bool>::iterator it = breakpoints.begin(); it!=breakpoints.end(); ++it)
    {
        breakpoints[it.key()] = false;
    }
}
