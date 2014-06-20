#include "semantico.h"

extern int erro_compilador;

bool checar_chamada(TabelaSimbolo &tabela, No* parametro, No* argumento)
{
   No* no = ultimo_parametro(tabela, argumento);

   if(CHECA_NO(parametro, DECLARACAO_VARIAVEL_ESCALAR))
   {
       NDeclVarEscalar *var = dynamic_cast<NDeclVarEscalar*>(parametro);

       return var->tipo == checar_tipo(tabela, no);
   }
   else
   {
       NDeclVarVetorial *param = dynamic_cast<NDeclVarVetorial*>(parametro);

       if(NCHECA_NO(no, IDENTIFICADOR_ESCALAR))
       {
           CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado "<<tipo_no(no)<<" próximo a "<<argumento->linha<<"\n";
           erro_compilador = true;
           return false;
       }
       else
       {
           NIdentificadorEscalar *ident = dynamic_cast<NIdentificadorEscalar*>(no);

           IteradorTabelaSimbolo itSim = tabela.find(*ident->nome);

           if(itSim==tabela.end())
           {
               CompInfo::err()<<"[ERRO SEMANTICO] Variavel "<<ident->nome<<" não foi previamente declarado próximo a "<<ident->linha<<"\n";
               erro_compilador = true;
               return false;
           }
           else
           {
               if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_FUNCAO))
               {
                   CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado função próximo a "<<ident->linha<<"\n";
                   erro_compilador = true;
                   return false;
               }
               else if(CHECA_NO(itSim.value()->top()->no, DECLARACAO_VARIAVEL_ESCALAR))
               {
                   CompInfo::err()<<"[ERRO SEMANTICO] Esperado variavel vetorial encontrado variavel escalar próximo a "<<ident->linha<<"\n";
                   erro_compilador = true;
                   return false;
               }
               else
               {
                   NDeclVarVetorial *arg = dynamic_cast<NDeclVarVetorial*>(itSim.value()->top()->no);


                   if(param->dimensoes->size()!=arg->dimensoes->size())
                   {
                       CompInfo::err()<<"[ERRO SEMANTICO] Parametro possui "<<param->dimensoes->size()<<" dimensões enquanto que argumento possui "<<arg->dimensoes->size()<<" próximo a "<<ident->linha<<"\n";
                       erro_compilador = true;
                       return false;
                   }


                   bool resultado = true;
                   QString dimArg, dimParam;

                   /* O primeiro parametro não é obrigatório a declaração */
                   if(param->dimensoes->at(0)->tipoNo() == TipoNo::INTEIRO&&arg->dimensoes->at(0)->tipoNo() == TipoNo::INTEIRO)
                   {
                       if(dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor != dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor)
                       {
                           resultado = false;
                           dimArg = QString::number(dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor);
                           dimParam = QString::number(dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor);
                       }
                       else
                       {
                           dimArg = QString::number(dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor);
                           dimParam = QString::number(dynamic_cast<NInteiro*>(param->dimensoes->at(0))->valor);
                       }
                   }
                   else if(arg->dimensoes->at(0)->tipoNo() == TipoNo::INTEIRO)
                   {
                       dimArg = QString::number(dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor);
                       dimParam = QString::number(dynamic_cast<NInteiro*>(arg->dimensoes->at(0))->valor);
                   }

                   /* Porém os outros são obrigátorio*/
                   for(int i=1; i<param->dimensoes->size(); ++i)
                   {
                       try {
                            resultado &= dynamic_cast<NInteiro*>(param->dimensoes->at(i))->valor == dynamic_cast<NInteiro*>(arg->dimensoes->at(i))->valor;
                       }catch(...)
                       {
                       }
                       dimArg +="][";
                       try {
                            dimArg += QString::number(dynamic_cast<NInteiro*>(arg->dimensoes->at(i))->valor);
                       }
                       catch(...)
                       {
                         dimArg+="";
                       }
                       dimParam +="][";
                       try{
                            dimParam += QString::number(dynamic_cast<NInteiro*>(param->dimensoes->at(i))->valor);
                       }
                       catch(...)
                       {
                         dimParam+="";
                       }
                   }

                   if(!resultado)
                   {
                       CompInfo::err()<<"[ERRO SEMANTICO] Argumento possui "<<arg->nome<<"["<<dimArg<<"] dimensões enquanto que o parametros possui "<<param->nome<<"["<<dimParam<<"] dimensões próximo a "<<ident->linha<<"\n";
                       erro_compilador = true;
                       return false;
                   }

                   if(param->tipo!=arg->tipo)
                   {
                       CompInfo::err()<<"[ERRO SEMANTICO] Parametro é do tipo "<<param->tipo<<"* enquanto que argumento é do tipo "<<arg->tipo<<"* próximo a "<<ident->linha<<"\n";
                       erro_compilador = true;
                       return false;
                   }

                   //salva para qual vetor este identificador aponta!!!
                   ident->ponteiro = arg;

                   return true;
               }
           }
       }
   }
}

No* ultimo_parametro(TabelaSimbolo &tabela, No * no)
{
   if(CHECA_NO(no, LISTA_EXPRESSOES))
   {
       NListaExpressoes *list  = dynamic_cast<NListaExpressoes*>(no);

       for(int i=0; i<(list->expressoes->size()-1); ++i)
       {
           checar_tipo(tabela, (No*) list->expressoes->at(i));
       }

       return ultimo_parametro(tabela, list->expressoes->at(list->expressoes->size()-1));
   }
   else
       return no;
}
