#ifndef CELULAMEMORIA_H
#define CELULAMEMORIA_H

#include <QtCore/qmath.h>
#include "QString"

using namespace std;

class CelulaMemoria
{
public:
    CelulaMemoria();
    CelulaMemoria(const CelulaMemoria &rhs);
    CelulaMemoria(const int value);
    CelulaMemoria(const double value);
    CelulaMemoria(const char value);
    CelulaMemoria operator=(const CelulaMemoria &rhs);
    CelulaMemoria operator=(const int &rhs);
    CelulaMemoria operator=(const double &rhs);
    CelulaMemoria operator=(const char &rhs);
    CelulaMemoria operator+(const CelulaMemoria &rhs);
    CelulaMemoria operator+(const int &rhs);
    CelulaMemoria operator-(const CelulaMemoria &rhs);
    CelulaMemoria operator-() const;
    CelulaMemoria operator*(const CelulaMemoria &rhs);
    CelulaMemoria operator/(const CelulaMemoria &rhs);
    CelulaMemoria operator&(const CelulaMemoria &rhs);
    CelulaMemoria operator|(const CelulaMemoria &rhs);
    CelulaMemoria operator^(const CelulaMemoria &rhs);
    CelulaMemoria operator>>(const CelulaMemoria &rhs);
    CelulaMemoria operator<<(const CelulaMemoria &rhs);
    CelulaMemoria operator%(const CelulaMemoria &rhs);
    CelulaMemoria operator~();
    CelulaMemoria operator++();
    CelulaMemoria operator++(int);
    CelulaMemoria operator--();
    CelulaMemoria operator--(int);
    CelulaMemoria pot(const CelulaMemoria &rhs);
    CelulaMemoria pot(const double &rhs);
    bool operator==(const CelulaMemoria &rhs);
    bool operator!=(const CelulaMemoria &rhs);
    bool operator>(const CelulaMemoria &rhs);
    bool operator<(const CelulaMemoria &rhs);
    bool operator<=(const CelulaMemoria &rhs);
    bool operator>=(const CelulaMemoria &rhs);
    char toChar() const;
    int toInt() const;
    double toDouble() const;
    void convToInt();
    void convToDouble();
    void convToChar();
    union
    {
        int inteiro;
        double real;
    }celula;
    enum
    {
        INTEIRO, REAL
    }tipo;
    friend std::ostream& operator<<(std::ostream& os, const CelulaMemoria& celula);
};

#endif // CELULAMEMORIA_H
