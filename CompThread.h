#ifndef COMPTHREAD_H
#define COMPTHREAD_H

#include <QThread>
#include "CompInfo.h"
#include <cstdlib>
#include <QDebug>
#include <QPlainTextEdit>
#include "semantico.h"

class CompThread;

class CompThread : public QThread
{
    Q_OBJECT
public:
    explicit CompThread(QObject *parent = 0);
    void appendMsg(QString msg);
    friend CompThread &operator<<(CompThread& out, const QString text);
    friend CompThread &operator<<(CompThread& out, const QString* text);
    friend CompThread &operator<<(CompThread& out, const int text);
    friend CompThread &operator<<(CompThread& out, const char* text);
private:
    void run();
    QString texto;

signals:
    emit void mensagem(QString msg);

public slots:

};

#endif // COMPTHREAD_H
