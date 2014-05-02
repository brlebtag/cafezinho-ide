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
    vm = new MaquinaVirtual(this);
    connect(this, SIGNAL(finished()),CompInfo::inst(),SLOT(thread_terminou()));
}

void CompThread::run()
{

    CompInfo::err().limpar();

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

    //Para Debugar a arvore (Abstract Syntatic Tree)
    /*if(!erro_compilador)
        debug_arvore(bloco, 0);*/


    if(!erro_compilador)
    {
        TabelaRef tabela;
        connect(vm, SIGNAL(limpar_terminal()), this, SLOT(limpar_tela()));

        gerar_codigo(*vm,tabela, bloco, 0, 0, 0);

        //Para Debugar o codigo gerado
        /*if(!erro_compilador)
            debug_codigo(*vm);*/

        if((*vm->rotulo[0])!=-1)
        {
            vm->executar();
        }
        else
        {
            CompInfo::err()<<"[Cafezinho] A função nulo programa() não foi definida!\n";
            vm->erf = true;
        }

        if(!vm->erf)
            appendMsg("<b>Programa terminado com sucesso!</b>");
    }

    delete bloco;

    fclose(file);
}

void CompThread::limpar_tela()
{
    emit limpar_terminal();
}

void CompThread::appendMsg(QString msg)
{
    emit mensagem(msg);
}

void CompThread::appendTexto(QString texto)
{
    emit texto_puro(texto);
}

void CompThread::modoEntrada()
{
    emit iniciarModoEntrada();
}

void CompThread::cancelarExecucao()
{
    vm->erf = true;
    vm->tp = true;
    appendMsg("<b>Programa encerrado com sucesso!</b>");
}

MaquinaVirtual* CompThread::getVM()
{
    return this->vm;
}
