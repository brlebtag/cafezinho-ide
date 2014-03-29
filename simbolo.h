#ifndef SIMBOLO_H
#define SIMBOLO_H

#include "arvore_abstrata.h"

class Simbolo
{
public:
    Simbolo(No* no = 0, int profundidade = 0);
    ~Simbolo();
    int profundidade;
    No* no;
};

#endif // SIMBOLO_H
