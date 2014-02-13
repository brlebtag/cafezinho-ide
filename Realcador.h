#ifndef REALCADOR_H
#define REALCADOR_H

#include <QSyntaxHighlighter>
#include <QString>
#include <QTextDocument>
#include <QDebug>
#include <QRegExp>
#include <QTextCharFormat>
#include <QList>
#include <QStringList>
#include "DadoBlocoTexto.h"

class Realcador : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Realcador(QTextDocument *documento);
protected:
    void highlightBlock(const QString &text);
private:

    struct RegrasRealce
    {
        QRegExp padrao;
        QTextCharFormat formato;
    };
    const static int QTD_SIMBOLOS;
    const static char simbolos [];

    QList<RegrasRealce> regrasRealce;
    QRegExp comecoComentario;
    QRegExp terminoComentario;
    QTextCharFormat formatoComentario;
    QTextCharFormat formatoFuncao;
    QTextCharFormat formatoPalavrasChaves;
    QTextCharFormat formatoCaracterLiteral;
    QTextCharFormat formatoPalavraLiteral;

};

#endif // REALCADOR_H
