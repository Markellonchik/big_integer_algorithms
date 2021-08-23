#include "BigIntegerAlg.h"

void normalize_len(BigInteger &X)
{
    while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
}

void light_normalize(BigInteger &X)
{
    X.val.push_back(0);
    for(int i = 0; i < X.size(); ++i)
    {
        if(X[i] < 0)X[i + 1]--, X[i] += X.BASE;
        if(X[i] >= X.BASE)X[i + 1]++, X[i] -= X.BASE;
    }
    while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
    normalize_sign(X);
}

void normalize(BigInteger &X)
{
    X.val.push_back(0);
    for(int i = 0; i + 1 < X.size(); ++i)
    {
        int carr = X[i] / X.BASE;
        X[i] %= X.BASE;
        if(X[i] < 0)X[i] += X.BASE, carr--;
        X[i + 1] += carr;
    }
    normalize_len(X);
    normalize_sign(X);
}

void normalize_sign(BigInteger &X)
{
    if(X[X.size() - 1] < 0)
    {
        X.minus ^= 1;
        for(int i = 0; i < X.size(); ++i)X[i] = -X[i];
        for(int i = 0; i + 1 < X.size(); ++i)
        {
            if(X[i] < 0)X[i] += X.BASE, X[i + 1]--;
        }
        while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
    }
}

BigInteger sqrt(BigInteger A)
{
    BigInteger l = 0;
    BigInteger r = A;
    while(l < r)
    {
        BigInteger mid = (l + r + 1) / 2;
        if(mid * mid <= A) l = mid;
        else r = mid - 1;
    }
    return l;
}

BigInteger pow(BigInteger A, BigInteger N)
{
    BigInteger R("1");
    while(N > 0)
    {
        if(N % 2 == 1)R *= A;
        A *= A;
        N /= 2;
    }
    return R;
}
BigInteger pow_mod(BigInteger A, BigInteger N, BigInteger MOD)
{
    BigInteger R("1");
    while(N > 0)
    {
        if(N % 2 == 1)R *= A, R %= MOD;
        A *= A;
        A %= MOD;
        N /= 2;
    }
    return R;
}
BigInteger abs(BigInteger A)
{
    A.minus = false;
    return A;
}

BigInteger fac(BigInteger N)
{
    BigInteger R(1);
    for(BigInteger i = 1; i <= N; ++i)
    {
        R *= i;
    }
    return R;
}

BigInteger gcd(BigInteger A, BigInteger B)
{
    if(A == 0)return B;
    return gcd(B % A, A);
}

//MUL DIV

BigInteger standart_mul(BigInteger X, BigInteger Y)
{
    int sign = 1;
    if(X < 0)sign = -sign;
    if(Y < 0)sign = -sign;
    X = abs(X);
    Y = abs(Y);
    BigInteger R("");
    for(int i = 0; i < X.size() + Y.size(); ++i)R.val.push_back(0);
    for(int i = 0; i < X.size(); ++i)
    {
        for(int j = 0; j < Y.size(); ++j)
        {
            R[i + j] += X.get(i) *
                        Y.get(j);
            if(R[i + j] >= R.BASE)
            {
                R[i + j + 1] += R[i + j] / R.BASE;
                R[i + j] %= R.BASE;
            }
        }
    }
    if(sign < 0)R = -R;
    normalize(R);
    return R;
}

BigInteger standart_div(BigInteger X, BigInteger Y)
{
    BigInteger R("");
    int sign = 1;
    if(X < 0)sign = -sign;
    if(Y < 0)sign = -sign;
    X = abs(X);
    Y = abs(Y);
    BigInteger A("0");
    BigInteger B = Y;
    B.minus = false;

    BigInteger BASE(R.BASE);

    for(int i = X.size() - 1; i >= 0; i--)
    {
        A *= BASE;
        A += X.get(i);

        digit l = 0;
        digit r = R.BASE - 1;
        while(l < r)
        {
            digit mid = (l + r + 1) / 2;
            if(B * BigInteger(mid) <= A)l = mid;
            else r = mid - 1;
        }
        A -= B * BigInteger(l);
        R.val.push_back(l);
    }
    reverse(R.val.begin(), R.val.end());
    while(R.size() > 1 && R[R.size() - 1] == 0)R.val.pop_back();

    if(sign < 0)R = -R;
    normalize(R);
    return R;
}

const digit MIN_KARATSUBA_LEN = 3;

