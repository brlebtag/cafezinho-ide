#include "GerarCodigo.h"

void gerar_inicializador(MaquinaVirtual &vm, TabelaRef &tabela, NInicializadorVetor *list, int profundidade, int offset, No* funcao)
{
    QQueue<NListaInicializador*> inicializador;
    IteradorTabelaRef itIdent = tabela.find(*list->nome);
    Referencia ref = itIdent.value().top();

    for(int i=0; i<list->init->size(); ++i)
    {
        inicializador.enqueue((NListaInicializador*)list->init->at(i));
    }

    int indice = 0;

    while(!inicializador.isEmpty())
    {
        NListaInicializador *init = inicializador.dequeue();

        for(int i=0; i<init->expressoes->size(); ++i)
        {
            if(CHECA_NO(init->expressoes->at(i), TipoNo::LISTA_INICIALIZADOR))
                inicializador.enqueue((NListaInicializador*)init->expressoes->at(i));
            else
            {
                //gera o código...
                gerar_codigo(vm, tabela, init->expressoes->at(i), profundidade, offset, funcao);

                if(ref.profundidade == 0)
                {
                    // ebx = pg + offset(inicial) + i
                    vm.codigo.push_back(new ISalva(vm.eax, vm.pg, indice+ref.offset));
                }
                else
                {
                    vm.codigo.push_back(new ISalva(vm.eax, vm.bp, indice+ref.offset));
                }

                ++indice;
            }
        }
    }
}
