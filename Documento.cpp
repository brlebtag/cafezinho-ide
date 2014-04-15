#include "Documento.h"

const int Documento::TAB_SPACE = 4;

Documento::Documento(QWidget *widget, EditorCodigo *edit, QObject *botao, bool sujo) :
    QObject(widget), widget(widget), edit(edit), botao(botao), sujo(sujo)
{
    aberto = false;
    edit->setWordWrapMode(QTextOption::NoWrap);
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    Realcador *realcador = new Realcador(edit->document());
    //O Realcador dispara textChanged() na primeira chamada...
    //assim o editor vai adicionar * pensando que mudou alguma coisa
    //Para corrigir isso eu adicionei essa flag primeiraChamada ela é de controle intero
    //IDE não vê isso ...
    primeiraChamada = true;
    QFontMetrics metrics(edit->font());
    edit->setTabStopWidth(4*metrics.width(' '));
    connect(edit,SIGNAL(cursorPositionChanged()),this,SLOT(texto_mudou()));
}

Documento::Documento(QWidget *widget, EditorCodigo *edit, bool sujo) :
    QObject(widget), widget(widget), edit(edit), sujo(sujo)
{
    aberto = false;
    edit->setWordWrapMode(QTextOption::NoWrap);
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    Realcador *realcador = new Realcador(edit->document());
    //O Realcador dispara textChanged() na primeira chamada...
    //assim o editor vai adicionar * pensando que mudou alguma coisa
    //Para corrigir isso eu adicionei essa flag primeiraChamada ela é de controle intero
    //IDE não vê isso ...
    primeiraChamada = true;
    QFontMetrics metrics(edit->font());
    edit->setTabStopWidth(4*metrics.width(' '));
    connect(edit,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
}

bool Documento::isVazio()
{
    return this->edit->toPlainText().isEmpty();
}

bool Documento::isSujo()
{
    if(primeiraChamada)
    {
        primeiraChamada = false;
        return true;
    }
    return this->sujo;
}

bool Documento::isAberto()
{
    return this->aberto;
}

void Documento::sujou()
{
    this->sujo = true;
}

void Documento::limpou()
{
    this->sujo = false;
}

void Documento::abriu()
{
    this->aberto = true;
}

void Documento::fechou()
{
    this->aberto = false;
}

QString Documento::getTextoDocumento()
{
    return this->edit->toPlainText();
}

void Documento::setNomeDocumento(QString fileName)
{
    this->caminhoCompleto = fileName;
    this->documentoId =  QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

void Documento::setTextoDocumento(QString &text)
{
    this->edit->setPlainText(text);
}

void Documento::setTextoDocumento(QByteArray text)
{
    this->edit->setPlainText(text);
}

void Documento::anexarTextoDocumento(QString &text)
{
    this->edit->appendPlainText(text);
}

QWidget *Documento::getWidget()
{
    return widget;
}

QString Documento::getDocumentoId()
{
    return this->documentoId;
}

QString Documento::getCaminhoCompleto()
{
    return this->caminhoCompleto;
}

void Documento::setFocus()
{
    this->edit->setFocus();
}

void Documento::repintarEditor()
{
    this->edit->forceUpdate();
}

void Documento::copiar()
{
    this->edit->copy();
}

void Documento::colar()
{
    this->edit->paste();
}

void Documento::recortar()
{
    this->edit->cut();
}

void Documento::desfazer()
{
    this->edit->undo();
}

void Documento::refazer()
{
    this->edit->redo();
}

bool Documento::isTextoSelecionado()
{
    return this->edit->isTextoSelecionado();
}

bool Documento::isColarDisponivel()
{
    return this->edit->canPaste(); //temporariamente...
}

bool Documento::isDesfazerDisponivel()
{
    return this->edit->document()->isUndoAvailable();
}

bool Documento::isRefazerDisponivel()
{
    return this->edit->document()->isRedoAvailable();
}

void Documento::setFonte(QString familia, int tamanho)
{
    QFont fonte;
    fonte.setFamily(familia);
    fonte.setStyleHint(QFont::Monospace);
    fonte.setFixedPitch(true);
    fonte.setPointSize(tamanho);
    QFontMetrics metrics(fonte);
    edit->setTabStopWidth(Documento::TAB_SPACE*metrics.width(' '));
    this->edit->setFont(fonte);
}

int Documento::getQuantidadeLinhas()
{
    return this->edit->document()->blockCount();
}

void Documento::setPosicaoCursor(int posicao)
{
    QTextCursor cursor(this->edit->textCursor());

    int posCursorAtual = getPosicaoCursor();

    //Marca como uma unica operação...
    cursor.beginEditBlock();

    //Movimenta o cursor para o inicio da linha
    cursor.movePosition(QTextCursor::StartOfLine);

    if(posicao > posCursorAtual)
    {
        //mover para baixo
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, posicao - posCursorAtual);
    }
    else
    {
        //mover para cima
        cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, posCursorAtual - posicao);
    }

    //Termina a marcação como unica operação
    cursor.endEditBlock();

    //Seta a posicao do novo Cursor
    this->edit->setTextCursor(cursor);
}

int Documento::getPosicaoCursor()
{
    return (edit->textCursor().block().blockNumber() + 1);
}

void Documento::duplicarLinha()
{
    QTextCursor cursor(this->edit->textCursor());

    //Marca como uma unica operação...
    cursor.beginEditBlock();

    //Pega o texto daquele bloco que o cursor está
    QString textoDup = cursor.block().text();

    //Movimenta o cursor para o fim da linha
    cursor.movePosition(QTextCursor::EndOfLine);

    //Inseri o
    cursor.insertText("\n"+textoDup);

    //Termina a marcação como unica operação
    cursor.endEditBlock();
}

QPlainTextEdit *Documento::getEditor()
{
    return this->edit;
}

QObject *Documento::getBotao()
{
    return botao;
}

void Documento::setBotao(QObject *botao)
{
    this->botao = botao;
}

void Documento::setSelecoes(QList<QTextEdit::ExtraSelection> selecoes)
{
    this->edit->setExtraSelections(selecoes);
}

void Documento::limparSelecoes()
{
    QList<QTextEdit::ExtraSelection> selecoes;
    this->edit->setExtraSelections(selecoes);
}

void Documento::texto_mudou()
{
    emit textoMudou(edit->document());
}
