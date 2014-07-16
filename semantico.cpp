#include "semantico.h"

extern int erro_compilador;

IteradorTabelaSimbolo analise_semantica(TabelaSimbolo &tabela, No* no, int profundidade, No* funcao)
{
    if(CHECA_NO(no, BLOCO))
    {
        NBloco *bloco = dynamic_cast<NBloco*>(no);
        Remover remover;

        for(IteradorInstrucao it = bloco->instrucoes->begin(); it != bloco->instrucoes->end(); ++it)
        {
            if(CHECA_NO((*it), BLOCO))
            {
                analise_semantica(tabela, (No*)(*it), profundidade+1, funcao);
            }
            else
            {
                IteradorTabelaSimbolo itSim = analise_semantica(tabela, (No*)(*it), profundidade, funcao);

                if(itSim != tabela.end())
                {
                    remover.push_back(itSim);
                }
            }
        }

        for(IteratorRemover it = remover.begin(); it!= remover.end(); ++it)
        {
            IteradorTabelaSimbolo itSim = (*it);

            delete itSim.value()->top();
            itSim.value()->pop();

            if(itSim.value()->empty())
            {
                delete itSim.value(); // remove a pilha
                tabela.erase(itSim);
            }
        }

        return tabela.end();
    }
    else if(CHECA_NO(no, DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO(no, DECLARACAO_VARIAVEL_VETORIAL))
    {
        NDeclaracaoVariavel *var = dynamic_cast<NDeclaracaoVariavel*>(no);

        IteradorTabelaSimbolo itSim = tabela.find(*var->nome);

        if(itSim == tabela.end())
        {
            tabela.insert(*var->nome, new PilhaSimbolo());
            itSim = tabela.find(*var->nome); //procuro novamente para q ele aponta para este novo elemento...
        }

        if((!itSim.value()->empty()) && itSim.value()->top()->profundidade == profundidade)
        {
            if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_FUNCAO))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<var->nome<<" já foi preveamente declarado como sendo outro tipo de simbolo próximo a linha "<<var->linha<<"\n";
                erro_compilador = true;
            }
            else
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<var->nome<<" já foi preveamente declarado próximo a linha "<<var->linha<<"\n";
                erro_compilador = true;
            }

            return tabela.end();
        }
        else
        {
            if(CHECA_NO(no, DECLARACAO_VARIAVEL_VETORIAL)&&(!checa_vetor_dimensao(dynamic_cast<NDeclVarVetorial*>(no)->eParametro, (NDeclVarVetorial*)no)))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Variavel vetorial "<<var->nome<<" não foi declarado corretamente as dimensões do vetor próximo a linha "<<var->linha<<"\n";
                erro_compilador = true;
                return tabela.end();
            }
            else
            {
                itSim.value()->push(new Simbolo(var, profundidade));
                return itSim;
            }
        }
    }
    else if(CHECA_NO(no, DECLARACAO_FUNCAO))
    {
        NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(no);

        IteradorTabelaSimbolo itSim = tabela.find(*func->nome);

        if(itSim==tabela.end())
        {
            tabela.insert(*func->nome, new PilhaSimbolo());
            itSim = tabela.find(*func->nome); //procuro novamente para q ele aponta para este novo elemento...
        }

        if((!itSim.value()->empty()) && itSim.value()->top()->profundidade == profundidade)
        {

            if(CHECA_NO(itSim.value()->top()->no , DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO(itSim.value()->top()->no , DECLARACAO_VARIAVEL_VETORIAL))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Função "<<func->nome<<" já foi declarado como sendo outro tipo de simbolo próximo a linha "<<func->linha<<"\n";
                erro_compilador = true;
            }
            else
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Função "<<func->nome<<" já foi preveamente declarado próximo a linha "<<func->linha<<"\n";
                erro_compilador = true;
            }

            itSim = tabela.end();
        }
        else
        {
            itSim.value()->push(new Simbolo(func, profundidade));
        }

        Remover remover;

        //insiro as variaveis locais
        for(IteradorVariavel it = func->parametros->begin(); it!= func->parametros->end(); it++)
        {
            IteradorTabelaSimbolo itSimVar = analise_semantica(tabela, (No*) (*it), profundidade+1, funcao);

            if(itSimVar != tabela.end())
            {
                remover.push_back(itSimVar);
            }
        }

        //executo para o bloco da função agora
        analise_semantica(tabela, (No*) func->bloco, profundidade+1, no);

        for(IteratorRemover it = remover.begin(); it!= remover.end(); ++it)
        {
            IteradorTabelaSimbolo itSim = (*it);

            delete itSim.value()->top();
            itSim.value()->pop();

            if(itSim.value()->empty())
            {
                delete itSim.value(); // remove a pilha
                tabela.erase(itSim);
            }
        }

        if(func->possuiRetorno==false&&func->tipo!=TIPO_NULO)
        {
            CompInfo::err()<<"[ERRO SEMANTICO] Nenhum retorno foi definido para "<<func->nome<<" esperado tipo "<<nome_tipo(func->tipo)<<" próximo a linha "<<func->linha<<"\n";
            erro_compilador = true;
        }

        return itSim;
    }
    else if(CHECA_NO(no, INSTRUCAO_EXPRESSAO))
    {
        return analise_semantica(tabela, (No*) dynamic_cast<NInstrucaoExpressao*>(no)->expressao, profundidade+1, funcao);
    }
    else if(CHECA_NO(no, RETORNE))
    {
        NRetorne *ret = dynamic_cast<NRetorne*>(no);

        NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(funcao);

        TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ((No*) ret->expressao));

        // Se expressao for uma expressão vazia e o tipo da função for nulo eu não caio na checagem tipo != func->tipo
        // por que tipo está como TIPO_ERRO por que checa_tipo() não verifica expressão e por isso retornará TIPO_ERRO
        if(ret->expressao->tipoNo()!=TipoNo::EXPRESSAO || func->tipo != TipoVariavel::TIPO_NULO)
        {
            if(tipo != func->tipo)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Esperado retorno do tipo "<<nome_tipo(func->tipo)<<" encontrado do tipo "<<nome_tipo(tipo)<<" próximo a linha "<<ret->linha<<"\n";
                erro_compilador = true;
            }
        }

        func->possuiRetorno = true;

        return tabela.end();
    }
    else if(CHECA_NO(no, LEIA))
    {
        NLeia *ler = dynamic_cast<NLeia*>(no);

        ListaExpressao *list = dynamic_cast<NListaExpressoes*>(ler->expressao)->expressoes;

        TipoVariavel::TipoVariavel tipo;

        for(int i = 0; i<list->size(); ++i)
        {
            No* r = ultimo_parametro(tabela, list->at(i));

            tipo = checar_tipo(tabela, ultimo_parametro(tabela, r));

            if(tipo == TIPO_ERRO || tipo == TIPO_NULO || tipo== TIPO_PALAVRA|| tipo == TIPO_NOVALINHA)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação encontrado valor tipo "<<nome_tipo(tipo)<<" próximo a linha "<<ler->linha<<"\n";
                erro_compilador = true;
            }

            if(CHECA_NO(r, CAST))
            {
                No* r1 = ultimo_parametro(tabela, dynamic_cast<NCast*>(r)->expressao);

                tipo = checar_tipo(tabela, ultimo_parametro(tabela, r1));

                if(tipo == TIPO_ERRO || tipo == TIPO_NULO || tipo== TIPO_PALAVRA|| tipo == TIPO_NOVALINHA)
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação encontrado valor tipo "<<nome_tipo(tipo)<<" próximo a linha "<<ler->linha<<"\n";
                    erro_compilador = true;
                }

                if(NCHECA_NO(r1, IDENTIFICADOR_ESCALAR)&&NCHECA_NO(r, IDENTIFICADOR_VETORIAL))
                {
                    CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador do tipo não identificador próximo a linha "<<ler->linha<<"\n";
                    erro_compilador = true;
                }
            }
            else if(NCHECA_NO(r, IDENTIFICADOR_ESCALAR)&&NCHECA_NO(r, IDENTIFICADOR_VETORIAL))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação sobre o operador do tipo não identificador próximo a linha "<<ler->linha<<"\n";
                erro_compilador = true;
            }
        }

        return tabela.end();
    }
    else if(CHECA_NO(no, ESCREVA))
    {
        NEscreva *escreve = dynamic_cast<NEscreva*>(no);

        ListaExpressao *list = dynamic_cast<NListaExpressoes*>(escreve->expressao)->expressoes;

        TipoVariavel::TipoVariavel tipo;

        for(int i = 0; i<list->size(); ++i)
        {
            tipo = checar_tipo(tabela, ultimo_parametro(tabela, list->at(i)));

            if(tipo == TIPO_ERRO || tipo == TIPO_NULO)
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel realizar está operação encontrado valor tipo "<<nome_tipo(tipo)<<" próximo a linha "<<escreve->linha<<"\n";
                erro_compilador = true;
            }
        }

        return tabela.end();
    }
    else if(CHECA_NO(no, NOVA_LINHA))
    {
        return tabela.end();
    }
    else if(CHECA_NO(no, SE))
    {
        NSe *ifinstr = dynamic_cast<NSe*>(no);

        TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ifinstr->expressao);

        if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO)
        {
            CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar está expressão encontrado valor do tipo "<<nome_tipo(tipo)<<" próximo a linha "<<ifinstr->linha<<"\n";
            erro_compilador = true;
        }

        analise_semantica(tabela,(No*) ifinstr->instrucao, profundidade+1, funcao);

        return tabela.end();
    }
    else if(CHECA_NO(no, SE_SENAO))
    {
        NSeSenao *ifinstr = dynamic_cast<NSeSenao*>(no);

        TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, ifinstr->expressao);

        if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO)
        {
            CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar está expressão encontrado valor do tipo "<<nome_tipo(tipo)<<" próximo a linha "<<ifinstr->linha<<"\n";
            erro_compilador = true;
        }

        analise_semantica(tabela,(No*) ifinstr->instrucaoSe, profundidade+1, funcao);
        analise_semantica(tabela,(No*) ifinstr->instrucaoSenao, profundidade+1, funcao);

        return tabela.end();
    }
    else if(CHECA_NO(no, ENQUANTO))
    {
        NEnquanto *enq = dynamic_cast<NEnquanto*>(no);

        TipoVariavel::TipoVariavel tipo = checar_tipo(tabela, enq->expressao);

        if(tipo==TIPO_ERRO||tipo==TIPO_PALAVRA||tipo==TIPO_NULO)
        {
            CompInfo::err()<<"[ERRO SEMANTICO] Não é possivel avaliar está expressão encontrado valor do tipo "<<nome_tipo(tipo)<<" próximo a linha "<<enq->linha<<"\n";
            erro_compilador = true;
        }

        analise_semantica(tabela, (No*)enq->instrucao, profundidade+1, funcao);

        return tabela.end();
    }
    else if(CHECA_NO(no, INICIALIZADOR_VETOR))
    {
        NInicializadorVetor *list = dynamic_cast<NInicializadorVetor*>(no);

        IteradorTabelaSimbolo itSim = tabela.find(*list->nome);

        if(itSim==tabela.end())
        {
            CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<list->nome<<" não foi preveamente declarado próximo a linha "<<list->linha<<"\n";
            erro_compilador = true;
        }
        else
        {

            if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_FUNCAO))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado função próximo a linha "<<list->linha<<"\n";
                erro_compilador = true;
            }
            else if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_VARIAVEL_ESCALAR))
            {
                CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado variavel escalar próximo a linha "<<list->linha<<"\n";
                erro_compilador = true;
            }
            else
            {
                NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(itSim.value()->top()->no);

                bool resultado = true;

                //Checa o tipo do indice para ver se é inteiro
                for(IteradorExpressao it = list->init->begin(); it!= list->init->end(); ++it)
                {
                    resultado &= checa_tipo_init(tabela, (No*)(*it), var->tipo);
                }

                if(!resultado)
                {
                    //mensagem de erro...
                    CompInfo::err()<<"[ERRO SEMANTICO] Valores para inicializar o vetor não coincidem com o tipo esperado "<<nome_tipo(var->tipo)<<" próximo a linha "<<list->linha<<"\n";
                    erro_compilador = true;
                }
            }
        }

        return tabela.end();
    }
    //Todos esses aqui já foram implementados em checar_tipo então eu o chamo e ignoro o retorno...
    else if(
        CHECA_NO(no, CHAMADA_FUNCAO)||
        CHECA_NO(no, IDENTIFICADOR_ESCALAR)||
        CHECA_NO(no, IDENTIFICADOR_VETORIAL)||
        CHECA_NO(no, ATRIBUICAO)||
        CHECA_NO(no, OPERACAO_BINARIA)||
        CHECA_NO(no, OPERACAO_UNARIA)||
        CHECA_NO(no, OPERACAO_TERCIARIA)||
        CHECA_NO(no, CAST) ||
        CHECA_NO(no, LISTA_EXPRESSOES)
    )
    {
        checar_tipo(tabela, no);
        return tabela.end();
    }
    else if(
        CHECA_NO(no, INTEIRO) ||
        CHECA_NO(no, CARACTER) ||
        CHECA_NO(no, REAL) ||
        CHECA_NO(no, PALAVRA_LITERAL)
    )
    {
        CompInfo::err()<<"[ERRO SEMANTICO] Esperado nada encontrado "<<(tipo_no(no))<<" próximo a linha "<<no->linha<<"\n";
        erro_compilador = true;
        return tabela.end();
    }

    return tabela.end();
}

