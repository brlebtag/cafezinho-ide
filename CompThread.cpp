#include "CompThread.h"

extern bool erro_compilador;

CompThread::CompThread(QObject *parent) :
    QThread(parent)
{
}

void CompThread::run()
{
    CompInfo *cmpInfo = CompInfo::inst();

    FILE *file = fopen(CompInfo::inst()->arquivo.toLocal8Bit().constData(), "r");

    if (!file)
    {
        emit mensagem(tr("[CAFEZINHO] Não foi possivel abrir o arquivo!\n"));
        return;
    }

    yyrestart(file);

    NBloco *bloco;
    do
    {
        bloco = new NBloco(0);
        yyparse(this, bloco);
    } while (!feof(file));

    if(!erro_compilador)
        emit mensagem(tr("[CAFEZINHO] Compilado com sucesso!\n"));

    delete bloco;

    fclose(file);
}

void CompThread::appendMsg(QString msg)
{
    emit mensagem(msg);
}
