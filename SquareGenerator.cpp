#include "SquareGenerator.h"

SquareGenerator::SquareGenerator(BigInteger mod, BigInteger a, BigInteger c, BigInteger d) : IntegerGenerator(mod), A(a), C(c), D(d), lastInt(c)
{
}

BigInteger SquareGenerator::randInt()
{
    BigInteger square = lastInt * lastInt % MOD;
    return lastInt = ( D * square + A * lastInt + C ) % MOD;
}
