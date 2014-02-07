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
    bool isRefazerDisponivel();
    bool isDesfazerDisponivel();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void atualizarLarguraAreaNumero(int newBlockCount);
    void atualizarAreaNumero(const QRect &, int);
    void clicouAreaNumero(int line);
    void textoSelecionadoHabilitado(bool yes);
    void desfazerDisp(bool b);
    void refazerDisp(bool b);

private:
    static bool numeroLinha;
    QWidget *areaNumero;
    QSet<int> breakpoints;
    QImage breakpointImg;
    bool textoSelecionado;
    bool refazerDisponivel;
    bool desfazerDisponivel;

signals:
    void breakpoint(int line, bool checked);

};


#endif // CODEEDITOR_H
