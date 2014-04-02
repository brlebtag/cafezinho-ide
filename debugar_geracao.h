#ifndef DEBUGAR_GERACAO_H
#define DEBUGAR_GERACAO_H

#include "arvore_abstrata.h"
#include "MaquinaVirtual.h"
#include "QDebug"

using namespace std;

//debug.cpp
void debug_arvore(No* no, int nivel);
QString imprime_nivel(int nivel);
//debug_codigo.cpp
void debug_codigo(MaquinaVirtual &vm);
void imprime_instrucao(MaquinaVirtual &vm, Instrucao * instrucao, int posicao);
QString nome_reg(MaquinaVirtual &vm, CelulaMemoria &celula);
QString nome_tipo_cast(TipoVariavel::TipoVariavel tipo);
QString nome_comando(Sistema::Comando comando);

#endif // DEBUGAR_GERACAO_H
