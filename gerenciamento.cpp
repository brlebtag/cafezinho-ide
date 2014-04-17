#include "GerarCodigo.h"

No* ultimo_elemento(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No *funcao)
{
    if(CHECA_NO(no, TipoNo::LISTA_EXPRESSOES))
    {
        NListaExpressoes *list = dynamic_cast<NListaExpressoes*>(no);

        for(int i = 0; i<(list->expressoes->size()-1); ++i)
        {
            No * r = ultimo_elemento(vm, tabela, list->expressoes->at(i), profundidade, offset, funcao);
            gerar_codigo(vm, tabela, r, profundidade, offset, funcao);
        }
        return  list->expressoes->at(list->expressoes->size()-1);
    }
    else
        return no;
}

void gerar_indice(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao)
{

    NIdentificadorVetorial* ident = dynamic_cast<NIdentificadorVetorial*>(no);

    IteradorTabelaRef it = tabela.find(*ident->nome);

    Referencia ref = it.value().top();

    NDeclVarVetorial *var = dynamic_cast<NDeclVarVetorial*>(ref.origem);

    int dimensao = 1;

    gerar_codigo(vm, tabela, ultimo_elemento(vm, tabela, ident->indice->at(ident->indice->size()-1), profundidade, offset, funcao) , profundidade, offset, funcao);

    int j = var->dimensoes->size() -1;

    //Se for diferente de 1 dimensão. obs j = dimensao -1 logo tem q ser j>0 e n j>1
    if(var->dimensoes->size()>1)
        vm.codigo.push_back(new IMove(vm.ebx, vm.eax));

    for(int i = ident->indice->size()-2; i>=0; --i, --j)
    {
        dimensao *= dynamic_cast<NInteiro*>(var->dimensoes->at(j))->valor;
        gerar_codigo(vm, tabela, ultimo_elemento(vm, tabela, ident->indice->at(i), profundidade, offset, funcao) , profundidade, offset, funcao);
        vm.codigo.push_back(new IMultIm(vm.eax, vm.eax, CelulaMemoria(dimensao)));
        vm.codigo.push_back(new IAdc(vm.ebx, vm.eax, vm.ebx));
    }
    //Se for diferente de 1 dimensão. obs j = dimensao -1 logo tem q ser j>0 e n j>1
    if(var->dimensoes->size()>1)
        vm.codigo.push_back(new IMove(vm.eax, vm.ebx));
}

void gerar_atribuicao(MaquinaVirtual &vm, TabelaRef &tabela, No *no, int profundidade, int offset, No* funcao)
{
    NIdentificador *lhs = dynamic_cast<NIdentificador*>(no);
    IteradorTabelaRef itIdent = tabela.find(*lhs->nome);
    Referencia ref = itIdent.value().top();

    if(CHECA_NO(no, TipoNo::IDENTIFICADOR_ESCALAR))
    {

        if(ref.profundidade == 0)
        {
            vm.codigo.push_back(new ISalva(vm.ebx, vm.pg, ref.offset));
        }
        else
        {
            if(ref.parametro)
            {
                vm.codigo.push_back(new ISalva(vm.ebx, vm.bp, -ref.offset));
            }
            else
            {
                vm.codigo.push_back(new ISalva(vm.ebx, vm.bp, ref.offset));
            }
        }
    }
    else
    {
        NIdentificadorVetorial* ident = dynamic_cast<NIdentificadorVetorial*>(lhs);

        empilha(vm, vm.ebx);

        gerar_indice(vm, tabela, lhs, profundidade, offset, funcao);

        if(ref.profundidade == 0)
        {
            // ecx = pg + offset(do vetor alocado)
            vm.codigo.push_back(new IAdcIm(vm.ecx, vm.pg, ref.offset));
            // eax = ecx + vm.eax(eax contém o deslocamento dentro do vetor)
            vm.codigo.push_back(new IAdc(vm.eax, vm.ecx, vm.eax));
        }
        else
        {
            if(ref.parametro)
            {
                // ecx = bp - ref.offset( - ref.offset é o lucar onde aquele parametro está com relacao a bp)
                vm.codigo.push_back(new ISubIm(vm.ecx, vm.bp, ref.offset));
                //carrega o valor que está em [ecx] que é o endereco do vetor pq é um ponteiro para o vetor...
                vm.codigo.push_back(new ICarrega(vm.ecx, vm.ecx));
                // apartir de encerreco soma o deslocamento dentro do vetor...
                vm.codigo.push_back(new IAdc(vm.eax, vm.ecx, vm.eax));
            }
            else
            {
                // ecx = bp + offset(do vetor alocado)
                vm.codigo.push_back(new IAdcIm(vm.ecx, vm.bp, ref.offset));
                // eax = ecx + vm.eax(eax contém o deslocamento dentro do vetor)
                vm.codigo.push_back(new IAdc(vm.eax, vm.ecx, vm.eax));
            }
        }

        desempilha(vm, vm.ebx);

        // vm.memoria[vm.eax] = vm.ebx
        vm.codigo.push_back(new ISalva(vm.ebx, vm.eax));
    }
}

void inserir_debug_instrucao(MaquinaVirtual &vm, No* n)
{
    vm.codigo.push_back(new IDebugPasso(n->linha, false));
}
