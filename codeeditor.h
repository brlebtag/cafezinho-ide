#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include "linenumberarea.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>
#include <QSet>
#include <QImage>
#include <QPointF>

class QPaintEvent;
class QWidget;



class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    friend class LineNumberArea;
    CodeEditor(QWidget *parent = 0);
    virtual ~CodeEditor() { };
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    static void setLineNumber(bool checked);
    void forceUpdate();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void lineNumberClicked(int line);

private:
    static bool line_number;
    QWidget *lineNumberArea;
    QSet<int> breakpoints;
    QImage breakImg;

signals:
    void breakpoint(int line, bool checked);

};


#endif // CODEEDITOR_H