void karatsuba_divide(BigInteger &A, BigInteger &A0, BigInteger &A1, int len)
{
    for(int i = 0; i < len; ++i)A0.val.push_back(i < A.size() ? A[i] : 0);
    for(int i = len; i < len + len; ++i)A1.val.push_back(i < A.size() ? A[i] : 0);
    normalize_len(A0);
    normalize_len(A1);
}

BigInteger karatsuba_mul(BigInteger A, BigInteger B)
{
    int len = std::max(A.size(), B.size());
    if(len < MIN_KARATSUBA_LEN)return standart_mul(A, B);
    len = (len + 1) / 2;
    BigInteger R("");
    BigInteger A0, A1, B0, B1;
    karatsuba_divide(A, A0, A1, len);
    karatsuba_divide(B, B0, B1, len);

    BigInteger M0 = karatsuba_mul(A0 , B0);
    BigInteger M2 = karatsuba_mul(A1 , B1);

    BigInteger M1 = karatsuba_mul((A0 + A1), (B0 + B1)) - M0 - M2;


    int SZ1 = M1.size(), SZ2 = M2.size();

    for(int i = 0; i < len; ++i)M1.val.push_back(0), M2.val.push_back(0), M2.val.push_back(0);
    for(int i = M1.size() - 1; i >= M1.size() - SZ1; --i)
    {
        M1[i] = M1[i - len];
        M1[i - len] = 0;
    }
    for(int i = M2.size() - 1; i >= M2.size() - SZ2; --i)
    {
        M2[i] = M2[i - len - len];
        M2[i - len - len] = 0;
    }

    return M0 + M1 + M2;
}

const int TOOM_SIZE = 3;

void toom_divide(BigInteger A, BigInteger &A0, BigInteger &A1, BigInteger &A2)
{
    while(A.size() % 3 != 0)A.val.push_back(0);
    for(int i = 0; i < A.size(); ++i){
        if(i < A.size() / 3)A0.val.push_back(A[i]);
        else if(i < A.size() / 3 * 2)A1.val.push_back(A[i]);
        else A2.val.push_back(A[i]);
    }
}

BigInteger toom_mul(BigInteger A, BigInteger B)
{
    BigInteger A0, A1, A2, B0, B1, B2;
    if(A.size() + B.size() < TOOM_SIZE)return standart_mul(A, B);
    int sz = std::max(A.size(), B.size());
    while(sz % 3 != 0)sz++;
    while(A.size() < sz)A.val.push_back(0);
    while(B.size() < sz)B.val.push_back(0);

    toom_divide(A, A0, A1, A2);
    toom_divide(B, B0, B1, B2);

    BigInteger r0, r1, r2, r3, r4;
    r0 = A0 - A1 - A1 + 4 * A2;
    r1 = A0 - A1 + A2;
    r2 = A0;
    r3 = A0 + A1 + A2;
    r4 = A0 + A1 + A1 + 4 * A2;
    BigInteger s0, s1, s2, s3, s4;
    s0 = B0 - B1 - B1 + 4 * B2;
    s1 = B0 - B1 + B2;
    s2 = B0;
    s3 = B0 + B1 + B2;
    s4 = B0 + B1 + B1 + 4 * B2;

    BigInteger t0, t1, t2, t3, t4;
    t0 = toom_mul(r0, s0);
    t1 = toom_mul(r1, s1);
    t2 = toom_mul(r2, s2);
    t3 = toom_mul(r3, s3);
    t4 = toom_mul(r4, s4);

    BigInteger z0, z1, z2, z3, z4;
    //std::cout << t0 << " " << t1 << " " << t2 << " " << t3 << " " << t4 << std::endl;
    z0 = t2;
    z1 = ( t0 / 4 - (t1 + t1) / 1 + (t3 + t3) / 1 - t4 / 4 ) / 3;
    z2 = -t0 / 24 + (t1 + t1) / 3 - (t2 * 5) / 4 + (t3 + t3) / 3 - t4 / 24;
    z3 = ( -t0 / 2 + t1 / 1 - t3 / 1 + t4 / 2 ) / 6;
    z4 = t0 / 24 - t1 / 6 + t2 / 4 - t3 / 6 + t4 / 24;

    z3.shiftLeft(sz / 3);
    z2.shiftLeft(sz / 3 * 2);
    z1.shiftLeft(sz / 3 * 3);
    z0.shiftLeft(sz / 3 * 4);

    //std::cout << z0 << " " << z1 << " " << z2 << " " << z3 << " " << z4 << "\n";

    BigInteger R = z0 + z1 + z2 + z3 + z4;
    normalize(R);
    return R;
}

