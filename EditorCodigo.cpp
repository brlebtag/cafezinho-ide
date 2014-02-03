#include "EditorCodigo.h"

bool EditorCodigo::numeroLinha = true;

EditorCodigo::EditorCodigo(QWidget *parent) : QPlainTextEdit(parent)
{
    areaNumero = new AreaNumero(this);
    connect(areaNumero,SIGNAL(clicouAreaNumero(int)),this,SLOT(clicouAreaNumero(int)));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(atualizarLarguraAreaNumero(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(atualizarAreaNumero(QRect,int)));
    atualizarLarguraAreaNumero(0);
    breakpointImg.load(":/bolinha.png");
    breakpoints.clear();
}

int EditorCodigo::lineNumberAreaWidth()
{
    //Calcula o numero de digitos
    int digits = 1;
    //Pega a quandidade de blocos (linhas)
    int max = qMax(1, blockCount());
    //vai dividindo por 10 para contar quantos digitos tem...
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    //retorna qtd digitos + 10(espaçamento, opcional)
    int space = 10 + fontMetrics().width(QLatin1Char('9')) * digits;

    if(!EditorCodigo::numeroLinha)
        space = 0;

    return space;
}

void EditorCodigo::setLineNumber(bool checked)
{
    EditorCodigo::numeroLinha = checked;
}

void EditorCodigo::forceUpdate()
{
    atualizarLarguraAreaNumero(0);
}

void EditorCodigo::atualizarLarguraAreaNumero(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void EditorCodigo::atualizarAreaNumero(const QRect &rect, int dy)
{
    if(EditorCodigo::numeroLinha)
    {
        if (dy)
            areaNumero->scroll(0, dy);
        else
            areaNumero->update(0, rect.y(), areaNumero->width(), rect.height());

        if (rect.contains(viewport()->rect()))
            atualizarLarguraAreaNumero(0);
    }
}

void EditorCodigo::clicouAreaNumero(int line)
{
    bool contain = breakpoints.contains(line);

    if(contain)
    {
        breakpoints.remove(line);
    }
    else
    {
        breakpoints.insert(line);
    }

    contain = ! contain;

    this->areaNumero->repaint(this->areaNumero->rect());

    emit breakpoint(line,contain);
}



void EditorCodigo::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    areaNumero->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void EditorCodigo::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    if(EditorCodigo::numeroLinha)
    {
        QPainter painter(areaNumero);
        painter.fillRect(event->rect(), Qt::lightGray);


        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int) blockBoundingRect(block).height();

        while (block.isValid() && top <= event->rect().bottom())
        {
            if (block.isVisible() && bottom >= event->rect().top())
            {
                int num = (blockNumber + 1);
                if(!breakpoints.contains(num))
                {
                    QString number = QString::number(num);
                    painter.setPen(Qt::black);
                    painter.drawText(0, top, areaNumero->width(), fontMetrics().height(),
                                     Qt::AlignRight, number);
                }
                else
                {
                    int dim = qMin(areaNumero->width(),fontMetrics().height());
                    QPointF pos(this->lineNumberAreaWidth()-dim,top);
                    QImage img = breakpointImg.scaled(dim,dim);
                    painter.drawImage(pos,img);
                }
            }

            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
        }
    }
}
