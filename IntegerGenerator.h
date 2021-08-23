#include "Generator.h"

#ifndef INTEGER_GENERATOR
#define INTEGER_GENERATOR

class IntegerGenerator : public Generator {
protected:
    BigInteger MOD;
public:
    IntegerGenerator(BigInteger mod);
    virtual BigInteger randInt()=0;
};

#endif // INTEGER_GENERATOR

