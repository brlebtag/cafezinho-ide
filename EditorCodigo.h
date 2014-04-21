#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include "AreaNumeroLinha.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>
#include <QSet>
#include <QImage>
#include <QPointF>
#include <QTextDocument>
#include "DadoBlocoTexto.h"

class QPaintEvent;
class QWidget;


class AreaNumeroLinha;

class EditorCodigo : public QPlainTextEdit
{
    Q_OBJECT

public:
    friend class AreaNumeroLinha;
    EditorCodigo(QWidget *parent = 0);
    virtual ~EditorCodigo() { };
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    static void setLineNumber(bool checked);
    void forceUpdate();
    bool isTextoSelecionado();
    QSet<int>& getBreakPoints();
    bool ligaDeslBreakPoint(int linha);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void atualizarLarguraAreaNumero(int newBlockCount);
    void atualizarAreaNumero(const QRect &, int);
    void clicouAreaNumero(int linha);
    void textoSelecionadoHabilitado(bool yes);
    void mudouPosicaoCursor();


private:
    static bool numeroLinha;
    QWidget *areaNumero;
    QSet<int> breakpoints;
    QImage breakpointImg;
    bool textoSelecionado;

    const static char simbolos [];
    const static int QTD_SIMBOLOS;

    bool combinaEsquerda(QTextBlock bloco, int simbolo, int i, int numSimbolos);
    bool combinaDireita(QTextBlock bloco, int simbolo, int i, int numSimbolos);
    void criarMarcacao(int posicao);

signals:
    void breakpoint(int line, bool checked);

};


#endif // CODEEDITOR_H
