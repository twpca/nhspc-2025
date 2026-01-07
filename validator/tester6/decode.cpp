#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int getSubtaskId(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (!strcmp("--testcase", argv[i - 1])) {
            return atoi(argv[i]);
        }
    }
    quitf(_fail, "Missing --testcase argument");
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = getSubtaskId(argc, argv);

    // 讀 n, k
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(1, 6, "k");
    inf.readChar('\n');

    // 讀 p_1 ... p_k
    vector<long long> p(k);
    __int128 prod = 1;
    for (int i = 0; i < k; ++i) {
        p[i] = inf.readLong(1LL, 1000000000000000000LL, "p_i");
        prod *= (__int128)p[i];
        if (i + 1 < k)
            inf.readSpace();
        else
            inf.readChar('\n');
    }
    inf.readEof();

    // 檢查 product 條件：1 <= product <= 1e18
    ensuref(prod >= 1 && prod <= (__int128)1000000000000000000LL,
            "product p_1 * ... * p_k must be in [1, 1e18]");

    if (c == 2) {    
    	ensuref(n >= 1 && n <= 10,
                "for subtask2, n must be in [1, 10]");
        ensuref(k >= 1 && k <= 2,
                "for subtask2, k must be in [1, 2]");
    }
    else if (c == 3) {
        // 子任務三：n <= 1e5
        ensuref(n >= 1 && n <= 100000,
                "for subtask3, n must be in [1, 100000]");
    }

    return 0;
}

