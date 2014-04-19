#ifndef COMPTHREAD_H
#define COMPTHREAD_H

#include <QThread>
#include "CompInfo.h"
#include <cstdlib>
#include <QDebug>
#include <QPlainTextEdit>
#include "semantico.h"
#include <QObject>
#include <QList>
#include "GerarCodigo.h"
#include "MaquinaVirtual.h"
#include <QMutex>
#include "debugar_geracao.h"

class CompThread;

class CompThread : public QThread
{
    Q_OBJECT
public:
    explicit CompThread(QObject *parent = 0);
    void appendMsg(QString msg);
    void appendTexto(QString texto);
    void modoEntrada();
    void cancelarExecucao();
    MaquinaVirtual* getVM();
    void setVM(MaquinaVirtual *vm);

private:
    void run();
    MaquinaVirtual *vm;

signals:
    emit void mensagem(QString msg);
    emit void texto_puro(QString texto);
    emit void iniciarModoEntrada();
    emit void limpar_terminal();

public slots:
    void limpar_tela();

};

#endif // COMPTHREAD_H
