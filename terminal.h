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
private:
    int fixCursor;
    void desligarModoEntrada();
signals:
    void terminouEntradaDados(QString texto);
};

#endif // TERMINAL_H
