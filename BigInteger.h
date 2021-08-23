#ifndef BIG_INTEGER
#define BIG_INTEGER
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long digit;

class BigInteger
{
private:

public:
    const int POW[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    const int EXP = 7;
    const int BASE = POW[EXP];
    BigInteger& operator =(const BigInteger &);
    BigInteger(const std::string&);
    BigInteger(digit);
    BigInteger(std::vector<digit>, bool);
    BigInteger(const BigInteger&);
    BigInteger(const BigInteger&&);
    BigInteger();
    ~BigInteger();
    std::vector<digit> val;
    bool minus;
    int size() const;
    digit get(int n)const;
    digit& operator[](int n);
    friend bool operator == (const BigInteger&, const BigInteger&);
    friend bool operator != (const BigInteger&, const BigInteger&);
    friend bool operator < (const BigInteger&, const BigInteger&);
    friend bool operator > (const BigInteger&, const BigInteger&);
    friend bool operator <= (const BigInteger&, const BigInteger&);
    friend BigInteger operator +(const BigInteger&, const BigInteger&);
    friend BigInteger operator -(const BigInteger&, const BigInteger&);
    friend BigInteger operator -(const BigInteger&);
    friend BigInteger operator *(const BigInteger&, const BigInteger&);
    friend BigInteger operator /(const BigInteger&, const BigInteger&);
    friend BigInteger operator /(const BigInteger&, digit);
    friend BigInteger operator %(const BigInteger&, const BigInteger&);
    BigInteger& operator +=(const BigInteger&);
    BigInteger& operator -=(const BigInteger&);
    BigInteger& operator *=(const BigInteger&);
    BigInteger& operator /=(const BigInteger&);
    BigInteger& operator %=(const BigInteger&);
    BigInteger& operator ++();
    BigInteger& operator --();
    void shiftLeft(int);
    friend std::ostream& operator << (std::ostream&,const BigInteger&);
    friend std::istream& operator >> (std::istream&,BigInteger&);
};

#include "BigIntegerAlg.h"

#endif // BIG_INTEGER
