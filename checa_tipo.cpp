#include "semantico.h"

extern int erro_compilador;

TipoVariavel::TipoVariavel checar_tipo(TabelaSimbolo &tabela, No* no)
{
    switch(no->tipoNo())
    {
        case IDENTIFICADOR_ESCALAR:
        {
            NIdentificadorEscalar *ident  = dynamic_cast<NIdentificadorEscalar*>(no);

            IteradorTabelaSimbolo itSim = tabela.find(*ident->nome);

            if(itSim==tabela.end())
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<ident->nome<<" não foi previamente declarado próximo a "<<ident->linha<<"\n";
                erro_compilador = true;
                ident->tipo = TIPO_ERRO;
            }
            else
            {
                if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_FUNCAO))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel escalar encontrado função próximo a "<<ident->linha<<"\n";
                    erro_compilador = true;
                    ident->tipo = TIPO_ERRO;
                }
                else if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_VARIAVEL_VETORIAL))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel escalar encontrado variavel vetorial próximo a "<<ident->linha<<"\n";
                    erro_compilador = true;
                    ident->tipo = TIPO_ERRO;
                }
                else
                {
                    ident->tipo = dynamic_cast<NDeclVarEscalar*>(itSim.value()->top()->no)->tipo;
                }
            }

            return ident->tipo;
        }
        break;
        case IDENTIFICADOR_VETORIAL:
        {
            NIdentificadorVetorial *ident  = dynamic_cast<NIdentificadorVetorial*>(no);

            IteradorTabelaSimbolo itSim = tabela.find(*ident->nome);

            if(itSim==tabela.end())
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<ident->nome<<" não foi previamente declarado próximo a "<<ident->linha<<"\n";
                erro_compilador = true;
                ident->tipo = TIPO_ERRO;
            }
            else
            {
                if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_FUNCAO))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado função próximo a "<<ident->linha<<"\n";
                    erro_compilador = true;
                    ident->tipo = TIPO_ERRO;
                }
                else if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_VARIAVEL_ESCALAR))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado variavel escalar próximo a "<<ident->linha<<"\n";
                    erro_compilador = true;
                    ident->tipo = TIPO_ERRO;
                }
                else
                {
                    NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(itSim.value()->top()->no);

                    //Checa para ver se o identificador possui as mesmas dimensoes do vetor declarado...
                    if(var->dimensoes->size()!=ident->indice->size())
                    {
                        //mensagem de erro...
                        CompInfo::err()<<"[ERRO SEMANTICO] Variavel vetorial apresenta "<<var->dimensoes->size()<<" dimensões próximo a "<<var->linha<<" enquanto que o identificador vetorial contém "<<ident->indice->size()<<" dimensões próximo a "<<ident->linha<<"\n";
                        erro_compilador = true;
                        ident->tipo = TIPO_ERRO;
                    }

                    bool resultado = true;

                    //Checa o tipo do indice para ver se é inteiro ou char...
                    for(IteradorExpressao it = ident->indice->begin(); it!= ident->indice->end(); ++it)
                    {
                        resultado &= (checar_tipo(tabela, (No*)(*it)) == TIPO_INT || checar_tipo(tabela, (No*)(*it)) == TIPO_CAR);
                    }

                    if(resultado)
                    {
                        ident->tipo = var->tipo;
                    }
                    else
                    {
                        //mensagem de erro...
                        CompInfo::err()<<"[ERRO SEMANTICO] Índice do vetor não é INT ou CAR próximo a "<<ident->linha<<"\n";
                        erro_compilador = true;
                        ident->tipo = TIPO_ERRO;
                    }
                }
            }
            return ident->tipo;
        }
        break;
        case LISTA_EXPRESSOES:
        {
            NListaExpressoes *list  = dynamic_cast<NListaExpressoes*>(no);

            for(int i=0; i<(list->expressoes->size()-1); ++i)
            {
                checar_tipo(tabela, (No*) list->expressoes->at(i));
            }

            list->tipo = checar_tipo(tabela, (No*) list->expressoes->at(list->expressoes->size()-1));

            return list->tipo;
        }
        break;
        case CHAMADA_FUNCAO:
        {
            NChamadaFuncao* cham = dynamic_cast<NChamadaFuncao*>(no);

            IteradorTabelaSimbolo itSim = tabela.find(*cham->nome);

            if(itSim==tabela.end())
            {
                CompInfo::err()<<"[ERRO SEMANTICO] função "<<cham->nome<<" não foi preveamente declarado próximo a "<<cham->nome<<"\n";
                erro_compilador = true;
                cham->tipo = TIPO_ERRO;
            }
            else
            {
                if(CHECA_NO(itSim.value()->top()->no , DECLARACAO_VARIAVEL_ESCALAR))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado função encontrado variavel escalar próximo a "<<cham->linha<<"\n";
                    erro_compilador = true;
                    cham->tipo = TIPO_ERRO;
                }
                else if(CHECA_NO(itSim.value()->top()->no , DECLARACAO_VARIAVEL_VETORIAL))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Esperado função encontrado variavel vetorial próximo a "<<cham->linha<<"\n";
                    erro_compilador = true;
                    cham->tipo = TIPO_ERRO;
                }
                else
                {
                    NDeclaracaoFuncao* func = dynamic_cast<NDeclaracaoFuncao*>(itSim.value()->top()->no);

                    if(func->parametros->size()!=cham->argumentos->size())
                    {
                        CompInfo::err()<<"[ERRO SEMANTICO] Esperado "<<func->parametros->size()<<" parametros, porém foi encontrado "<<cham->argumentos->size()<<" argumentos na função "<<cham->nome<<" próximo a "<<cham->linha<<"\n";
                        erro_compilador = true;
                        cham->tipo = TIPO_ERRO;
                    }
                    else
                    {
                        bool resultado = true;

                        //Checa cada parametro da funcao definida para ver se os argumentos passados batem...

                        for(int i=0; i<func->parametros->size(); i++)
                        {
                            resultado &= checar_chamada(tabela, func->parametros->at(i), cham->argumentos->at(i));
                        }

                        if(!resultado)
                        {
                            erro_compilador = true;
                            cham->tipo = TIPO_ERRO;
                        }
                        else
                            cham->tipo = func->tipo;
                    }
                }
            }
            return cham->tipo;
        }
        break;
        case ATRIBUICAO:
        {
            NAtribuicao* atrib = dynamic_cast<NAtribuicao*>(no);

            TipoVariavel::TipoVariavel lhs = checar_tipo(tabela, (No*) atrib->lhs);
            TipoVariavel::TipoVariavel rhs = checar_tipo(tabela, (No*) atrib->rhs);

            if(lhs==TIPO_ERRO||lhs==TIPO_PALAVRA||lhs==TIPO_NULO||lhs==TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador esquerdo do tipo "<<nome_tipo(lhs)<<" próximo a "<<atrib->linha<<"\n";
                erro_compilador = true;
                atrib->tipo = TIPO_ERRO;
            }

            if(rhs==TIPO_ERRO||rhs==TIPO_PALAVRA||rhs==TIPO_NULO||rhs==TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador direito do tipo "<<nome_tipo(rhs)<<" próximo a "<<atrib->linha<<"\n";
                erro_compilador = true;
                atrib->tipo = TIPO_ERRO;
            }

            if(NCHECA_NO(atrib->lhs, TipoNo::IDENTIFICADOR_ESCALAR) && NCHECA_NO(atrib->lhs, TipoNo::IDENTIFICADOR_VETORIAL))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador esquerdo do tipo não identificador próximo a "<<atrib->linha<<"\n";
                erro_compilador = true;
                atrib->tipo = TIPO_ERRO;
            }

            if(!erro_compilador)
            {
                if(atrib->op==DIV_ATRIBUICAO||atrib->op==POT_ATRIBUICAO)
                {
                    if(lhs!=TIPO_REAL)
                    {
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }
                    else
                        atrib->tipo = TIPO_REAL;//ESTRITAMENTE REAL
                }
                else if(atrib->op==MULT_ATRIBUICAO||atrib->op==ADICAO_ATRIBUICAO||atrib->op==SUBTRACAO_ATRIBUICAO)
                {
                    //CAR > INT > REAL
                    if(lhs!=TIPO_REAL&&rhs==TIPO_REAL)
                    {
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }

                    if(lhs==TIPO_CAR&&rhs==TIPO_INT)
                    {
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }

                    atrib->tipo = lhs;
                }
                else
                    if(
                        atrib->op==ESQ_ATRIBUICAO
                        ||atrib->op==DIR_ATRIBUICAO
                        ||atrib->op==E_ATRIBUICAO
                        ||atrib->op==XOR_ATRIBUICAO
                        ||atrib->op==OU_ATRIBUICAO
                        ||atrib->op==MOD_ATRIBUICAO
                    )
                {
                    //ESTRITAMENTE INTEIRO...
                    if(rhs==TIPO_REAL||lhs==TIPO_REAL)
                    {
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }

                    if(lhs!=TIPO_INT)
                    {
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }

                    atrib->tipo = TIPO_INT;

                }
                else if(atrib->op==ATRIBUICAO_OP&&(!erro_compilador))
                {
                    if(lhs==TIPO_INT&&rhs==TIPO_REAL)
                    {
                        CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador esquerdo do tipo INT enquanto que o operador direito é do tipo REAL próximo a "<<atrib->linha<<"\n";
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }

                    if(lhs==TIPO_CAR&&(rhs==TIPO_REAL||rhs==TIPO_INT))
                    {
                        CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador esquerdo do tipo "<<nome_tipo(lhs)<<" enquanto que o operador direito é do tipo "<<nome_tipo(rhs)<<" próximo a "<<atrib->linha<<"\n";
                        atrib->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }
                }
            }

            return atrib->tipo;
        }
        break;
        case OPERACAO_BINARIA:
        {
            NOperacaoBinaria* bin = dynamic_cast<NOperacaoBinaria*>(no);

            TipoVariavel::TipoVariavel lhs = checar_tipo(tabela, (No*) bin->lhs);
            TipoVariavel::TipoVariavel rhs = checar_tipo(tabela, (No*) bin->rhs);

            if(lhs==TIPO_ERRO||lhs==TIPO_PALAVRA||lhs==TIPO_NULO||lhs==TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador esquerdo do tipo "<<nome_tipo(lhs)<<" próximo a "<<bin->linha<<"\n";
                erro_compilador = true;
                bin->tipo = TIPO_ERRO;
            }

            if(rhs==TIPO_ERRO||rhs==TIPO_PALAVRA||rhs==TIPO_NULO||rhs==TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador direito do tipo "<<nome_tipo(rhs)<<" próximo a "<<bin->linha<<"\n";
                erro_compilador = true;
                bin->tipo = TIPO_ERRO;
            }

            if(!erro_compilador)
            {
                if(bin->op==Operador::DIV_OP||bin->op==Operador::POT_OP)
                {
                    //ESTRITAMENTE REAL
                    bin->tipo = TIPO_REAL;
                }
                else if(bin->op==Operador::SOM_OP||bin->op==Operador::SUB_OP||bin->op==Operador::MULT_OP)
                {
                    //REAL > INT E INT > CAR
                    if(lhs==TIPO_REAL||rhs==TIPO_REAL)
                        bin->tipo = TIPO_REAL;
                    else if(lhs==TIPO_INT||rhs==TIPO_INT)
                        bin->tipo = TIPO_INT;
                    else
                        bin->tipo = TIPO_CAR;
                }
                else
                    if(
                        bin->op==Operador::EQ_OP
                        ||bin->op==Operador::OU_OP
                        ||bin->op==Operador::E_OP
                        ||bin->op==Operador::OU_BIT_OP
                        ||bin->op==Operador::E_BIT_OP
                        ||bin->op==Operador::XOR_BIT_OP
                        ||bin->op==Operador::NE_OP
                        ||bin->op==Operador::BT_OP
                        ||bin->op==Operador::LT_OP
                        ||bin->op==Operador::REST_OP
                        ||bin->op==Operador::LE_OP
                        ||bin->op==Operador::GE_OP
                        ||bin->op==Operador::ESQ_OP
                        ||bin->op==Operador::DIR_OP
                    )
                {
                    //ESTRITAMENTE INTEIRO...
                    if(lhs==TIPO_REAL||rhs==TIPO_REAL)
                    {
                        bin->tipo = TIPO_ERRO;
                        erro_compilador = true;
                    }
                    bin->tipo = TIPO_INT;
                }
            }

            return bin->tipo;
        }
        break;
        case OPERACAO_UNARIA:
        {
            NOperacaoUnaria* uni = dynamic_cast<NOperacaoUnaria*>(no);

            TipoVariavel::TipoVariavel rhs = checar_tipo(tabela, (No*) uni->rhs);

            if(rhs==TIPO_ERRO||rhs==TIPO_PALAVRA||rhs==TIPO_NULO||rhs==TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o valor do tipo "<<nome_tipo(rhs)<<" próximo a "<<uni->linha<<"\n";
                erro_compilador = true;
                uni->tipo = TIPO_ERRO;
            }

            if(rhs==TIPO_CAR&&(uni->op == Operador::NEG_OP||uni->op == Operador::MIN_OP))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar a operação de NEGACAO(~ ou !) ou NEGATIVO(-) sobre valores do tipo CAR próximo a "<<uni->linha<<"\n";
                erro_compilador = true;
                uni->tipo = TIPO_ERRO;
            }

            if(!erro_compilador)
            {
                if(uni->op==Operador::INC_POS_OP||uni->op==Operador::DEC_POS_OP||uni->op==Operador::INC_PRE_OP||uni->op==Operador::DEC_PRE_OP)
                {
                    if(NCHECA_NO(uni->rhs, TipoNo::IDENTIFICADOR_ESCALAR) && NCHECA_NO(uni->rhs, TipoNo::IDENTIFICADOR_VETORIAL))
                    {
                        CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador direito do tipo não identificador próximo a "<<uni->linha<<"\n";
                        erro_compilador = true;
                        uni->tipo = TIPO_ERRO;
                    }
                }

                uni->tipo = rhs;
            }

            return uni->tipo;
        }
        break;
        case OPERACAO_TERCIARIA:
        {
            NOperacaoTerciaria* ter = dynamic_cast<NOperacaoTerciaria*>(no);

            TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, (No*) ter->expressao);

            if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO||tipo==TIPO_NOVALINHA)
            {
                //error
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar a expressão próximo a "<<ter->linha<<"\n";
                erro_compilador = true;
                ter->tipo = TIPO_ERRO;
            }

            TipoVariavel::TipoVariavel ifexpr = checar_tipo(tabela, (No*) ter->ifExpr);
            TipoVariavel::TipoVariavel elsexpr = checar_tipo(tabela, (No*) ter->elsExpr);


            if(ifexpr==TIPO_ERRO||ifexpr==TIPO_PALAVRA||ifexpr==TIPO_NULO||tipo==TIPO_NOVALINHA)
            {
                //error
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar a expressão próximo a "<<ter->ifExpr->linha<<"\n";
                erro_compilador = true;
                ter->tipo = TIPO_ERRO;
            }

            if(elsexpr==TIPO_ERRO||elsexpr==TIPO_PALAVRA||elsexpr==TIPO_NULO||tipo==TIPO_NOVALINHA)
            {
                //error
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar a expressão próximo a "<<ter->elsExpr->linha<<"\n";
                erro_compilador = true;
                ter->tipo = TIPO_ERRO;
            }

            if(!erro_compilador)
            {
                if(ifexpr==TIPO_REAL||elsexpr==TIPO_REAL)
                {
                    ter->tipo = TIPO_REAL;
                }
                else if(ifexpr==TIPO_INT||elsexpr==TIPO_INT)
                {
                    ter->tipo = TIPO_INT;
                }
                else
                {
                    ter->tipo = TIPO_CAR;
                }
            }

            return ter->tipo;
        }
        break;
        case CAST:
        {
            NCast* cast = dynamic_cast<NCast*>(no);
            TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, (No*) cast->expressao);
            if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO||cast->tipo==TIPO_NULO||tipo==TIPO_NOVALINHA)
                return TIPO_ERRO;
            return cast->tipo;
        }
        break;
        case NOVA_LINHA:
        {
            return TIPO_NOVALINHA;
        }
        case INTEIRO:
        {
            //NInteger* inteiro = dynamic_cast<NInteger*>(node);
            return TIPO_INT;
        }
        break;
        case CARACTER:
        {
            //NChar* character = dynamic_cast<NChar*>(node);
            return TIPO_CAR;
        }
        break;
        case REAL:
        {
            //NChar* character = dynamic_cast<NChar*>(node);
            return TIPO_REAL;
        }
        break;
        case PALAVRA_LITERAL:
        {
            //NString* str = dynamic_cast<NString*>(node);
            return TIPO_PALAVRA;
        }
        break;
    }

    return TIPO_ERRO;
}

bool checa_tipo_init(TabelaSimbolo &tabela, No* no, TipoVariavel::TipoVariavel tipo)
{
    if(CHECA_NO(no, LISTA_INICIALIZADOR))
    {
        NListaInicializador *list  = dynamic_cast<NListaInicializador*>(no);

        bool resultado = true;

        for(int i=0; i<list->expressoes->size(); ++i)
        {
            resultado &= checa_tipo_init(tabela, (No*) list->expressoes->at(i), tipo);
        }

        if(resultado)
            list->tipo = tipo;
        else
            list->tipo = TIPO_ERRO;

        return resultado;
    }
    else
    {
        return checar_tipo(tabela, no) == tipo;
    }
}

