#ifndef BIG_INTEGER_ALG
#define BIG_INTEGER_ALG

#include "BigInteger.h"
#include "Generators.h"

#include <complex>
typedef std::complex<double> cd;


void normalize_len(BigInteger &);
void light_normalize(BigInteger &);
void normalize(BigInteger &);
void normalize_sign(BigInteger &);

BigInteger sqrt(BigInteger A);
BigInteger abs(BigInteger A);
BigInteger pow(BigInteger A, BigInteger N);
BigInteger pow_mod(BigInteger A, BigInteger N, BigInteger MOD);
BigInteger fac(BigInteger N);
BigInteger gcd(BigInteger A, BigInteger B);

//MUL DIV
BigInteger standart_mul(BigInteger A, BigInteger B);
BigInteger standart_div(BigInteger A, BigInteger B);
BigInteger karatsuba_mul(BigInteger A, BigInteger B);
BigInteger toom_mul(BigInteger A, BigInteger B);
std::vector<cd> FFT(std::vector<cd> A);
BigInteger FFT_mul(BigInteger A, BigInteger B);

//PRIME
bool prime(BigInteger A);
bool primeFerma(BigInteger A);
bool primeMillerRabin(BigInteger A);
int jacobi(BigInteger A, BigInteger N);
bool primeSolovayStrassen(BigInteger A);

#endif
