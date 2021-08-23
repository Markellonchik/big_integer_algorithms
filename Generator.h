#include <string>
#include "BigInteger.h"
#ifndef GENERATOR
#define GENERATOR

class Generator{
protected:
public:
    virtual std::string getGist(int len, double *seq);
    virtual ~Generator();
};

#endif // GENERATOR
