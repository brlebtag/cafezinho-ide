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
#include <QTextEdit>
#include "GerarCodigo.h"
#include "MaquinaVirtual.h"

class CompThread;

class CompThread : public QThread
{
    Q_OBJECT
public:
    explicit CompThread(QObject *parent = 0);
    void appendMsg(QString msg);
    void appendTexto(QString texto);

private:
    void run();
    QList<QTextEdit::ExtraSelection> selecoes;

signals:
    emit void mensagem(QString msg);
    emit void texto_puro(QString texto);

public slots:

};

#endif // COMPTHREAD_H
