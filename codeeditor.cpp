#include "codeeditor.h"

bool CodeEditor::line_number = true;

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    connect(lineNumberArea,SIGNAL(lineNumberClicked(int)),this,SLOT(lineNumberClicked(int)));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    updateLineNumberAreaWidth(0);
    breakImg.load(":/bolinha.png");
    breakpoints.clear();
}

int CodeEditor::lineNumberAreaWidth()
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

    if(!CodeEditor::line_number)
        space = 0;

    return space;
}

void CodeEditor::setLineNumber(bool checked)
{
    CodeEditor::line_number = checked;
}

void CodeEditor::forceUpdate()
{
    this->lineNumberArea->hide();
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if(CodeEditor::line_number)
    {
        if (dy)
            lineNumberArea->scroll(0, dy);
        else
            lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

        if (rect.contains(viewport()->rect()))
            updateLineNumberAreaWidth(0);
    }
}

void CodeEditor::lineNumberClicked(int line)
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

    this->lineNumberArea->repaint(this->lineNumberArea->rect());

    emit breakpoint(line,contain);
}



void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    if(CodeEditor::line_number)
    {
        QPainter painter(lineNumberArea);
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
                    painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                                     Qt::AlignRight, number);
                }
                else
                {
                    int dim = qMin(lineNumberArea->width(),fontMetrics().height());
                    QPointF pos(this->lineNumberAreaWidth()-dim,top);
                    QImage img = breakImg.scaled(dim,dim);
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
