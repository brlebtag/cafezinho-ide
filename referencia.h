#ifndef REFERENCIA_H
#define REFERENCIA_H

#include "arvore_abstrata.h"

class Referencia
{
public:
    Referencia(No* origem, int profundidade = 0, int offset = 0, bool parametro = false, bool vetor = false, bool variavel = false);
    Referencia();
    ~Referencia();
    int profundidade;
    int offset;
    bool parametro;
    bool vetor;
    No* origem;
    //Informação para debug...
    bool variavel;
};

#endif // REFERENCIA_H
