#include "linenumberarea.h"


LineNumberArea::LineNumberArea(CodeEditor *editor) : QWidget(editor)
{
    this->codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}

void LineNumberArea::mousePressEvent(QMouseEvent *event)
{
    QTextBlock block = codeEditor->firstVisibleBlock();
    int height = codeEditor->blockBoundingRect(block).height();
    int line = ((int)event->pos().y()/height) + block.blockNumber() + 1;
    emit lineNumberClicked(line);
}
