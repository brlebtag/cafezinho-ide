#include "GerarCodigo.h"

void gerar_codigo(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao)
{
    int linha_decl_var_atual = -1; //contém a linha da ultima declaração
    /*
     * Eu irei da break apenas na primeira instrucao de declaração de variavel (na arvore
     * para cada declaracao de variavel possui um nó porém eu só vou dar break para a primeira
     * ocorrencia naquela linha) esta variavel de controle gerencia isto!
     */

    switch(no->tipoNo())
    {
        case TipoNo::BLOCO:
        {
            NBloco *bloco = dynamic_cast<NBloco*>(no);
            RemoverRef remover;
            int i = 1;

            if(profundidade == 0)
            {
                /*
                 *		Cabeçario do programa Inicio:
                 *		- Variaveis Globais
                 *		- programa()
                 *		- Desaloca variaveis Globais
                 *		- Parar Programa
                 */

                // rotulo[0] endereco do programa()
                vm.rotulo.push_back(new int(-1));
                //rotulo[1] endereco de encerramento do programa...
                vm.rotulo.push_back(new int(0));
                //Variaveis Globais
                for(IteradorInstrucao it = bloco->instrucoes->begin(); it!= bloco->instrucoes->end(); ++it)
                {
                    if(CHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_VETORIAL))
                    {
                        //se tiver alguma coisa assim int a,b,c,d todos vão estar na "mesma linha" porem só vai ficar
                        //para uma vez....
                        if(CompInfo::isDebug())
                        {
                            if(linha_decl_var_atual!=(*it)->linha)
                            {
                                linha_decl_var_atual = (*it)->linha;
                                inserir_debug_instrucao(vm, (*it));
                            }
                        }
                        Alocado resultado = alocar_variavel(vm, tabela, (*it), profundidade, offset + i);
                        i += resultado.first;
                        remover.push_back(resultado.second);
                    }
                }

                //empilho o ponteiro da base da pilha(que funciona como o ponteiro que aponta para o inicio do frame...)
                empilha(vm, vm.bp);
                //chama main...
                invoca(vm, (*vm.rotulo[0]));
                (*vm.rotulo[1]) = vm.codigo.size();
                if(i>1)
                    dec_pp(vm, i-1);
                vm.codigo.push_back(new IParar());

                //Funcoes.. ou atribuicoes...
                for(IteradorInstrucao it = bloco->instrucoes->begin(); it!= bloco->instrucoes->end(); ++it)
                {
                    if(NCHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_ESCALAR) && NCHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_VETORIAL))
                    {
                        //Não precisa colocar parada no bloco....
                        if(CompInfo::isDebug()&&NCHECA_NO((*it), TipoNo::INICIALIZADOR_VETOR)&&NCHECA_NO((*it), TipoNo::BLOCO))
                        {
                            if(NCHECA_NO((*it), TipoNo::ATRIBUICAO))
                            {
                                inserir_debug_instrucao(vm, (*it));
                            }
                            else if(reinterpret_cast<NAtribuicao*>(*it)->inicializa_variavel!=true)
                            {
                                inserir_debug_instrucao(vm, (*it));
                            }
                        }

                        //Reinicializa o offset...
                        gerar_codigo(vm, tabela, (*it), profundidade, 0, funcao);
                    }
                }
            }
            else
            {
                for(IteradorInstrucao it = bloco->instrucoes->begin(); it!= bloco->instrucoes->end(); ++it)
                {
                    if(CHECA_NO((*it), TipoNo::BLOCO))
                    {
                        //Não precisa colocar parada no bloco....
                        gerar_codigo(vm, tabela, (*it), profundidade +1, offset + i -1, funcao);
                    }
                    else if(CHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_ESCALAR) || CHECA_NO((*it), TipoNo::DECLARACAO_VARIAVEL_VETORIAL))
                    {
                        //se tiver alguma coisa assim int a,b,c,d todos vão estar na "mesma linha" porem só vai ficar
                        //para uma vez....
                        if(CompInfo::isDebug())
                        {
                            if(linha_decl_var_atual!=(*it)->linha)
                            {
                                linha_decl_var_atual = (*it)->linha;
                                inserir_debug_instrucao(vm, (*it));
                            }
                        }
                        Alocado resultado = alocar_variavel(vm, tabela, (*it), profundidade, offset + i);
                        i += resultado.first;
                        remover.push_back(resultado.second);
                    }
                    else
                    {
                        if(CompInfo::isDebug()&&NCHECA_NO((*it), TipoNo::INICIALIZADOR_VETOR)&&NCHECA_NO((*it), TipoNo::BLOCO))
                        {
                            if(NCHECA_NO((*it), TipoNo::ATRIBUICAO))
                            {
                                inserir_debug_instrucao(vm, (*it));
                            }
                            else if(reinterpret_cast<NAtribuicao*>(*it)->inicializa_variavel!=true)
                            {
                                inserir_debug_instrucao(vm, (*it));
                            }
                        }
                        gerar_codigo(vm, tabela, (*it), profundidade, offset + i -1 , funcao);
                    }
                }
            }

            for(IteradorRemoverRef it = remover.begin(); it!= remover.end(); ++it)
            {
                IteradorTabelaRef var = (*it);

                var.value().pop();

                if(var.value().isEmpty())
                {
                    tabela.erase(var);
                }
            }

            //desalocar variaveis locais alocadas...
            if(i>1&&profundidade>0)
                dec_pp(vm, i-1);
        }
        break;
        case TipoNo::DECLARACAO_FUNCAO:
        {
            NDeclaracaoFuncao *func = dynamic_cast<NDeclaracaoFuncao*>(no);

            int i = 1;

            RemoverRef remover;

            // bp = pp
            move(vm, vm.bp, vm.pp);

            IteradorTabelaRef it = tabela.find(*func->nome);

            if(it == tabela.end())
            {
                PilhaRef pilha;
                //offset da funcao será a posicao do vm.roluto. O vm.roluto guarda a posicao da primeira instrucao de Func()...
                //precisa ser assim por que tabela insere e remove seus elementos logo ira perder a informacao do inicio de func()
                //mas o rotulo sempre existe enquato o programa existir...
                if(func->nome->compare("programa")==0&&func->tipo==TipoVariavel::TIPO_NULO)
                {
                    (*vm.rotulo[0]) = vm.codigo.size()-1;
                    pilha.push(Referencia(no, profundidade, 0));
                }
                else
                {
                    vm.rotulo.push_back(new int(vm.codigo.size()-1));
                    pilha.push(Referencia(no, profundidade, vm.rotulo.size()-1));
                }
                tabela.insert(*func->nome, pilha);
                it = tabela.find(*func->nome);
            }
            else
            {
                //offset da funcao será a posicao da primeira instrucao da funcao dentro de codigo[]
                if(func->nome->compare("programa")==0&&func->tipo==TipoVariavel::TIPO_NULO)
                {
                    (*vm.rotulo[0]) = vm.codigo.size()-1;
                    it.value().push(Referencia(no, profundidade, 0, false));
                }
                else
                {
                    vm.rotulo.push_back(new int(vm.codigo.size()-1));
                    it.value().push(Referencia(no, profundidade, vm.rotulo.size()-1, false));
                }
            }

            // empilha er
            empilha(vm, vm.er);

            //Empilha de trás para frente...
            for(int i= func->parametros->size()-1; i>=0; --i)
            {
                Alocado aloc = alocar_variavel(vm, tabela, func->parametros->at(i), profundidade + 1, i+1, true);
                remover.push_back(aloc.second);
            }

            gerar_codigo(vm, tabela, func->bloco, profundidade+1, offset, func);

            for(IteradorRemoverRef it = remover.begin(); it!= remover.end(); ++it)
            {
                IteradorTabelaRef var = (*it);

                var.value().pop();

                if(var.value().isEmpty())
                {
                    tabela.erase(var);
                }
            }

            //verifica se a ultima instrucão é do tipo IRet se for não inseri o retorno denovo...
            if(dynamic_cast<IRet*>(vm.codigo[vm.codigo.size()-1])==NULL)
            {
                move(vm, vm.pp, vm.bp);
                carrega(vm, vm.er, vm.pp);
                int qtd = func->parametros->size();
                if(qtd>0)
                {
                    dec_pp(vm, qtd);
                }
                dec_pp(vm, 1);
                carrega(vm, vm.bp, vm.pp);
                ret(vm);
            }
        }
        break;
        case TipoNo::CHAMADA_FUNCAO:
        {
            NChamadaFuncao *cham = dynamic_cast<NChamadaFuncao*>(no);
            //empilho o ponteiro da base da pilha(que funciona como o ponteiro que aponta para o inicio do frame...)
            empilha(vm, vm.bp);

            for(int i = cham->argumentos->size() -1; i>=0; --i)
            {
                //Manda gerar o parametro it e salva ele em eax...
                gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, cham->argumentos->at(i), profundidade, offset, funcao), profundidade, offset, funcao);
                empilha(vm, vm.eax);
            }

            IteradorTabelaRef it = tabela.find(*cham->nome);

            invoca(vm, (*vm.rotulo[it.value().top().offset]));
        }
        break;
        case TipoNo::RETORNE:
        {
            NRetorne *retorno = dynamic_cast<NRetorne*>(no);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, retorno->expressao, profundidade, offset, funcao), profundidade, offset, funcao);
            move(vm, vm.pp, vm.bp);
            carrega(vm, vm.er, vm.pp);
            int qtd = dynamic_cast<NDeclaracaoFuncao*>(funcao)->parametros->size();
            if(qtd>0)
            {
                dec_pp(vm, qtd);
            }
            dec_pp(vm, 1);
            carrega(vm, vm.bp, vm.pp);
            ret(vm);
        }
        break;
        case TipoNo::IDENTIFICADOR_ESCALAR:
        {
            NIdentificadorEscalar *ident = dynamic_cast<NIdentificadorEscalar*>(no);

            IteradorTabelaRef itIdent = tabela.find(*ident->nome);

            Referencia ref = itIdent.value().top();

            if(ref.profundidade == 0)
            {
                if(ref.vetor)
                {
                    //carrega endereço de Ident[0] em eax
                    vm.codigo.push_back(new IMoveIm(vm.eax, CelulaMemoria(ref.offset)));
                    // adiciona pg + eax
                    vm.codigo.push_back(new IAdc(vm.eax, vm.pg, vm.eax));
                }
                else
                {
                    vm.codigo.push_back(new ICarrega(vm.eax, vm.pg, ref.offset));
                }
            }
            else
            {
                if(ref.parametro)
                {
                    vm.codigo.push_back(new ICarrega(vm.eax, vm.bp, (-ref.offset)));
                }
                else
                {
                    if(ref.vetor)
                    {
                        //carrega endereço de Ident[0] em eax
                        vm.codigo.push_back(new IMoveIm(vm.eax, CelulaMemoria(ref.offset)));
                        // adiciona bp + eax
                        vm.codigo.push_back(new IAdc(vm.eax, vm.bp, vm.eax));
                    }
                    else
                    {
                        vm.codigo.push_back(new ICarrega(vm.eax, vm.bp, ref.offset));
                    }
                }
            }
        }
        break;
        case TipoNo::IDENTIFICADOR_VETORIAL:
        {
            NIdentificadorVetorial *ident = dynamic_cast<NIdentificadorVetorial*>(no);

            IteradorTabelaRef itIdent = tabela.find(*ident->nome);

            Referencia ref = itIdent.value().top();

            gerar_indice(vm, tabela, no, profundidade, offset, funcao);

            // em eax está o valor de deslocamento do vetor, etc: a[valor]
            // ebx = eax
            vm.codigo.push_back( new IMove(vm.ebx, vm.eax));

            if(ref.profundidade == 0)
            {
                //carrega endereço de Ident[0] em eax
                vm.codigo.push_back(new IMoveIm(vm.eax, ref.offset));
                // adiciona pg + eax
                vm.codigo.push_back(new IAdc(vm.eax, vm.pg, vm.eax));
            }
            else
            {
                if(ref.parametro)
                {
                    vm.codigo.push_back(new ICarrega(vm.eax, vm.bp, (-ref.offset)));
                }
                else
                {
                    vm.codigo.push_back(new IAdcIm(vm.eax, vm.bp, ref.offset));
                }
            }

            vm.codigo.push_back(new IAdc(vm.eax, vm.eax, vm.ebx));
            vm.codigo.push_back(new ICarrega(vm.eax, vm.eax));
        }
        break;
        case TipoNo::SE:
        {
            NSe *se = dynamic_cast<NSe*>(no);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, se->expressao, profundidade, offset, funcao), profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &sair_se = (*vm.rotulo[vm.rotulo.size()-1]);
            //salta se nao for igual
            cmp_imm(vm, vm.eax, 0);
            seq(vm, sair_se);
            if(CompInfo::isDebug()&&NCHECA_NO(se->instrucao, TipoNo::BLOCO))
            {
                inserir_debug_instrucao(vm, se->instrucao);
            }
            gerar_codigo(vm, tabela, se->instrucao, profundidade, offset, funcao);
            //vm.codigo.size() -1 contém a ultima instrucao inserida... logo vm.codigo.size() é a proxima instrucao...
            sair_se = vm.codigo.size();

        }
        break;
        case TipoNo::SE_SENAO:
        {
            NSeSenao* seSenao = dynamic_cast<NSeSenao*>(no);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, seSenao->expressao, profundidade, offset, funcao), profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &senao = (*vm.rotulo[vm.rotulo.size()-1]);
            //salta se nao for igual
            cmp_imm(vm, vm.eax, 0);
            seq(vm, senao);
            if(CompInfo::isDebug()&&NCHECA_NO(seSenao->instrucaoSe, TipoNo::BLOCO))
            {
                inserir_debug_instrucao(vm, seSenao->instrucaoSe);
            }
            gerar_codigo(vm, tabela, seSenao->instrucaoSe, profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &sair_se = (*vm.rotulo[vm.rotulo.size()-1]);
            si(vm, sair_se);
            senao = vm.codigo.size();
            if(CompInfo::isDebug()&&NCHECA_NO(seSenao->instrucaoSenao, TipoNo::BLOCO))
            {
                inserir_debug_instrucao(vm, seSenao->instrucaoSenao);
            }
            gerar_codigo(vm, tabela, seSenao->instrucaoSenao, profundidade, offset, funcao);
            sair_se = vm.codigo.size();

        }
        break;
        case TipoNo::ENQUANTO:
        {
            NEnquanto *enq = dynamic_cast<NEnquanto*>(no);
            vm.rotulo.push_back(new int(vm.codigo.size()));
            int &loop = (*vm.rotulo[vm.rotulo.size()-1]);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, enq->expressao, profundidade, offset, funcao), profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &sair_loop = (*vm.rotulo[vm.rotulo.size()-1]);
            cmp_imm(vm, vm.eax, 0);
            seq(vm, sair_loop);
            if(CompInfo::isDebug()&&NCHECA_NO(enq->instrucao, TipoNo::BLOCO))
            {
                inserir_debug_instrucao(vm, enq->instrucao);
            }
            gerar_codigo(vm, tabela, enq->instrucao, profundidade, offset, funcao);
            si(vm, loop);
            sair_loop = vm.codigo.size();
        }
        break;
        case TipoNo::OPERACAO_TERCIARIA:
        {
            NOperacaoTerciaria *ter = dynamic_cast<NOperacaoTerciaria*>(no);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, ter->expressao, profundidade, offset, funcao), profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &senao = (*vm.rotulo[vm.rotulo.size()-1]);
            //salta se nao for igual
            cmp_imm(vm, vm.eax, CelulaMemoria(0));
            seq(vm, senao);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, ter->ifExpr, profundidade, offset, funcao), profundidade, offset, funcao);
            vm.rotulo.push_back(new int(0));
            int &sair_se = (*vm.rotulo[vm.rotulo.size()-1]);
            si(vm, sair_se);
            senao = vm.codigo.size();
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, ter->elsExpr, profundidade, offset, funcao), profundidade, offset, funcao);
            sair_se = vm.codigo.size();

        }
        break;
        case TipoNo::OPERACAO_UNARIA:
        {
            NOperacaoUnaria *uni = dynamic_cast<NOperacaoUnaria*>(no);
            No* r = ultimo_elemento(vm, tabela, uni->rhs, profundidade, offset, funcao);
            gerar_codigo(vm, tabela, r, profundidade, offset, funcao);

            switch(uni->op)
            {
                case Operador::NEG_OP:
                {
                    // ~eax ou ! eax
                    vm.codigo.push_back(new INaoBit(vm.eax, vm.eax));
                }
                break;
                case Operador::MIN_OP:
                {
                    // -eax
                    vm.codigo.push_back(new INeg(vm.eax, vm.eax));
                }
                break;
                case Operador::INC_POS_OP:
                {
                    //salva ebx = eax +1
                    vm.codigo.push_back(new IAdcIm(vm.ebx, vm.eax, CelulaMemoria(1)));
                    gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);
                    //mas retorna apenas eax...
                }
                break;
                case Operador::DEC_POS_OP:
                {
                    //salva ebx = eax -1
                    vm.codigo.push_back(new ISubIm(vm.ebx, vm.eax, CelulaMemoria(1)));
                    gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);
                    //mas retorna apenas eax...
                }
                break;
                case Operador::INC_PRE_OP:
                {
                    //salva ebx = eax +1
                    vm.codigo.push_back(new IAdcIm(vm.ebx, vm.eax, CelulaMemoria(1)));
                    vm.codigo.push_back(new IMove(vm.eax, vm.ebx));
                    gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);
                    // e retorna eax= ebx
                }
                break;
                case Operador::DEC_PRE_OP:
                {
                    //salva ebx = eax -1
                    vm.codigo.push_back(new ISubIm(vm.ebx, vm.eax, CelulaMemoria(1)));
                    vm.codigo.push_back(new IMove(vm.eax, vm.ebx));
                    gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);
                    // e retorna eax= ebx
                }
                break;
            }
        }
        break;
        case TipoNo::OPERACAO_BINARIA:
        {
            NOperacaoBinaria *bin = dynamic_cast<NOperacaoBinaria*>(no);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, bin->rhs, profundidade, offset, funcao), profundidade, offset, funcao);
            empilha(vm, vm.eax);
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, bin->lhs, profundidade, offset, funcao), profundidade, offset, funcao);
            desempilha(vm, vm.ebx);

            switch(bin->op)
            {
                case Operador::EQ_OP:
                {
                    vm.codigo.push_back(new ILigEq(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::OU_OP:
                {
                    // Zero = falso
                    // Diferente de Zero = verdadeiro
                    vm.codigo.push_back(new IBoolean(vm.eax));
                    vm.codigo.push_back(new IBoolean(vm.ebx));
                    vm.codigo.push_back(new IOuBit(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::E_OP:
                {
                    // Zero = falso
                    // Diferente de Zero = verdadeiro
                    vm.codigo.push_back(new IBoolean(vm.eax));
                    vm.codigo.push_back(new IBoolean(vm.ebx));
                    vm.codigo.push_back(new IEBit(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::OU_BIT_OP:
                {
                    vm.codigo.push_back(new IOuBit(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::E_BIT_OP:
                {
                    vm.codigo.push_back(new IEBit(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::XOR_BIT_OP:
                {
                    vm.codigo.push_back(new IXorBit(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::NE_OP:
                {
                    vm.codigo.push_back(new ILigNaoEq(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::BT_OP:
                {
                    vm.codigo.push_back(new ILigMaiorQ(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::LT_OP:
                {
                    vm.codigo.push_back(new ILigMenorQ(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::SOM_OP:
                {
                    vm.codigo.push_back(new IAdc(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::SUB_OP:
                {
                    vm.codigo.push_back(new ISub(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::MULT_OP:
                {
                    vm.codigo.push_back(new IMult(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::DIV_OP:
                {
                    vm.codigo.push_back(new IDiv(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::REST_OP:
                {
                    vm.codigo.push_back(new IResto(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::LE_OP:
                {
                    vm.codigo.push_back(new ILigMenorEq(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::GE_OP:
                {
                    vm.codigo.push_back(new ILigMaiorEq(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::ESQ_OP:
                {
                    vm.codigo.push_back(new IShiftEsq(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::DIR_OP:
                {
                    vm.codigo.push_back(new IShiftDir(vm.eax, vm.eax, vm.ebx));
                }
                break;
                case Operador::POT_OP:
                {
                    vm.codigo.push_back(new IPotencia(vm.eax, vm.eax, vm.ebx));
                }
                break;
            }
        }
        break;
        case TipoNo::INSTRUCAO_EXPRESSAO:
        {
            NInstrucaoExpressao *expr = dynamic_cast<NInstrucaoExpressao*>(no);
            gerar_codigo(vm, tabela, expr->expressao, profundidade, offset, funcao);
        }
        break;
        case TipoNo::ATRIBUICAO:
        {
            NAtribuicao *atr = dynamic_cast<NAtribuicao*>(no);

            // lhs = rhs
            gerar_codigo(vm, tabela, ultimo_elemento(vm,tabela, atr->rhs, profundidade, offset, funcao), profundidade, offset, funcao);

            if(atr->op!=Operador::ATRIBUICAO_OP)
                empilha(vm, vm.eax);

            No *r = ultimo_elemento(vm,tabela, atr->lhs, profundidade, offset, funcao);

            //se ele não for operacao de a=b então gera o a pq é do tipo a op= b e eu preciso do valor do a...
            if(atr->op!=Operador::ATRIBUICAO_OP)
            {
                gerar_codigo(vm, tabela, r, profundidade, offset, funcao);
            }

            if(atr->op!=Operador::ATRIBUICAO_OP)
                desempilha(vm, vm.ebx);
            else
                move(vm, vm.ebx, vm.eax);

            switch(atr->op)
            {
                case Operador::MULT_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IMult(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::DIV_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IDiv(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::MOD_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IResto(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::ADICAO_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IAdc(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::SUBTRACAO_ATRIBUICAO:
                {
                    vm.codigo.push_back(new ISub(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::ESQ_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IShiftEsq(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::DIR_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IShiftDir(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::E_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IEBit(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::XOR_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IXorBit(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::OU_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IOuBit(vm.ebx, vm.eax, vm.ebx));
                }
                break;
                case Operador::POT_ATRIBUICAO:
                {
                    vm.codigo.push_back(new IPotencia(vm.ebx, vm.eax, vm.ebx));
                }
                break;
            }

            gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);

        }
        break;
        case TipoNo::LEIA:
        {
            NLeia *leia = dynamic_cast<NLeia*>(no);

            ListaExpressao *list = dynamic_cast<NListaExpressoes*>(leia->expressao)->expressoes;

            for(int i = 0; i<list->size(); ++i)
            {
                No * r = ultimo_elemento(vm,tabela, list->at(i), profundidade, offset, funcao);

                if(CHECA_NO(r, TipoNo::CAST))
                {
                    r = ultimo_elemento(vm, tabela, dynamic_cast<NCast*>(r)->expressao, profundidade, offset, funcao);
                }

                switch(dynamic_cast<NExpressao*>(r)->tipo)
                {
                    case TipoVariavel::TIPO_CAR:
                    {
                        vm.codigo.push_back(new ILeituraCar(vm.ebx));
                    }
                    break;
                    case TipoVariavel::TIPO_INT:
                    {
                        vm.codigo.push_back(new ILeituraInt(vm.ebx));
                    }
                    break;
                    case TipoVariavel::TIPO_REAL:
                    {
                        vm.codigo.push_back(new ILeituraReal(vm.ebx));
                    }
                    break;
                }

                gerar_atribuicao(vm, tabela, r, profundidade, offset, funcao);
            }
        }
        break;
        case TipoNo::ESCREVA:
        {
            NEscreva *escreva = dynamic_cast<NEscreva*>(no);

            ListaExpressao *list = dynamic_cast<NListaExpressoes*>(escreva->expressao)->expressoes;

            for(int i = 0; i<list->size(); ++i)
            {
                No * r = ultimo_elemento(vm,tabela, list->at(i), profundidade, offset, funcao);
                gerar_codigo(vm, tabela, r, profundidade, offset, funcao);

                switch(dynamic_cast<NExpressao*>(r)->tipo)
                {
                    case TipoVariavel::TIPO_CAR:
                    {
                        vm.codigo.push_back(new IEscritaChar(vm.eax));
                    }
                    break;
                    case TipoVariavel::TIPO_INT:
                    {
                        vm.codigo.push_back(new IEscritaInt(vm.eax));
                    }
                    break;
                    case TipoVariavel::TIPO_REAL:
                    {
                        vm.codigo.push_back(new IEscritaDouble(vm.eax));
                    }
                    break;
                }
            }
        }
        break;
        case TipoNo::LISTA_EXPRESSOES:
        {
            NListaExpressoes *list = dynamic_cast<NListaExpressoes*>(no);

            for(int i = 0; i<list->expressoes->size(); ++i)
            {
                gerar_codigo(vm, tabela, list->expressoes->at(i), profundidade, offset, funcao);
            }
        }
        break;
        case TipoNo::TERMINAR:
        {
            //terminar o programa...
            vm.codigo.push_back(new ISalto((*vm.rotulo[1])));

        }
        break;
        case TipoNo::LIMPAR:
        {
            //terminar o programa...
            vm.codigo.push_back(new ISistema(Sistema::LIMPAR));

        }
        break;
        case TipoNo::INICIALIZADOR_VETOR:
        {
            NInicializadorVetor *list = dynamic_cast<NInicializadorVetor*>(no);
            gerar_inicializador(vm, tabela, list, profundidade, offset, funcao);

        }
        break;
        case TipoNo::NOVA_LINHA:
        {
            NNovaLinha *novalinha = dynamic_cast<NNovaLinha*>(no);

            // echo palavra
            vm.codigo.push_back(new ISistema(Sistema::NOVA_LINHA));
        }
        break;
        case TipoNo::CAST:
        {
            NCast *cast = dynamic_cast<NCast*>(no);
            gerar_codigo(vm, tabela, cast->expressao, profundidade, offset, funcao);
            vm.codigo.push_back(new ICast(vm.eax, cast->tipo));
        }
        break;
        case TipoNo::INTEIRO:
        {
            NInteiro *cons = dynamic_cast<NInteiro*>(no);
            // mv eax, IMM
            vm.codigo.push_back(new IMoveIm(vm.eax, cons->valor));
        }
        break;
        case TipoNo::CARACTER:
        {
            NCaracter *cons = dynamic_cast<NCaracter*>(no);
            // mv eax, IMM
            vm.codigo.push_back(new IMoveIm(vm.eax, cons->valor));
        }
        break;
        case TipoNo::REAL:
        {
            NReal *cons = dynamic_cast<NReal*>(no);
            // mv eax, IMM
            vm.codigo.push_back(new IMoveIm(vm.eax, cons->valor));
        }
        break;
        case TipoNo::PALAVRA_LITERAL:
        {
            NPalavraLiteral *cons = dynamic_cast<NPalavraLiteral*>(no);

            // echo palavra
            vm.codigo.push_back(new IEscritaPalavraIm(cons->valor));
        }
        break;
    }
}
