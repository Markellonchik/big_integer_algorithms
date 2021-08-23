#include "BigIntegerAlg.h"
#include "BigInteger.h"
#include <cstdlib>

BigInteger::BigInteger(const std::string&input)
{
    digit st = 1;
    int ps = 0;
    int frst = 0;

    minus = false;
    if(input.size() > 0 && input[frst] == '-')minus = true, frst = 1;

    for(int i = (int)input.size() - 1; i >= frst; i--, st *= 10)
    {
        if(st >= BASE)ps++, st = 1;
        if(ps == val.size())val.push_back(0);
        val[val.size() - 1] += st * (input[i] - '0');
    }
}

BigInteger::BigInteger(digit input) : minus(false)
{
    if(input < 0)input = -input, minus = true;
    while(input > 0)
    {
        val.push_back(input % BASE);
        input /= BASE;
    }
    if(val.size() == 0)val.push_back(0);
}

BigInteger::BigInteger(std::vector<digit> input, bool minus): val(input), minus(minus)
{
    normalize(*this);
}

BigInteger::BigInteger() : BigInteger("")
{
}

BigInteger::~BigInteger()
{
}

BigInteger& BigInteger::operator =(const BigInteger &X)
{
    minus = X.minus;
    val = X.val;
    return *this;
}

BigInteger::BigInteger(const BigInteger &X)
{
    minus = X.minus;
    val = X.val;
}
BigInteger::BigInteger(const BigInteger &&X)
{
    minus = X.minus;
    val = X.val;
}

BigInteger operator +(const BigInteger &X,const BigInteger &Y)
{
    int fac1 = 1, fac2 = 1;
    if(X.minus)fac1 *= -1;
    if(Y.minus)fac2 *= -1;

    BigInteger R("");
    R.val.size();
    for(int i = 0; i < std::max(X.size(), Y.size()); ++i)
    {
        R.val.push_back((i < X.size() ? X.get(i) : 0) * fac1
                       +(i < Y.size() ? Y.get(i) : 0) * fac2);
    }
    normalize(R);
    return R;
}
BigInteger operator -(const BigInteger &X, const BigInteger &Y)
{
    int fac1 = 1, fac2 = -1;
    if(X.minus)fac1 *= -1;
    if(Y.minus)fac2 *= -1;

    BigInteger R("");
    R.val.size();
    for(int i = 0; i < std::max(X.size(), Y.size()); ++i)
    {
        R.val.push_back((i < X.size() ? X.get(i) : 0) * fac1
                       +(i < Y.size() ? Y.get(i) : 0) * fac2);
    }
    normalize(R);
    return R;
}
BigInteger operator -(const BigInteger &X)
{
    BigInteger R = X;
    R.minus ^= 1;
    return R;
}
BigInteger operator *(const BigInteger &X, const BigInteger &Y)
{
    digit fac = 1;
    if(X.minus)fac *= -1;
    if(Y.minus)fac *= -1;

    BigInteger R = standart_mul(abs(X), abs(Y));
    if(fac < 0)R.minus ^= 1;
    return R;
}
BigInteger operator /(const BigInteger &X, const BigInteger &Y)
{
    return standart_div(X, Y);
}
BigInteger operator /(const BigInteger &X, digit y)
{
    return standart_div(X, BigInteger(y));
}

BigInteger operator %(const BigInteger& X, const BigInteger& Y)
{
    digit fac = 1;
    if(X.minus)fac *= -1;
    if(Y.minus)fac *= -1;
    BigInteger R = abs(X) - abs(X) / abs(Y) * abs(Y);
    if(fac < 0)R.minus ^= 1;
    return R;
}

BigInteger& BigInteger::operator +=(const BigInteger&X)
{
    return *this = *this + X;
}
BigInteger& BigInteger::operator -=(const BigInteger&X)
{
    return *this = *this - X;
}
BigInteger& BigInteger::operator *=(const BigInteger&X)
{
    return *this = *this * X;
}
BigInteger& BigInteger::operator /=(const BigInteger&X)
{
    return *this = *this / X;
}
BigInteger& BigInteger::operator %=(const BigInteger&X)
{
    return *this = *this % X;
}

BigInteger& BigInteger::operator ++()
{
    *this += BigInteger(1);
    return *this;
}
BigInteger& BigInteger::operator --()
{
    *this -= BigInteger(1);
    return *this;
}

bool operator < (const BigInteger& X, const BigInteger &Y)
{
    if(X.minus && !Y.minus)return true;
    if(!X.minus && Y.minus)return false;

    if(X.size() < Y.size())return true;
    if(X.size() > Y.size())return false;
    for(int i = X.size() - 1; i >= 0; i--)
    {
        if(X.get(i) < Y.get(i))return true;
        if(X.get(i) > Y.get(i))return false;
    }
    return false;
}
bool operator == (const BigInteger &X,const BigInteger &Y)
{
    if(X.minus != Y.minus)return false;
    if(X.size() != Y.size())return false;
    for(int i = 0; i < X.size(); ++i)
        if(X.get(i) != Y.get(i))return false;
    return true;
}
bool operator != (const BigInteger &X,const BigInteger &Y)
{
    return !(X == Y);
}
bool operator > (const BigInteger& X, const BigInteger &Y)
{
    if(X < Y || X == Y)return false;
    return true;
}
bool operator <= (const BigInteger& X, const BigInteger &Y)
{
    return !(X > Y);
}

digit& BigInteger::operator[](int n)
{
    return val[n];
}

int BigInteger::size() const
{
    return val.size();
}

digit BigInteger::get(int n) const
{
    return val[n];
}

void BigInteger::shiftLeft(int len)
{
    int sz = val.size();
    for(int i = 0; i < len; ++i)val.push_back(0);
    for(int i = val.size() - 1; i >= val.size() - sz; --i)
    {
        val[i] = val[i - sz];
        val[i - sz] = 0;
    }
}

std::ostream& operator << (std::ostream &out, const BigInteger &X)
{
    if(X.minus)out << "-";
    out << X.get(X.size() - 1);
    for(int i = X.size() - 2; i >= 0; i--){
        for(int j = 1; j < X.EXP; ++j)if(X.get(i) < X.POW[j])out << 0;
        out << X.get(i);
    }
    return out;
}
std::istream& operator >> (std::istream &in, BigInteger &X)
{
    std::string input;
    in >> input;
    X = BigInteger(input);
    return in;
}
