
#include "BigInteger.h"
#include <iostream>

using namespace std;

int main()
{
    BigInteger a, b;
    cin >> a >> b;
    cout << standart_mul(a, b) << endl;
    cout << FFT_mul(a, b) << endl;
    cout << karatsuba_mul(a, b) << endl;
    cout << primeFerma(a) << endl;
    cout << primeMillerRabin(a) << endl;
    cout << primeSolovayStrassen(a) << endl;
}
