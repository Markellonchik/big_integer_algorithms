#include "SquareGenerator.h"

#ifndef LINEAR_GENERATOR
#define LINEAR_GENERATOR

class LinearGenerator : public SquareGenerator {
public:
    LinearGenerator(BigInteger mod, BigInteger a, BigInteger c);
};

#endif // LINEAR_GENERATOR
