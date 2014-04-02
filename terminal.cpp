#include "terminal.h"

Terminal::Terminal(QWidget *parent) : QPlainTextEdit(parent)
{
    this->setReadOnly(true);
    _modoEntrada = false;
}

void Terminal::modoEntrada()
{
    this->setReadOnly(false);
    this->fixCursor = this->textCursor().position();
    _modoEntrada = true;
}

void Terminal::desligarModoEntrada()
{
    this->setReadOnly(true);
    _modoEntrada = false;
}

void Terminal::keyPressEvent(QKeyEvent *e)
{
    setFocusPolicy(Qt::ClickFocus);

    switch(e->key())
    {
        case Qt::Key_Up:
        {
            e->ignore();
            return;
        }
        break;
        case Qt::Key_Down:
        {
            e->ignore();
            return;
        }
        break;
        case Qt::Key_Left:
        {
            if(this->textCursor().position()<=fixCursor)
            {
                e->ignore();
                return;
            }
        }
        break;
        case Qt::Key_Backspace:
        {
            if(this->textCursor().position()<=fixCursor)
            {
                e->ignore();
                return;
            }

        }
        break;
    }

    if((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
    {
        QString texto;
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(fixCursor, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        texto = cursor.selectedText();
        desligarModoEntrada();
        emit terminouEntradaDados(texto);
    }

    QPlainTextEdit::keyPressEvent(e);
}

void Terminal::mousePressEvent(QMouseEvent *e)
{
    if(_modoEntrada)
        e->ignore();
    else
        QPlainTextEdit::mousePressEvent(e);
}

void Terminal::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(_modoEntrada)
        e->ignore();
    else
        QPlainTextEdit::mouseDoubleClickEvent(e);
}
