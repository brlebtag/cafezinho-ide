#ifndef SEMANTICO_H
#define SEMANTICO_H

#include <QStack>
#include <QHash>
#include <QList>
#include <QString>
#include "arvore_abstrata.h"
#include "simbolo.h"
#include "CompThread.h"
#include "CompInfo.h"

using namespace std;
using namespace TipoVariavel;
using namespace Operador;
using namespace TipoNo;

typedef QStack<Simbolo*> PilhaSimbolo;
typedef QHash<QString, PilhaSimbolo*> TabelaSimbolo;
typedef TabelaSimbolo::iterator IteradorTabelaSimbolo;

#ifndef __LISTA__
#define __LISTA__
typedef QList<NInstrucao*> ListaInstrucao;
typedef QList<NExpressao*> ListaExpressao;
typedef QList<NDeclaracaoVariavel*> ListaVariavel;
#endif

#ifndef __ITERADORES__
#define __ITERADORES__
typedef QList<NInstrucao*>::iterator IteradorInstrucao;
typedef QList<NExpressao*>::iterator IteradorExpressao;
typedef QList<NDeclaracaoVariavel*>::iterator IteradorVariavel;
#endif

typedef QList<IteradorTabelaSimbolo> Remover;
typedef QList<IteradorTabelaSimbolo>::iterator IteratorRemover;

//semantico.cpp
IteradorTabelaSimbolo analise_semantica(TabelaSimbolo &tabela, No* no, int profundidade, No* funcao=0);

//checa_tipo.cpp
TipoVariavel::TipoVariavel checar_tipo(TabelaSimbolo &tabela, No* no);
//checa_tipo.cpp
bool checa_tipo_init(TabelaSimbolo &tabela, No* no, TipoVariavel::TipoVariavel tipo);

//checa_vetor_dimensao.cpp
bool checa_vetor_dimensao(bool parametro, NDeclVarVetorial *var);
//checa_chamada.cpp
No* ultimo_parametro(TabelaSimbolo &tabela, No * no);
//checa_chamada.cpp
bool checar_chamada(TabelaSimbolo &tabela, No* parametro, No* argumento);

//nome.cpp
QString tipo_no(No * no);
//nome.cpp
QString nome_tipo(TipoVariavel::TipoVariavel tipo);


#ifndef __CHECA_NO__
#define __CHECA_NO__
#define CHECA_NO(no, IDENT) no->tipoNo() == IDENT
#define NCHECA_NO(no, IDENT) no->tipoNo() != IDENT
#endif

#endif // SEMANTICO_H
