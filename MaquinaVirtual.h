#ifndef MAQUINAVIRTUAL_H
#define MAQUINAVIRTUAL_H

#include <QObject>
#include <QString>
#include <QVector>
#include "Instrucao.h"
#include "CelulaMemoria.h"
#include "CompThread.h"
#include "CompInfo.h"
#include <QSet>

/*
 * Este enum é utilizado para fazer o controle se está executando normal
 * se está em passo por cima, passa entrando...
 */

namespace StatusExec {
    enum StatusExec {
        ENTRA, CONT, CIMA
    };
}


class MaquinaVirtual : public QObject
{
    Q_OBJECT
public:
    friend class IDebugPasso;
    explicit MaquinaVirtual(QObject *parent = 0);
    virtual ~MaquinaVirtual();
    void executar();
    void parar();
    void passo();
    void reiniciar();
    void msgErro(QString _err);
    int pc; //Contator de programa
    CelulaMemoria pp; //Ponteiro da pilha
    CelulaMemoria eax; // registrador acumulador
    CelulaMemoria ebx; // registrador de proposito geral
    CelulaMemoria ecx; // registrador de proposito geral
    CelulaMemoria edx; // registrador de proposito geral
    CelulaMemoria bp; // ponteiro base pilha (usar como fp do assembly MIPS)
    CelulaMemoria er; // endereço de retorno
    CelulaMemoria pg; // Ponteiro Global...
    bool bf; //flag maior que...
    bool sf; //flag menor que...
    bool ef; //flag igual a...
    bool erf; //Flag indicando erro ou finalizar o processo...
    bool tp; //Flag indicando que não foi erro mais sim para terminar o processo
    QVector<CelulaMemoria> memoria;
    QVector<Instrucao*> codigo;
    QVector<int*>rotulo;
    void escreveInt(int c);
    void escreveChar(char c);
    void escreveDouble(double c);
    void escrevePalavra(QString *palavra);
    int leInt();
    char leChar();
    double leDouble();
    bool execute;
    void sistema(Sistema::Comando comando);
    StatusExec::StatusExec statusExec;
    /*
     * Dentro do código quando eu entro no modo debug eu crio varios pontos de paradas que são quando se deve chamar para o usuario
     * escolher entre passa por cima, passa entrando, continuar. Mas eu posso colocar os breakpoints em qualquer linha...
     * Estes são breakpoints invalidos! Então eu faço um processo de coverter os breakpoints invalidos em válidos, ou seja breakpoints
     * que são os pontos de paradas que foram colocados no modo debug...
     */
    QSet<int> valido_break;


protected:
    void sincronizar_passo(int linha, bool breakpoint);

signals:
    void limpar_terminal();
    void mudou_instrucao(int linha);

public slots:

};

#endif // MAQUINAVIRTUAL_H
