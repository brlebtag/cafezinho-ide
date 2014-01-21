#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include "linenumberarea.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>

class QPaintEvent;
class QWidget;



class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
    virtual ~CodeEditor() { };
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    bool line_number;
    QWidget *lineNumberArea;

};

#endif // CODEEDITOR_H
