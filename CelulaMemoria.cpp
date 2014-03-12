#include "CelulaMemoria.h"

CelulaMemoria::CelulaMemoria()
{
    this->celula.real = 0;
    this->tipo = TipoCelula::REAL;
}

CelulaMemoria::CelulaMemoria(char value)
{
    this->celula.caracter = value;
    this->tipo = TipoCelula::CAR;
}

CelulaMemoria::CelulaMemoria(int value)
{
    this->celula.inteiro = value;
    this->tipo = TipoCelula::INT;
}

CelulaMemoria::CelulaMemoria(double value)
{
    this->celula.real = value;
    this->tipo = TipoCelula::REAL;
}

CelulaMemoria &CelulaMemoria::operator=(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator=(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator=(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator=(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator=(const int &rhs)
{
    this->celula.inteiro = rhs;
    this->tipo = TipoCelula::INT;
}

CelulaMemoria &CelulaMemoria::operator=(const char &rhs)
{
    this->celula.caracter = rhs;
    this->tipo = TipoCelula::CAR;
}

CelulaMemoria &CelulaMemoria::operator=(const double &rhs)
{
    this->celula.real = rhs;
    this->tipo = TipoCelula::REAL;
}

CelulaMemoria &CelulaMemoria::operator+(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator+(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator+(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator+(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator+(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro + rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator+(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter + rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator+(const double &rhs)
{
    CelulaMemoria m;
    m.celula.real = this->celula.real + rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator-(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator-(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator-(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator-(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator-(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro - rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator-(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter - rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator-(const double &rhs)
{
    CelulaMemoria m;
    m.celula.real = this->celula.real - rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator*(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator *(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator *(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator *(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator*(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro * rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator*(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter * rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator*(const double &rhs)
{
    CelulaMemoria m;
    m.celula.real = this->celula.real * rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator/(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator /(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator /(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator /(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator/(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro / rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator/(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter / rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator/(const double &rhs)
{
    CelulaMemoria m;
    m.celula.real = this->celula.real / rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::pot(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->pot(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->pot(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->pot(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::pot(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = (int) qPow(this->celula.inteiro , (double)(rhs));
    return m;
}

CelulaMemoria &CelulaMemoria::pot(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = (char) qPow(this->celula.caracter , (double)(rhs));
    return m;
}

CelulaMemoria &CelulaMemoria::pot(const double &rhs)
{
    CelulaMemoria m;
    m.celula.real = qPow(this->celula.real , rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::operator&(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator&(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator&(rhs.celula.inteiro);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator&(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro & rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator&(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter & rhs;
    return m;
}


CelulaMemoria &CelulaMemoria::operator|(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator|(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator|(rhs.celula.inteiro);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator|(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro | rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator|(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter | rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator^(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator^(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator^(rhs.celula.inteiro);
        break;
    }
}

CelulaMemoria &CelulaMemoria::operator^(const int &rhs)
{
    CelulaMemoria m;
    m.celula.inteiro = this->celula.inteiro ^ rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator^(const char &rhs)
{
    CelulaMemoria m;
    m.celula.caracter = this->celula.caracter ^ rhs;
    return m;
}

CelulaMemoria &CelulaMemoria::operator>>(int shift)
{
    CelulaMemoria m;
    switch(this->tipo)
    {
        case TipoCelula::CAR :
            m.celula.caracter = this->celula.caracter>>shift;
        break;
        case TipoCelula::INT :
            m.celula.inteiro = this->celula.inteiro>>shift;
        break;
    }

    return m;
}

CelulaMemoria &CelulaMemoria::operator<<(int shift)
{
    CelulaMemoria m;
    switch(this->tipo)
    {
        case TipoCelula::CAR :
            m.celula.caracter = this->celula.caracter<<shift;
        break;
        case TipoCelula::INT :
            m.celula.inteiro = this->celula.inteiro<<shift;
        break;
    }

    return m;
}

CelulaMemoria &CelulaMemoria::operator>>(const CelulaMemoria &rhs)
{
    CelulaMemoria m;
    switch(this->tipo)
    {
        case TipoCelula::CAR :
            m.celula.caracter = this->celula.caracter>>rhs.celula.caracter;
        break;
        case TipoCelula::INT :
            m.celula.inteiro = this->celula.inteiro>>rhs.celula.inteiro;
        break;
    }

    return m;
}

CelulaMemoria &CelulaMemoria::operator<<(const CelulaMemoria &rhs)
{
    CelulaMemoria m;
    switch(this->tipo)
    {
        case TipoCelula::CAR :
            m.celula.caracter = this->celula.caracter<<rhs.celula.inteiro;
        break;
        case TipoCelula::INT :
            m.celula.inteiro = this->celula.inteiro<<rhs.celula.caracter;
        break;
    }

    return m;
}


bool CelulaMemoria::operator==(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator==(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator==(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator==(rhs.celula.real);
        break;
    }
}

bool CelulaMemoria::operator==(const int &rhs)
{
    return this->celula.inteiro == rhs;
}

bool CelulaMemoria::operator==(const char &rhs)
{
    return this->celula.caracter == rhs;
}

bool CelulaMemoria::operator==(const double &rhs)
{
    return this->celula.real == rhs;
}

bool CelulaMemoria::operator>(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator>(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator>(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator>(rhs.celula.real);
        break;
    }
}

bool CelulaMemoria::operator>(const int &rhs)
{
    return this->celula.inteiro > rhs;
}

bool CelulaMemoria::operator>(const char &rhs)
{
    return this->celula.caracter > rhs;
}

bool CelulaMemoria::operator>(const double &rhs)
{
    return this->celula.real > rhs;
}

bool CelulaMemoria::operator<(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->operator<(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->operator<(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->operator<(rhs.celula.real);
        break;
    }
}

bool CelulaMemoria::operator<(const int &rhs)
{
    return this->celula.inteiro < rhs;
}

bool CelulaMemoria::operator<(const char &rhs)
{
    return this->celula.caracter < rhs;
}

bool CelulaMemoria::operator<(const double &rhs)
{
    return this->celula.real < rhs;
}

CelulaMemoria &CelulaMemoria::eLogico(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->eLogico(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->eLogico(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->eLogico(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::eLogico(const int &rhs)
{
    CelulaMemoria m = (this->celula.inteiro&&rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::eLogico(const char &rhs)
{
    CelulaMemoria m = (this->celula.caracter&&rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::eLogico(const double &rhs)
{
    CelulaMemoria m = (this->celula.real&&rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::ouLogico(const CelulaMemoria &rhs)
{
    switch(rhs.tipo)
    {
        case TipoCelula::CAR :
            return this->eLogico(rhs.celula.caracter);
        break;
        case TipoCelula::INT :
            return this->eLogico(rhs.celula.inteiro);
        break;
        case TipoCelula::REAL :
            return this->eLogico(rhs.celula.real);
        break;
    }
}

CelulaMemoria &CelulaMemoria::ouLogico(const int &rhs)
{
    CelulaMemoria m = (this->celula.inteiro&&rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::ouLogico(const char &rhs)
{
    CelulaMemoria m = (this->celula.caracter&&rhs);
    return m;
}

CelulaMemoria &CelulaMemoria::ouLogico(const double &rhs)
{
    CelulaMemoria m = (this->celula.real&&rhs);
    return m;
}

TipoCelula::Tipo CelulaMemoria::getTipo()
{
    return this->tipo;
}

QString CelulaMemoria::toString()
{
    switch(this->tipo)
    {
        case TipoCelula::CAR :
            return QString(this->celula.caracter);
        break;
        case TipoCelula::INT :
            return QString::number(this->celula.inteiro);
        break;
        case TipoCelula::REAL :
            return QString::number(this->celula.real);
        break;
    }
}
