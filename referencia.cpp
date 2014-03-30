#include "referencia.h"

Referencia::Referencia() { }
Referencia::Referencia(No* origem, int profundidade, int offset, bool parametro, bool vetor)
    : origem(origem), profundidade(profundidade), offset(offset), parametro(parametro), vetor(vetor) { }
Referencia::~Referencia(){}
