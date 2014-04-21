#include "EditorCodigo.h"

bool EditorCodigo::numeroLinha = true;

const char EditorCodigo::simbolos [] = {'{', '}', '(',')', '[',']'};

const int EditorCodigo::QTD_SIMBOLOS = 6;

EditorCodigo::EditorCodigo(QWidget *parent) : QPlainTextEdit(parent)
{
    areaNumero = new AreaNumeroLinha(this);
    connect(areaNumero,SIGNAL(clicouAreaNumero(int)),this,SLOT(clicouAreaNumero(int)));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(atualizarLarguraAreaNumero(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(atualizarAreaNumero(QRect,int)));
    connect(this,SIGNAL(copyAvailable(bool)),this,SLOT(textoSelecionadoHabilitado(bool)));
    connect(this,SIGNAL(cursorPositionChanged()), this, SLOT(mudouPosicaoCursor()));
    atualizarLarguraAreaNumero(0);
    breakpointImg.load(":/bolinha.png");
    breakpoints.clear();
    textoSelecionado = false;
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

bool EditorCodigo::isTextoSelecionado()
{
    return this->textoSelecionado;
}

QSet<int> &EditorCodigo::getBreakPoints()
{
    return this->breakpoints;
}

bool EditorCodigo::ligaDeslBreakPoint(int linha)
{
    bool contem = breakpoints.contains(linha);

    if(contem)
    {
        breakpoints.remove(linha);
    }
    else
    {
        breakpoints.insert(linha);
    }

    contem = ! contem;

    this->areaNumero->repaint(this->areaNumero->rect());

    return contem;
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

void EditorCodigo::clicouAreaNumero(int linha)
{
    emit breakpoint(linha, ligaDeslBreakPoint(linha));
}

void EditorCodigo::textoSelecionadoHabilitado(bool yes)
{
    this->textoSelecionado = yes;
}
// '{', '}', '(',')', '[',']'

void EditorCodigo::mudouPosicaoCursor()
{
    DadoBlocoTexto *dado = static_cast<DadoBlocoTexto*>(textCursor().block().userData());
    QList<QTextEdit::ExtraSelection> selecoes;
    setExtraSelections(selecoes);

    int posicao = textCursor().block().position();

    for(int i=0; i<dado->tamanho(); i++)
    {
        int atualPos = textCursor().position() - textCursor().block().position();

        for(int j=0; j<EditorCodigo::QTD_SIMBOLOS; j+=2)
        {
            if(dado->em(i).caracter == simbolos[j] && dado->em(i).posicao == atualPos)
            {
                if(combinaDireita(textCursor().block(), j, i+1, 0))
                    criarMarcacao(posicao + dado->em(i).posicao);

            }
            else if(dado->em(i).caracter == simbolos[j+1] && dado->em(i).posicao == atualPos)
            {
                if(combinaEsquerda(textCursor().block(), j+1, i-1, 0))
                    criarMarcacao(posicao + dado->em(i).posicao);

            }
        }
    }
}

bool EditorCodigo::combinaEsquerda(QTextBlock bloco, int simbolo, int i, int numSimbolos)
{
    DadoBlocoTexto *dado = static_cast<DadoBlocoTexto*>(bloco.userData());

    int docPos = bloco.position();

    for(; i>=0&& dado->tamanho() > 0; --i)
    {
        if(dado->em(i).caracter == simbolos[simbolo])
        {
            ++numSimbolos;
            continue;
        }

        if(dado->em(i).caracter == simbolos[simbolo-1] && numSimbolos == 0)
        {
            criarMarcacao(docPos + dado->em(i).posicao);
            return true;
        }
        else if(dado->em(i).caracter == simbolos[simbolo-1])
        {
                --numSimbolos;
        }
    }

    bloco = bloco.previous();

    if(bloco.isValid())
        return combinaEsquerda(bloco, simbolo, static_cast<DadoBlocoTexto*>(bloco.userData())->tamanho()-1, numSimbolos);

    return false;
}

bool EditorCodigo::combinaDireita(QTextBlock bloco, int simbolo, int i, int numSimbolos)
{

    DadoBlocoTexto *dado = static_cast<DadoBlocoTexto*>(bloco.userData());

    int docPos = bloco.position();

    for(; i < dado->tamanho(); ++i)
    {
        if(dado->em(i).caracter == simbolos[simbolo])
        {
            ++numSimbolos;
            continue;
        }

        if(dado->em(i).caracter == simbolos[simbolo+1] && numSimbolos == 0)
        {
            criarMarcacao(docPos + dado->em(i).posicao);
            return true;
        }
        else if(dado->em(i).caracter == simbolos[simbolo+1])
        {
                --numSimbolos;
        }
    }
    bloco = bloco.next();

    if(bloco.isValid())
        return combinaDireita(bloco, simbolo, 0, numSimbolos);

    return false;
}

void EditorCodigo::criarMarcacao(int posicao)
{
    QList<QTextEdit::ExtraSelection> selecoes = extraSelections();
    QTextEdit::ExtraSelection selecao;
    QTextCharFormat formato = selecao.format;
    formato.setBackground(Qt::green);
    selecao.format = formato;

    QTextCursor cursor = textCursor();
    cursor.setPosition(posicao);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    selecao.cursor = cursor;
    selecoes.append(selecao);
    setExtraSelections(selecoes);
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
                    QPointF pos(this->lineNumberAreaWidth()-fontMetrics().height(),top);
                    QImage img = breakpointImg.scaled(fontMetrics().height(), fontMetrics().height());
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
