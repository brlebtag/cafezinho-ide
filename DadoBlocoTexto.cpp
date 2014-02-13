#include "DadoBlocoTexto.h"

DadoBlocoTexto::DadoBlocoTexto()
{
    _informacao = new QList<Informacao>();
}

DadoBlocoTexto::~DadoBlocoTexto()
{
    delete _informacao;
}

void DadoBlocoTexto::inserir(char caracter, int posicao)
{
    Informacao info;

    info.caracter = caracter;
    info.posicao = posicao;
    _informacao->append(info);
}

const DadoBlocoTexto::Informacao &DadoBlocoTexto::em(int i) const
{
    return _informacao->at(i);
}

int DadoBlocoTexto::tamanho()
{
    return _informacao->size();
}



