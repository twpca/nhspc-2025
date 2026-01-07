#include <bits/stdc++.h>

using Unif = std::uniform_int_distribution<>;
constexpr int MN_T[] = {-1, 1, 1};
constexpr int MX_T[] = {-1, 10, 10};
constexpr long long MN_XY[] = {-1LL, 0LL, 0LL};
constexpr long long MX_XY[] = {-1LL, 10LL, 100000000000LL};
std::mt19937_64 rng;

void gen_case(char fn[], int c) {
    FILE *f = fopen(fn, "w");
    int t = 10;
    fprintf(f, "%d\n", t);
    while (t--) {
        long long x, y;
        if (t==0) {
            x = MN_XY[c];
            y = MX_XY[c];
        } else {
            x =  Unif(MN_XY[c], MX_XY[c])(rng);
            y =  Unif(MN_XY[c], MX_XY[c])(rng);
        }
        fprintf(f, "%lld %lld\n", x, y);
    }
    fclose(f);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("./test2 seed test");
        assert(0);
    }

    int s = atoi(argv[1]);
    int c = atoi(argv[2]);
    rng = std::mt19937_64(s);

    char f[40];
    for (int i=1; i<=3; i++) {
        sprintf(f, "%d_%02d.in", c, i);
        gen_case(f, c);
    }
}

