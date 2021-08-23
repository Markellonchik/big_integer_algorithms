#include "Generator.h"
#include "sstream"
#include<iostream>
std::string Generator::getGist(int len, double *seq) {
    std::ostringstream gist;
    gist << std::fixed;

    int cnt[10], sz = 0;
    for(int i = 0; i < 10; ++i)cnt[i] = 0;
    for(int i = 0; i < len; ++i)if(seq[i] >= 0 && seq[i] <= 1)cnt[int(seq[i] * 10)]++, sz++;

    for(int i = 0; i < 10; ++i) {
        gist.precision(1);
        gist << "[" << i * 0.1 << "; " << (i + 1) * 0.1 << "]\t";
        gist.precision(3);
        gist << (double)cnt[i] / sz << '\n';
    }
    return gist.str();
}
Generator::~Generator() {
}

