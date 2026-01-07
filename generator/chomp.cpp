#include "jngen.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>

std::mt19937 rng;

void gen(int index, std::ofstream& outf){
    int cls = getOpt("cls");
    int T;

    if(cls == 1) T = 1;
    else T = ((rng() % 3 == 0) ? (1000) : (rng() % 500 + 501));

    outf << T << std::endl;

    for(int t = 0; t < T; t++){
        int N;
        if(cls == 2) N = rng() % 50 + 1;
        else N = rng() % 500 + 1;
        
        int p, q, r;
        if(cls == 1){
            p = 0;
            q = rng() % (N + 1);
            r = rng() % (N + 1);
            if(q > r) std::swap(q, r);
            q = q - p;
            r = r - p - q;
        }
        else{
            p = rng() % (N + 1);
            q = rng() % (N + 1);
            r = rng() % (N + 1);
            if(p > q) std::swap(p, q);
            if(q > r) std::swap(q, r);
            if(p > q) std::swap(p, q);
            q = q - p;
            r = r - p - q;
        }
        if(p + q + r == 0) r = 1;
        outf << N << " " << p << " " << q << " " << r << std::endl;
    }
    return;
}

int main(int argc, char* argv[]) {
    parseArgs(argc, argv);
    
    int cls = getOpt("cls");
    int cases = getOpt("cases");
    std::string seed = getOpt("seed");
    
    std::seed_seq seq(seed.begin(), seed.end());
    rng.seed(seq);
    
    for(int i = 1; i <= cases; i++){
        std::ofstream outfile;
        char fn[100] = "";
        sprintf(fn, "%d_%02d.in", cls, i);
        outfile.open(fn);
        gen(i, outfile);
        outfile.close();
    }

    return 0;
}