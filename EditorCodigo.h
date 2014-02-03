#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include "AreaNumero.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>
#include <QSet>
#include <QImage>
#include <QPointF>

class QPaintEvent;
class QWidget;



class AreaNumero;

class EditorCodigo : public QPlainTextEdit
{
    Q_OBJECT

public:
    friend class AreaNumero;
    EditorCodigo(QWidget *parent = 0);
    virtual ~EditorCodigo() { };
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    static void setLineNumber(bool checked);
    void forceUpdate();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void atualizarLarguraAreaNumero(int newBlockCount);
    void atualizarAreaNumero(const QRect &, int);
    void clicouAreaNumero(int line);

private:
    static bool numeroLinha;
    QWidget *areaNumero;
    QSet<int> breakpoints;
    QImage breakpointImg;

signals:
    void breakpoint(int line, bool checked);

};


#endif // CODEEDITOR_H
