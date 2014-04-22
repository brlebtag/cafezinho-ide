#include "CelulaMemoria.h"

CelulaMemoria::CelulaMemoria()
{
    this->celula.real = 0.0;
    this->tipo = INTEIRO;
}

CelulaMemoria::CelulaMemoria(const CelulaMemoria &rhs)
{
    this->tipo = rhs.tipo;
    if(rhs.tipo == INTEIRO)
    {
        this->celula.inteiro = rhs.celula.inteiro;
    }
    else
    {
        this->celula.real = rhs.celula.real;
    }
}


CelulaMemoria::CelulaMemoria(const int value)
{
    this->celula.inteiro = value;
    this->tipo = INTEIRO;
}

CelulaMemoria::CelulaMemoria(const char value)
{
    this->celula.inteiro = (int) value;
    this->tipo = INTEIRO;
}

CelulaMemoria::CelulaMemoria(const double value)
{
    this->celula.real = value;
    this->tipo = REAL;
}

CelulaMemoria CelulaMemoria::operator=(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        this->celula.inteiro = rhs.celula.inteiro;
        this->tipo = INTEIRO;
    }
    else
    {
        this->celula.real = rhs.celula.real;
        this->tipo = REAL;
    }
    return (*this);
}

CelulaMemoria CelulaMemoria::operator=(const int &rhs)
{
    this->celula.inteiro = rhs;
    this->tipo = INTEIRO;
    return (*this);
}

CelulaMemoria CelulaMemoria::operator=(const double &rhs)
{
    this->celula.real = rhs;
    this->tipo = REAL;
    return (*this);
}

CelulaMemoria CelulaMemoria::operator=(const char &rhs)
{
    this->celula.inteiro = (int) rhs;
    this->tipo = INTEIRO;
    return (*this);
}

CelulaMemoria CelulaMemoria::operator+(const CelulaMemoria &rhs)
{
    CelulaMemoria r;

    if( this->tipo != REAL && rhs.tipo == REAL)
    {
        r.celula.real = ((double)this->celula.inteiro) + rhs.celula.real;
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo != REAL)
    {
        r.celula.real = this->celula.real + ((double)rhs.celula.inteiro);
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo == REAL)
    {
        r.celula.real = this->celula.real + rhs.celula.real;
        r.tipo = REAL;
    }
    else
    {
        r.celula.inteiro = this->celula.inteiro + rhs.celula.inteiro;
        r.tipo = INTEIRO;
    }

    return r;
}

CelulaMemoria CelulaMemoria::operator+(const int &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro + rhs;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator-(const CelulaMemoria &rhs)
{
    CelulaMemoria r;

    if( this->tipo != REAL && rhs.tipo == REAL)
    {
        r.celula.real = ((double)this->celula.inteiro) - rhs.celula.real;
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo != REAL)
    {
        r.celula.real = this->celula.real - ((double)rhs.celula.inteiro);
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo == REAL)
    {
        r.celula.real = this->celula.real - rhs.celula.real;
        r.tipo = REAL;
    }
    else
    {
        r.celula.inteiro = this->celula.inteiro - rhs.celula.inteiro;
        r.tipo = INTEIRO;
    }

    return r;
}

CelulaMemoria CelulaMemoria::operator-() const
{
    CelulaMemoria m;

    if( this->tipo == REAL )
    {
        m.celula.real = - this->celula.real;
        m.tipo = REAL;
    }
    else
    {
        m.celula.inteiro = - this->celula.inteiro;
        m.tipo = INTEIRO;
    }

    return m;
}

CelulaMemoria CelulaMemoria::operator*(const CelulaMemoria &rhs)
{
    CelulaMemoria r;

    if( this->tipo != REAL && rhs.tipo == REAL)
    {
        r.celula.real = ((double)this->celula.inteiro) * rhs.celula.real;
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo != REAL)
    {
        r.celula.real = this->celula.real * ((double)rhs.celula.inteiro);
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo == REAL)
    {
        r.celula.real = this->celula.real * rhs.celula.real;
        r.tipo = REAL;
    }
    else
    {
        r.celula.inteiro = this->celula.inteiro * rhs.celula.inteiro;
        r.tipo = INTEIRO;
    }

    return r;
}

CelulaMemoria CelulaMemoria::operator/(const CelulaMemoria &rhs)
{
    CelulaMemoria r;

    if( this->tipo != REAL && rhs.tipo == REAL)
    {
        r.celula.real = ((double)this->celula.inteiro) / rhs.celula.real;
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo != REAL)
    {
        r.celula.real = this->celula.real / ((double)rhs.celula.inteiro);
        r.tipo = REAL;
    }
    else if(this->tipo == REAL && rhs.tipo == REAL)
    {
        r.celula.real = this->celula.real / rhs.celula.real;
        r.tipo = REAL;
    }
    else
    {
        r.celula.real = (double)(((double) this->celula.inteiro) / ((double)rhs.celula.inteiro));
        r.tipo = REAL;
    }

    return r;
}

CelulaMemoria CelulaMemoria::operator&(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro & rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator|(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro | rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator^(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro ^ rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator>>(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro >> rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator<<(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro << rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

CelulaMemoria CelulaMemoria::operator%(const CelulaMemoria &rhs)
{
    CelulaMemoria r;
    r.celula.inteiro = this->celula.inteiro % rhs.celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

bool CelulaMemoria::operator==(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro == rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) == rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real == rhs.celula.real;
        else
            return this->celula.inteiro == ((int)(rhs.celula.real));
    }
}

bool CelulaMemoria::operator>(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro > rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) > rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real > rhs.celula.real;
        else
            return this->celula.inteiro > ((int)(rhs.celula.real));
    }
}

bool CelulaMemoria::operator<(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro < rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) < rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real < rhs.celula.real;
        else
            return this->celula.inteiro < ((int)(rhs.celula.real));
    }
}

bool CelulaMemoria::operator<=(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro <= rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) <= rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real <= rhs.celula.real;
        else
            return this->celula.inteiro <= ((int)(rhs.celula.real));
    }
}