std::vector<cd> FFT(std::vector<cd> A)
{
    int n = A.size();
    if(n == 1)return A;
    std::vector<cd> A0, A1;
    for(int i = 0; i < n; ++i)
    {
        if(i & 1)A1.push_back(A[i]);
        else A0.push_back(A[i]);
    }

    A0 = FFT(A0);
    A1 = FFT(A1);

    double ang = 2 * acos(-1) / n;
    for(int i = 0; i < n / 2; ++i)
    {
        cd wi = cd(cos(ang * i), sin(ang * i));
        A[i] = A0[i] + wi * A1[i];
        A[i + n / 2] = A0[i] - wi * A1[i];
    }
    return A;
}


BigInteger FFT_mul(BigInteger A, BigInteger B)
{
    int sz = A.size() + B.size();
    int N = 1;
    while(N < sz)N <<= 1;
    std::vector<cd> A1(N), B1(N);
    for(int i = 0; i < N; ++i)
    {
        A1[i] = i < A.size() ? A[i] : 0;
        B1[i] = i < B.size() ? B[i] : 0;
    }

    std::vector<cd> FFT1 = FFT(A1);
    std::vector<cd> FFT2 = FFT(B1);

    for(int i = 0; i < N; ++i)FFT1[i] *= FFT2[i];

    FFT1 = FFT(FFT1);

    for(int i = 0; i < N; ++i)FFT1[i] /= N;
    reverse(FFT1.begin() + 1, FFT1.end());

    std::vector<digit> r(N);
    for(int i = 0; i < N; ++i)r[i] = digit(0.5 + FFT1[i].real());

    BigInteger R(r, false);

    return R;
}

//PRIME

bool prime(BigInteger A){
    if(A == 2)return true;
    if(A % 2 == 0)return false;
    BigInteger sq = sqrt(A);
    for(BigInteger i = 3; i <= sq; i += 2){
        if(A % i == 0)return false;
    }
    return true;
}

const BigInteger RAND_A("2819128"), RAND_C("13251828"), RAND_D("2183192171");
const int FERMA_ITER = 30;

bool primeFerma(BigInteger A)
{
    if(A == 1)return false;
    if(A == 2 || A == 3)return true;
    BigInteger rnd;
    SquareGenerator gen(A - 1, RAND_A, RAND_C, RAND_D);
    for(int i = 0; i < FERMA_ITER; ++i)
    {
        rnd = gen.randInt() + 1;
        if(pow_mod(rnd, A - 1, A) != 1)return false;
    }
    return true;
}

const int MILLER_RABIN_ITER = 60;

bool primeMillerRabin(BigInteger A)
{
    if(A == 2)return true;
    if(A % 2 == 0)return false;

    BigInteger rnd;
    SquareGenerator gen(A - 1, RAND_A, RAND_C, RAND_D);

    BigInteger A1 = A - 1;
    BigInteger Q = A1;
    int p = 0;
    BigInteger R;
    while(Q % 2 == 0)
    {
        p++;
        Q /= 2;
    }

    for(int i = 0; i < MILLER_RABIN_ITER; ++i)
    {
        rnd = gen.randInt() + 1;
        R = pow_mod(rnd, Q, A);
        if(R == 1 || R == A1)return true;

        for(int j = 1; j < p; ++j)
        {
            R = R * R % A;
            if(R == A1)return true;
        }
    }
    return false;
}

const int SOLOVAY_STRASSEN_ITER = 30;

int jacobi(BigInteger A, BigInteger N)
{
    int r = 1;
    while(A != 0)
    {
        while(A % 2 == 0)
        {
            A /= 2;
            BigInteger k = N % 8;
            if(k == 3 || k == 5)r = -r;
        }
        std::swap(N, A);
        if(A % 4 == N % 4 && N % 4 == 3)r = -r;
        A %= N;
    }
    if(N == 1)return r;
    else return 0;
}

bool primeSolovayStrassen(BigInteger A)
{
    if(A == 2)return true;
    if(A % 2 == 0)return false;

    BigInteger rnd;
    BigInteger A1 = A - 1;
    BigInteger Ahalf = A1 / 2;
    SquareGenerator gen(A1, RAND_A, RAND_C, RAND_D);

    for(int i = 0; i < SOLOVAY_STRASSEN_ITER; ++i)
    {
        rnd = gen.randInt();
        int jac = jacobi(rnd, A);
        BigInteger pw = pow_mod(rnd, Ahalf, A);
        if(jac == 0 && pw != 0)return false;
        if(jac == 1 && pw != 1)return false;
        if(jac == -1 && pw != A1)return false;
    }
    return true;
}
