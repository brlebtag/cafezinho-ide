#ifndef COMPINFO_H
#define COMPINFO_H

#include <QObject>
#include <QPlainTextEdit>
#include <QWaitCondition>
#include <QMutex>
#include "validarbreakpoint.h"
#include <QSet>

class CompThread;
class MaquinaVirtual;

class Output
{
public:
    Output();
    void setTexto(QString texto);
    friend Output &operator<<(Output& out, const QString text);
    friend Output &operator<<(Output& out, const QString* text);
    friend Output &operator<<(Output& out, int text);
    friend Output &operator<<(Output& out, double text);
    friend Output &operator<<(Output& out, char text);
};

class Error
{
public:
    Error();
    void appendTexto(QString texto);
    void appendTexto(const char* texto);
    QString &getTexto();
    bool isFimLinha();
    void limpar();
    void descarga(QString &texto);
    friend Error &operator<<(Error& err, const QString text);
    friend Error &operator<<(Error& err, const QString* text);
    friend Error &operator<<(Error& err, const int text);
    friend Error &operator<<(Error& err, const char* text);
private:
    QString texto;

};

class CompInfo : public QObject
{
    Q_OBJECT
public:
    friend class Output;
    friend class Error;
    static CompInfo* inst();
    static MaquinaVirtual* getVM();
    static void setVM(MaquinaVirtual* vm);
    QString arquivo;
    static Output &out();
    static Error &err();
    static void setThread(CompThread *thread);
    static CompThread *getThread();
    static void modoEntrada();
    static void appendTexto(QString texto);
    static void thread_terminou();
    QMutex mutexIO;//EntradaSaidaMutex
    QString entrada;
    QWaitCondition waitIO;
    QMutex mutexSincPasso;
    QWaitCondition waitSincPasso;
    static void pararExecucao();
    static bool isDebug();
    static void setDebug(bool debug);
    static void inserirParada(int linha);
    static bool isBreakPoint(int linha);
    static void validarBreakPoint(QSet<int> &breakpoint);
    bool debug;
private:
    explicit CompInfo(QObject *parent = 0);
    ~CompInfo();
    static CompInfo* cmpInfo;
    Error *_err;
    Output *_out;
    CompThread * thread;
    ValidarBreakPoint validar;
    MaquinaVirtual *vm;


public slots:
};

#endif // COMPINFO_H
