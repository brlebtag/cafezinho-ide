#include "debugar_geracao.h"

QString imprime_nivel(int nivel)
{
    QString level = "|";
    for(int i=0; i<nivel; ++i)
    {
        level+="-";
    }
    level+=" ";

    return level;
}

void debug_arvore(No* no, int nivel)
{
    switch(no->tipoNo())
    {
        case TipoNo::NO:
        {
            qDebug()<<imprime_nivel(nivel)<<"NO, linha: "<<no->linha;
        }
        break;
        case TipoNo::TERMINAR:
        {
            qDebug()<<imprime_nivel(nivel)<<"TERMINAR, linha: "<<no->linha;
        }
        break;
        case TipoNo::LIMPAR:
        {
            qDebug()<<imprime_nivel(nivel)<<"LIMPAR, linha: "<<no->linha;
        }
        break;
        case TipoNo::EXPRESSAO:
        {
            qDebug()<<imprime_nivel(nivel)<<"EXPRESSAO, linha: "<<no->linha;
        }
        break;
        case TipoNo::INSTRUCAO:
        {
            qDebug()<<imprime_nivel(nivel)<<"INSTRUCAO, linha: "<<no->linha;
        }
        break;
        case TipoNo::INTEIRO:
        {
            NInteiro *cons = dynamic_cast<NInteiro*>(no);
            qDebug()<<imprime_nivel(nivel)<<"INTEIRO: "<<cons->valor<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::CARACTER:
        {
            NCaracter *cons = dynamic_cast<NCaracter*>(no);
            qDebug()<<imprime_nivel(nivel)<<"CARACTER: "<<((char)cons->valor)<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::REAL:
        {

            NReal *cons = dynamic_cast<NReal*>(no);
            qDebug()<<imprime_nivel(nivel)<<"REAL: "<<cons->valor<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::PALAVRA_LITERAL:
        {

            NPalavraLiteral *cons = dynamic_cast<NPalavraLiteral*>(no);
            qDebug()<<imprime_nivel(nivel)<<"PALAVRA LITERAL: "<<*cons->valor<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::IDENTIFICADOR:
        {

            NIdentificador *ident = dynamic_cast<NIdentificador*>(no);
            qDebug()<<imprime_nivel(nivel)<<"IDENTIFICADOR: "<<*ident->nome<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::IDENTIFICADOR_ESCALAR:
        {

            NIdentificadorEscalar *ident = dynamic_cast<NIdentificadorEscalar*>(no);
            qDebug()<<imprime_nivel(nivel)<<"IDENTIFICADOR ESCALAR: "<<*ident->nome<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::IDENTIFICADOR_VETORIAL:
        {
            NIdentificadorVetorial *ident = dynamic_cast<NIdentificadorVetorial*>(no);

            qDebug()<<imprime_nivel(nivel)<<"IDENTIFICADOR VETORIAL: "<<*ident->nome<<", linha: "<<no->linha;
            for(int i=0; i<ident->indice->size(); ++i)
                debug_arvore(ident->indice->at(i), nivel+1);
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL:
        {

            NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);
            qDebug()<<imprime_nivel(nivel)<<"DECLARACAO VARIAVEL: "<<*var->nome<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
        {

            NDeclVarEscalar *var = dynamic_cast<NDeclVarEscalar*>(no);
            qDebug()<<imprime_nivel(nivel)<<"DECLARACAO VARIAVEL ESCALAR: "<<*var->nome<<", linha: "<<no->linha;
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
        {

            NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(no);
            qDebug()<<imprime_nivel(nivel)<<"DECLARACAO VARIAVEL VETORIAL: "<<*var->nome<<", linha: "<<no->linha;

            for(int i=0; i<var->dimensoes->size(); ++i)
                debug_arvore(var->dimensoes->at(i), nivel+1);

        }
        break;
        case TipoNo::BLOCO:
        {

            qDebug()<<imprime_nivel(nivel)<<"BLOCO, linha: "<<no->linha;

            NBloco *bloco = dynamic_cast<NBloco*>(no);

            for(int i=0; i<bloco->instrucoes->size(); ++i)
                debug_arvore(bloco->instrucoes->at(i), nivel+1);
        }
        break;
        case TipoNo::CHAMADA_FUNCAO:
        {

            NChamadaFuncao *call = dynamic_cast<NChamadaFuncao*>(no);
            qDebug()<<imprime_nivel(nivel)<<"CHAMADA FUNCAO: "<<*call->nome<<", linha: "<<no->linha;

            for(int i=0; i<call->argumentos->size(); ++i)
                debug_arvore(call->argumentos->at(i), nivel+1);
        }
        break;
        case TipoNo::DECLARACAO_FUNCAO:
        {

            NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(no);
            qDebug()<<imprime_nivel(nivel)<<"DECLARACAO FUNCAO: "<<*func->nome<<", linha: "<<no->linha;

            for(int i=0; i<func->parametros->size(); ++i)
                debug_arvore(func->parametros->at(i), nivel+1);

            debug_arvore(func->bloco, nivel+1);
        }
        break;
        case TipoNo::INSTRUCAO_EXPRESSAO:
        {

            qDebug()<<imprime_nivel(nivel)<<"INSTRUCAO EXPRESSAO, linha: "<<no->linha;

            NInstrucaoExpressao *expr = dynamic_cast<NInstrucaoExpressao*>(no);
            debug_arvore(expr->expressao, nivel+1);
        }
        break;
        case TipoNo::ATRIBUICAO:
        {

            NAtribuicao *atr = dynamic_cast<NAtribuicao*>(no);
            qDebug()<<imprime_nivel(nivel)<<"ATRIBUICAO, Init:"<<atr->inicializa_variavel<<", linha: "<<no->linha;
            debug_arvore(atr->lhs, nivel+1);
            debug_arvore(atr->rhs, nivel+1);
        }
        break;
        case TipoNo::OPERACAO_BINARIA:
        {

            qDebug()<<imprime_nivel(nivel)<<"OPERACAO BINARIA, linha: "<<no->linha;

            NOperacaoBinaria *bin = dynamic_cast<NOperacaoBinaria*>(no);
            debug_arvore(bin->lhs, nivel+1);
            debug_arvore(bin->rhs, nivel+1);
        }
        break;
        case TipoNo::OPERACAO_UNARIA:
        {

            qDebug()<<imprime_nivel(nivel)<<"OPERACAO UNARIA, linha: "<<no->linha;

            NOperacaoUnaria *uni = dynamic_cast<NOperacaoUnaria*>(no);
            debug_arvore(uni->rhs, nivel+1);
        }
        break;
        case TipoNo::OPERACAO_TERCIARIA:
        {

            qDebug()<<imprime_nivel(nivel)<<"OPERACAO TERCIARIA, linha: "<<no->linha;

            NOperacaoTerciaria *ter = dynamic_cast<NOperacaoTerciaria*>(no);
            debug_arvore(ter->expressao, nivel+1);
            debug_arvore(ter->ifExpr, nivel+1);
            debug_arvore(ter->elsExpr, nivel+1);
        }
        break;
        case TipoNo::RETORNE:
        {

            qDebug()<<imprime_nivel(nivel)<<"RETORNE, linha: "<<no->linha;

            NRetorne *ret = dynamic_cast<NRetorne*>(no);
            debug_arvore(ret->expressao, nivel+1);
        }
        break;
        case TipoNo::LEIA:
        {

            qDebug()<<imprime_nivel(nivel)<<"LEIA, linha: "<<no->linha;

            NLeia *leia = dynamic_cast<NLeia*>(no);
            debug_arvore(leia->expressao, nivel+1);
        }
        break;
        case TipoNo::ESCREVA:
        {

            qDebug()<<imprime_nivel(nivel)<<"ESCREVA, linha: "<<no->linha;

            NEscreva *escreva = dynamic_cast<NEscreva*>(no);
            debug_arvore(escreva->expressao, nivel+1);
        }
        break;
        case TipoNo::NOVA_LINHA:
        {

            qDebug()<<imprime_nivel(nivel)<<"NOVA LINHA, linha: "<<no->linha;
        }
        break;
        case TipoNo::SE:
        {

            qDebug()<<imprime_nivel(nivel)<<"SE, linha: "<<no->linha;

            NSe *se = dynamic_cast<NSe*>(no);
            debug_arvore(se->expressao, nivel+1);
            debug_arvore(se->instrucao, nivel+1);
        }
        break;
        case TipoNo::SE_SENAO:
        {

            qDebug()<<imprime_nivel(nivel)<<"SE SENAO, linha: "<<no->linha;

            NSeSenao *senao = dynamic_cast<NSeSenao*>(no);
            debug_arvore(senao->expressao, nivel+1);
            debug_arvore(senao->instrucaoSe, nivel+1);
            debug_arvore(senao->instrucaoSenao, nivel+1);
        }
        break;
        case TipoNo::ENQUANTO:
        {

            qDebug()<<imprime_nivel(nivel)<<"ENQUANTO, linha: "<<no->linha;

            NEnquanto *enq = dynamic_cast<NEnquanto*>(no);
            debug_arvore(enq->expressao, nivel+1);
            debug_arvore(enq->instrucao, nivel+1);
        }
        break;
        case TipoNo::CAST:
        {

            qDebug()<<imprime_nivel(nivel)<<"CAST, linha: "<<no->linha;

            NCast *cast = dynamic_cast<NCast*>(no);
            debug_arvore(cast->expressao, nivel+1);
        }
        break;
        case TipoNo::LISTA_EXPRESSOES:
        {

            qDebug()<<imprime_nivel(nivel)<<"LISTA EXPRESSOES, linha: "<<no->linha;

            NListaExpressoes *list = dynamic_cast<NListaExpressoes*>(no);

            for(int i=0; i<list->expressoes->size(); ++i)
                debug_arvore(list->expressoes->at(i), nivel+1);
        }
        break;
        case TipoNo::INICIALIZADOR_VETOR:
        {

            qDebug()<<imprime_nivel(nivel)<<"INICIALIZADOR VETOR, linha: "<<no->linha;

            NInicializadorVetor *list = dynamic_cast<NInicializadorVetor*>(no);
            int i=0;
            for(ListaExpressao::iterator it = list->init->begin(); it!= list->init->end(); ++it, ++i)
                debug_arvore((*it), nivel+1);
        }
        break;
        case TipoNo::LISTA_INICIALIZADOR:
        {

            qDebug()<<imprime_nivel(nivel)<<"LISTA INICIALIZADOR, linha: "<<no->linha;

            NListaInicializador *list = dynamic_cast<NListaInicializador*>(no);
            int i=0;

            for(ListaExpressao::iterator it = list->expressoes->begin(); it!= list->expressoes->end(); ++it, ++i)
                debug_arvore((*it), nivel+1);
        }
        break;
    }
}


QString nome_no(No* no)
{
    switch(no->tipoNo())
    {
        case TipoNo::NO:
        {
            return "No";
        }
        break;
        case TipoNo::TERMINAR:
        {
            return "Terminar";
        }
        break;
        case TipoNo::LIMPAR:
        {
            return "Limpar";
        }
        break;
        case TipoNo::EXPRESSAO:
        {
            return "Expressao";
        }
        break;
        case TipoNo::INSTRUCAO:
        {
            return "Instrucao";
        }
        break;
        case TipoNo::INTEIRO:
        {
            return "Inteiro";
        }
        break;
        case TipoNo::CARACTER:
        {
            return "Caracter";
        }
        break;
        case TipoNo::REAL:
        {

            return "Real";
        }
        break;
        case TipoNo::PALAVRA_LITERAL:
        {

            return "Palavra Literal";
        }
        break;
        case TipoNo::IDENTIFICADOR:
        {
            return "Identificador";
        }
        break;
        case TipoNo::IDENTIFICADOR_ESCALAR:
        {
            return "Identificador Escalar";
        }
        break;
        case TipoNo::IDENTIFICADOR_VETORIAL:
        {
            return "Identificador Vetorial";
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL:
        {
            return "Declaracao Variavel";
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_ESCALAR:
        {
            return "Declaracao Variavel Escalar";
        }
        break;
        case TipoNo::DECLARACAO_VARIAVEL_VETORIAL:
        {

            return "Declaracao Variavel Vetorial";

        }
        break;
        case TipoNo::BLOCO:
        {

            return "Bloco";
        }
        break;
        case TipoNo::CHAMADA_FUNCAO:
        {

            return "Chamada Funcao";
        }
        break;
        case TipoNo::DECLARACAO_FUNCAO:
        {
            return "Declaracao Funcao";
        }
        break;
        case TipoNo::INSTRUCAO_EXPRESSAO:
        {
            return "Instrucao Expressao";
        }
        break;
        case TipoNo::ATRIBUICAO:
        {
            return "Atribuicao";
        }
        break;
        case TipoNo::OPERACAO_BINARIA:
        {
            return "Operacao Binaria";
        }
        break;
        case TipoNo::OPERACAO_UNARIA:
        {
            return "Operacao Unaria";
        }
        break;
        case TipoNo::OPERACAO_TERCIARIA:
        {
            return "Operacao Terciaria";
        }
        break;
        case TipoNo::RETORNE:
        {
            return "Retorn";
        }
        break;
        case TipoNo::LEIA:
        {
            return "Leia";
        }
        break;
        case TipoNo::ESCREVA:
        {
            return "Escreva";
        }
        break;
        case TipoNo::NOVA_LINHA:
        {
            return "Nova Linha";
        }
        break;
        case TipoNo::SE:
        {
            return "Se";
        }
        break;
        case TipoNo::SE_SENAO:
        {
            return "Se Senao";
        }
        break;
        case TipoNo::ENQUANTO:
        {
            return "Enquanto";
        }
        break;
        case TipoNo::CAST:
        {
            return "Cast";
        }
        break;
        case TipoNo::LISTA_EXPRESSOES:
        {
            return "Lista Expressoes";
        }
        break;
        case TipoNo::INICIALIZADOR_VETOR:
        {
            return "Inicializador Vetor";
        }
        break;
        case TipoNo::LISTA_INICIALIZADOR:
        {
            return "Lista Inicializador";
        }
        break;
    }
}
