#include "IntegerGenerator.h"

#ifndef SQUARE_GENERATOR
#define SQUARE_GENERATOR

class SquareGenerator : public IntegerGenerator {
protected:
    BigInteger A, C, D, lastInt;
public:
    SquareGenerator(BigInteger mod, BigInteger a, BigInteger c, BigInteger d);
    virtual BigInteger randInt();
};

#endif // SQUARE_GENERATOR
