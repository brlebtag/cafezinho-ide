#include "semantico.h"

QString nome_tipo(TipoVariavel::TipoVariavel tipo)
{
    switch(tipo)
    {
        case TipoVariavel::TIPO_ERRO:
        {
            return "ERRO";
        }
        break;
        case TipoVariavel::TIPO_CAR:
        {
            return "CAR";
        }
        break;
        case TipoVariavel::TIPO_INT:
        {
            return "INT";
        }
        break;
        case TipoVariavel::TIPO_REAL:
        {
            return "REAL";
        }
        break;
        case TipoVariavel::TIPO_PALAVRA:
        {
            return "PALAVRA LITERAL";
        }
        break;
        case TipoVariavel::TIPO_NULO:
        {
            return "NULO";
        }
        break;
        case TipoVariavel::TIPO_NOVALINHA:
        {
            return "NOVA LINHA";
        }
        break;

    }
}

QString tipo_no(No * no)
{
    switch(no->tipoNo())
    {
        case INTEIRO:
        {
            return "INTEIRO CONSTANTE";
        }
        break;
        case CARACTER:
        {
            return "CARACTER CONSTANTE";
        }
        break;
        case REAL:
        {
            return "REAL CONSTANTE";
        }
        break;
        case PALAVRA_LITERAL:
        {
            return "PALAVRA LITERAL";
        }
        break;
        case IDENTIFICADOR_ESCALAR:
        {
            return "IDENTIFICADOR ESCALAR";
        }
        break;
        case IDENTIFICADOR_VETORIAL:
        {
            return "IDENTIFICADOR VETORIAL";
        }
        break;
        case CHAMADA_FUNCAO:
        {
            return "CHAMADA FUNCAO";
        }
        break;
        case INSTRUCAO_EXPRESSAO:
        {
            return "INSTRUCAO EXPRESSAO";
        }
        break;
        case ATRIBUICAO:
        {
            return "ATRIBUICAO";
        }
        break;
        case OPERACAO_BINARIA:
        {
            return "OPERACAO BINARIA";
        }
        break;
        case OPERACAO_UNARIA:
        {
            return "OPERACAO UNARIA";
        }
        break;
        case OPERACAO_TERCIARIA:
        {
            return "OPERACAO TERCIARIA";
        }
        break;
        case NOVA_LINHA:
        {
            return "NOVA LINHA";
        }
        break;
        case CAST:
        {
            return "CAST";
        }
        break;
        case DECLARACAO_FUNCAO:
        {
            return "DECLARACAO DE FUNCAO";
        }
        break;
        case DECLARACAO_VARIAVEL_ESCALAR:
        {
            return "DECLARACAO DE VARIAVEL ESCALAR";
        }
        break;
        case DECLARACAO_VARIAVEL_VETORIAL:
        {
            return "DECLARACAO DE VARIAVEL VETORIAL";
        }
        break;
        case EXPRESSAO:
        {
            return "EXPRESSAO";
        }
        break;
        case LISTA_EXPRESSOES:
        {
            return "LISTA DE EXPRESSOES";
        }
        break;
    }
}
