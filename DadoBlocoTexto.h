#ifndef DADOBLOCOTEXTO_H
#define DADOBLOCOTEXTO_H

#include <QTextBlockUserData>
#include <QList>


class DadoBlocoTexto : public QTextBlockUserData
{
private:
    class Informacao
    {
    public:
        char caracter;
        int posicao;
    };
    QList<Informacao> * _informacao;

public:
    DadoBlocoTexto();
    virtual ~DadoBlocoTexto();
    void inserir(char caracter, int posicao);
    const Informacao &em(int i)const;
    int tamanho();
};

#endif // DADOBLOCOTEXTO_H
