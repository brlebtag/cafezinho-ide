#ifndef CELULAMEMORIA_H
#define CELULAMEMORIA_H

#include <QString>
#include <QtCore/qmath.h>

namespace TipoCelula
{
     enum Tipo
     {
         INT,
         CAR,
         REAL
     };
}

class CelulaMemoria
{
public:
    CelulaMemoria();
    CelulaMemoria(char value);
    CelulaMemoria(int value);
    CelulaMemoria(double value);
    CelulaMemoria &operator=(const CelulaMemoria &rhs);
    CelulaMemoria &operator=(const int &rhs);
    CelulaMemoria &operator=(const char &rhs);
    CelulaMemoria &operator=(const double &rhs);
    CelulaMemoria &operator+(const CelulaMemoria &rhs);
    CelulaMemoria &operator+(const int &rhs);
    CelulaMemoria &operator+(const char &rhs);
    CelulaMemoria &operator+(const double &rhs);
    CelulaMemoria &operator-(const CelulaMemoria &rhs);
    CelulaMemoria &operator-(const int &rhs);
    CelulaMemoria &operator-(const char &rhs);
    CelulaMemoria &operator-(const double &rhs);
    CelulaMemoria &operator*(const CelulaMemoria &rhs);
    CelulaMemoria &operator*(const int &rhs);
    CelulaMemoria &operator*(const char &rhs);
    CelulaMemoria &operator*(const double &rhs);
    CelulaMemoria &operator/(const CelulaMemoria &rhs);
    CelulaMemoria &operator/(const int &rhs);
    CelulaMemoria &operator/(const char &rhs);
    CelulaMemoria &operator/(const double &rhs);
    CelulaMemoria &pot(const CelulaMemoria &rhs); //operador potencia...
    CelulaMemoria &pot(const int &rhs);
    CelulaMemoria &pot(const char &rhs);
    CelulaMemoria &pot(const double &rhs);
    bool operator==(const CelulaMemoria &rhs);
    bool operator==(const int &rhs);
    bool operator==(const char &rhs);
    bool operator==(const double &rhs);
    bool operator>(const CelulaMemoria &rhs);
    bool operator>(const int &rhs);
    bool operator>(const char &rhs);
    bool operator>(const double &rhs);
    bool operator<(const CelulaMemoria &rhs);
    bool operator<(const int &rhs);
    bool operator<(const char &rhs);
    bool operator<(const double &rhs);

    TipoCelula::Tipo getTipo();
    QString toString();
    char toChar();
    int toInt();
    double toDouble();
    TipoCelula::Tipo tipo;
    union
    {
        int inteiro;
        double real;
        char caracter;
    }celula;
};

#endif // CELULAMEMORIA_H