bool CelulaMemoria::operator>=(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro >= rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) >= rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real >= rhs.celula.real;
        else
            return this->celula.inteiro >= ((int)(rhs.celula.real));
    }
}

bool CelulaMemoria::operator!=(const CelulaMemoria &rhs)
{
    if(rhs.tipo == INTEIRO)
    {
        if(this->tipo == INTEIRO)
            return this->celula.inteiro != rhs.celula.inteiro;
        else
            return ((int)(this->celula.real) != rhs.celula.inteiro);
    }
    else
    {
        if(this->tipo == REAL)
            return this->celula.real != rhs.celula.real;
        else
            return this->celula.inteiro != ((int)(rhs.celula.real));
    }
}

char CelulaMemoria::toChar() const
{
    if(this->tipo==REAL)
        return (int) this->celula.real;
    return (char) this->celula.inteiro;
}

int CelulaMemoria::toInt() const
{
    if(this->tipo==REAL)
        return (int) this->celula.real;
    return this->celula.inteiro;
}

double CelulaMemoria::toDouble() const
{
    if(this->tipo==INTEIRO)
        return (double) this->celula.inteiro;
    return this->celula.real;
}

CelulaMemoria CelulaMemoria::operator++()
{
    (*this) = (*this) + 1;
    return *this;
}

CelulaMemoria CelulaMemoria::operator++(int)
{
    CelulaMemoria r(*this);
    operator++();
    return r;
}

CelulaMemoria CelulaMemoria::operator--()
{
     (*this) = (*this) - 1;
    return *this;
}

CelulaMemoria CelulaMemoria::operator--(int)
{
    CelulaMemoria r(*this);
    operator--();
    return r;
}

CelulaMemoria CelulaMemoria::operator~()
{
    CelulaMemoria r;
    r.celula.inteiro = ~ this->celula.inteiro;
    r.tipo = INTEIRO;
    return r;
}

void CelulaMemoria::convToInt()
{
    if(this->tipo != INTEIRO)
        this->celula.inteiro = (int) this->celula.real;
    this->tipo = INTEIRO;
}

void CelulaMemoria::convToDouble()
{
     if(this->tipo != REAL)
        this->celula.real = (double) this->celula.inteiro;
    this->tipo = REAL;
}

void CelulaMemoria::convToChar()
{
    this->celula.inteiro = ((int)((char)this->celula.inteiro));
    this->tipo = INTEIRO;
}

CelulaMemoria CelulaMemoria::pot(const CelulaMemoria &rhs)
{
    CelulaMemoria m;
    double a, b;

    if(this->tipo == INTEIRO)
        a = this->celula.inteiro;
    else
        a = this->celula.real;

    if(rhs.tipo == INTEIRO)
        b = rhs.celula.inteiro;
    else
        b = rhs.celula.real;

    m.celula.real = qPow(a, b);
    m.tipo = REAL;
    return m;
}
CelulaMemoria CelulaMemoria::pot(const double &rhs)
{
    CelulaMemoria m;
    double a;

    if(this->tipo == INTEIRO)
        a = this->celula.inteiro;
    else
        a = this->celula.real;

    m.celula.real = qPow(a, rhs);
    m.tipo = REAL;
    return m;
}

std::ostream& operator<<(std::ostream& os, const CelulaMemoria& celula)
{
    if(celula.tipo==CelulaMemoria::INTEIRO)
        os<<celula.toInt();
    else
        os<<celula.toDouble();
}
