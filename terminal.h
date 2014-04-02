#ifndef TERMINAL_H
#define TERMINAL_H

#include <QPlainTextEdit>
#include <QKeyEvent>
#include <QString>
#include <QTextCursor>
#include <QDebug>

class Terminal : public QPlainTextEdit
{
    Q_OBJECT

public:
    Terminal(QWidget *parent = 0);
    void modoEntrada();
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent (QMouseEvent * e);
    virtual void mouseDoubleClickEvent (QMouseEvent * e);
private:
    int fixCursor;
    bool _modoEntrada;
    void desligarModoEntrada();
signals:
    void terminouEntradaDados(QString texto);
};

#endif // TERMINAL_H
