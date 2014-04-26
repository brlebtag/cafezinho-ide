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
#include "arvore_abstrata.h"

/*
 * Este enum é utilizado para fazer o controle se está executando normal
 * se está em passo por cima, passa entrando...
 */

namespace StatusExec {
    enum StatusExec {
        ENTRAR, CONTINUAR, PROXIMA
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
    void empilha_chamada();
    void desempilha_chamada();
    StatusExec::StatusExec statusExec;
    void proximo();
    void entrar();
    void continuar();
    void empilha_variavel(No *no, int offset, bool vetor);
    void desempilha_variavel(No *no);

    /*
     * Com essa variavel eu guardarei as informação da pilha de execução, partir do momento que for acionado passar por cima
     * eu vou adicionar/remover da pilha todas as chamadas de funções. Quando a pilha ficar vazia entao sinc_passo = true
     */
private:
    int qtdChamadasFuncao;
    bool sinc_passo;


protected:
    void sincronizar_passo(int linha);

signals:
    void limpar_terminal();
    void mudou_instrucao(int linha);
    void comecar_execucao();
    void terminou_execucao(bool sucesso);
    void desabilitar_botoes_debug();
    void empilha_variavel_debug(No *no, int offset, bool vetor);
    void desempilha_variavel_debug(No *no);

public slots:

};

#endif // MAQUINAVIRTUAL_H
