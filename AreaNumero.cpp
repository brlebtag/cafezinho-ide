#include "AreaNumero.h"


AreaNumero::AreaNumero(EditorCodigo *editor) : QWidget(editor)
{
    this->editorCodigo = editor;
}

QSize AreaNumero::sizeHint() const
{
    return QSize(editorCodigo->lineNumberAreaWidth(), 0);
}

QSize AreaNumero::minimumSizeHint() const
{
    return QSize(editorCodigo->lineNumberAreaWidth(), 0);
}

void AreaNumero::paintEvent(QPaintEvent *event)
{
    editorCodigo->lineNumberAreaPaintEvent(event);
}

void AreaNumero::mousePressEvent(QMouseEvent *event)
{
    //Pega o bloco que está no editorCodigo
    QTextBlock block = editorCodigo->firstVisibleBlock();
    //pega o tamanho de cada bloco de texto
    int height = editorCodigo->blockBoundingRect(block).height();
    // pega a posicao do click divido pela altura de cada bloco texto (inteiro) + o primeiro bloco
    // visivel + 1 (por que o blockNumber começa em zero)
    int line = ((int)event->pos().y()/height) + block.blockNumber() + 1;
    //dispara o evento clicouAreaNumero
    emit clicouAreaNumero(line);
}
