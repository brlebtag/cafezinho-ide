#ifndef VALIDARBREAKPOINT_H
#define VALIDARBREAKPOINT_H
#include <QList>
#include <QtAlgorithms>
#include <QMap>
#include <QSet>

/*
 * Dentro do código quando eu entro no modo debug eu crio varios pontos de paradas que são quando se deve chamar para o usuario
 * escolher entre proximo, entrar, continuar. Mas eu posso colocar os breakpoints em qualquer linha porem estes são breakpoints
 * invalidos! Então eu faço um processo de converter os breakpoints invalidos em válidos, ou seja breakpoints
 * que são também pontos de paradas que foram colocados no modo debug...
 */

class ValidarBreakPoint
{
public:
    ValidarBreakPoint();
    void inserirParada(int linha);
    bool isBreakPoint(int linha);
    void validarBreakPoints(QSet<int> &breakpoints);
private:
    QMap<int, bool> breakpoints;
    void reiniciar_breakpoints();
};

#endif // VALIDARBREAKPOINT_H
