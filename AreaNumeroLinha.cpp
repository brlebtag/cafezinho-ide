#include "AreaNumeroLinha.h"


AreaNumeroLinha::AreaNumeroLinha(EditorCodigo *editor) : QWidget(editor)
{
    this->editorCodigo = editor;
}

QSize AreaNumeroLinha::sizeHint() const
{
    return QSize(editorCodigo->lineNumberAreaWidth(), 0);
}

QSize AreaNumeroLinha::minimumSizeHint() const
{
    return QSize(editorCodigo->lineNumberAreaWidth(), 0);
}

void AreaNumeroLinha::paintEvent(QPaintEvent *event)
{
    editorCodigo->lineNumberAreaPaintEvent(event);
}

void AreaNumeroLinha::mousePressEvent(QMouseEvent *event)
{
    //Pega o bloco que está no editorCodigo
    QTextBlock block = editorCodigo->firstVisibleBlock();
    //pega o tamanho de cada bloco de texto
    int height = editorCodigo->blockBoundingRect(block).height();
    // pega a posicao do click divido pela altura de cada bloco texto (inteiro) + o primeiro bloco
    // visivel + 1 (por que o blockNumber começa em zero)
    int line = ((int)(event->pos().y()/height)) + block.blockNumber() + 1;
    //dispara o evento clicouAreaNumero
    emit clicouAreaNumero(line);
}
