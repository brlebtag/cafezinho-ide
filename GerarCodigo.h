#ifndef GERARCODIGO_H
#define GERARCODIGO_H

#include "arvore_abstrata.h"
#include "MaquinaVirtual.h"
#include "Instrucao.h"
#include "referencia.h"
#include <QHash>
#include <QStack>
#include <QList>
#include <QQueue>
#include <QString>
#include "CompInfo.h"
#include "debugar_geracao.h"

using namespace std;

#ifndef __LISTA__
#define __LISTA__
typedef QList<NInstrucao*> ListaInstrucao;
typedef QList<NExpressao*> ListaExpressao;
typedef QList<NDeclaracaoVariavel*> ListaVariavel;
#endif

typedef QStack<Referencia> PilhaRef;
typedef QHash<QString, PilhaRef> TabelaRef;
typedef QHash<QString, PilhaRef>::iterator IteradorTabelaRef;
typedef QList<IteradorTabelaRef> RemoverRef;
typedef QList<IteradorTabelaRef>::iterator IteradorRemoverRef;
typedef QPair<int, IteradorTabelaRef> Alocado;

#ifndef __ITERADORES__
#define __ITERADORES__
typedef QList<NInstrucao*>::iterator IteradorInstrucao;
typedef QList<NExpressao*>::iterator IteradorExpressao;
typedef QList<NDeclaracaoVariavel*>::iterator IteradorVariavel;
#endif

#ifndef __CHECA_NO__
#define __CHECA_NO__
#define CHECA_NO(no, IDENT) no->tipoNo() == IDENT
#define NCHECA_NO(no, IDENT) no->tipoNo() != IDENT
#endif


//GerarCodigo.cpp
void gerar_codigo(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao = 0);

//alocar_variavel.cpp
Alocado alocar_variavel(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, bool parametro = false);
int dimensao_vetor(NDeclVarVetorial *var);

//gerenciamento.cpp
No* ultimo_elemento(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao);
void gerar_indice(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao);
void gerar_atribuicao(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao);
void inserir_debug_instrucao(MaquinaVirtual &vm, No* no);
void empilha_exec(MaquinaVirtual &vm);
void desempilha_exec(MaquinaVirtual &vm);

//gerar_inicializador.cpp
void gerar_inicializador(MaquinaVirtual &vm, TabelaRef &tabela, NInicializadorVetor *list, int profundidade, int offset, No* funcao);;

//Comandos.cpp
void empilha(MaquinaVirtual &vm , CelulaMemoria &op);
void desempilha(MaquinaVirtual &vm, CelulaMemoria &op);
void inc_pp(MaquinaVirtual &vm, int qtd);
void dec_pp(MaquinaVirtual &vm, int qtd);
void invoca(MaquinaVirtual &vm, int &offset);
void troca(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void move(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void seq(MaquinaVirtual &vm, int &offset);
void cmp(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria op2);
void cmp_imm(MaquinaVirtual &vm, CelulaMemoria &op1, int op2);
void si(MaquinaVirtual &vm, int &offset);
void carrega(MaquinaVirtual &vm, CelulaMemoria &op1, CelulaMemoria &op2);
void ret(MaquinaVirtual &vm);

#endif // GERARCODIGO_H
