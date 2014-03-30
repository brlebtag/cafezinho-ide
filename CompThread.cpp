#include "CompThread.h"
#include "arvore_abstrata.h"

extern int yyparse(NBloco * bloco);
extern void yyrestart( FILE *file );
extern bool erro_compilador;
extern bool erro_lexico;
extern int yylineno;

CompThread::CompThread(QObject *parent) :
    QThread(parent)
{
}

void CompThread::run()
{

    FILE *file = fopen(CompInfo::inst()->arquivo.toLocal8Bit().constData(), "r");

    if (!file)
    {
        emit mensagem(tr("[CAFEZINHO] Não foi possivel abrir o arquivo!\n"));
        return;
    }

    yyrestart(file);

    yylineno = 1;
    erro_compilador = 0;
    erro_lexico = 0;

    CompInfo::setOut(this);

    NBloco *bloco;
    do
    {
        bloco = new NBloco(0);
        yyparse(bloco);
    } while (!feof(file));

    if(!erro_compilador)
    {
        TabelaSimbolo tabela;
        analise_semantica(tabela, bloco, 0, 0);
    }

    if(!erro_compilador)
    {
        TabelaRef tabela;
        MaquinaVirtual vm;

        gerar_codigo(vm,tabela, bloco, 0, 0, 0);

        if((*vm.rotulo[0])!=-1)
        {
            vm.executar();
        }
        else
            CompInfo::err()<<"[Cafezinho] A função nulo programa() não foi definida!";
    }

    delete bloco;

    fclose(file);
}

void CompThread::appendMsg(QString msg)
{
    emit mensagem(msg);
}

void CompThread::appendTexto(QString texto)
{
    emit texto_puro(texto);
}
