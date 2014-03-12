#ifndef MAQUINAVIRTUAL_H
#define MAQUINAVIRTUAL_H

#include <QObject>
#include <QList>
#include <QHash>
#include <Instrucao.h>
#include <CelulaMemoria.h>
#include <QString>

class MaquinaVirtual : public QObject
{
    Q_OBJECT
public:
    explicit MaquinaVirtual(QObject *parent = 0);
    virtual ~MaquinaVirtual();
    void executar();
    void parar();
    void rodar();
    void passo();
    void inserirInstrucao(Instrucao* i);
    void empilhar(CelulaMemoria m);
    void desempilhar();
    void escreva(QString texto);
    int lerInt();
    double lerReal();
    char lerCar();
    CelulaMemoria &getCelula(int offset);
    void setCelula(CelulaMemoria& registrador, int offset);
    int aloca(int quantidade);
    int pc; //Contator de programa
    int sp; //Ponteiro da pilha
    CelulaMemoria eax; // registrador acumulador
    CelulaMemoria ebx; // registrador de proposito geral
    CelulaMemoria ecx; // registrador de proposito geral
    CelulaMemoria edx; // registrador de proposito geral
    int bp; // ponteiro base pilha (usar como fp do assembly MIPS)
    int ra; // endereço de retorno
    bool bf; //flag maior que...
    bool sf; //flag menor que...
    bool ef; //flag igual a...
    bool erf; //Flag indicando erro...
private:
    bool execute;
    QList<CelulaMemoria> memoria;
    QList<Instrucao*> codigo;

signals:

public slots:

};

#endif // MAQUINAVIRTUAL_H
