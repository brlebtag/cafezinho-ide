#include "AreaNumero.h"


AreaNumero::AreaNumero(EditorCodigo *editor) : QWidget(editor)
{
    this->codeEditor = editor;
}

QSize AreaNumero::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

QSize AreaNumero::minimumSizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void AreaNumero::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}

void AreaNumero::mousePressEvent(QMouseEvent *event)
{
    QTextBlock block = codeEditor->firstVisibleBlock();
    int height = codeEditor->blockBoundingRect(block).height();
    int line = ((int)event->pos().y()/height) + block.blockNumber() + 1;
    emit clicouAreaNumero(line);
}
