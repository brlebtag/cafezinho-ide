#ifndef COMPTHREAD_H
#define COMPTHREAD_H

#include <QThread>
#include "CompInfo.h"
#include "arvore_abstrata.h"
#include <cstdlib>
#include <QDebug>
#include <QPlainTextEdit>

class CompThread;

extern int yyparse(CompThread* thread, NBloco * bloco);
extern void yyrestart( FILE *file );

class CompThread : public QThread
{
    Q_OBJECT
public:
    explicit CompThread(QObject *parent = 0);
    void appendMsg(QString msg);

private:
    void run();

signals:
    emit void mensagem(QString msg);

public slots:

};

#endif // COMPTHREAD_H
