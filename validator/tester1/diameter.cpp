#include "testlib.h"
#include <string>

const int MAXN = 2000;

int subtask(int argc, char **argv) {
    for (int i = 0; i + 1 < argc; i++) {
        if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
        }
   }
   abort();
}

std::string g[MAXN];
int rt[MAXN];

int dsu_find(int v) {
    if (rt[v] == v) return v;
    return rt[v] = dsu_find(rt[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int task = subtask(argc, argv);

    for (int iter = 0; iter < 2; ++iter) {
        int n = inf.readInt(1, MAXN);
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            g[i] = inf.readToken("[01]{" + std::to_string(n) + "}");
            inf.readEoln();
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    ensure(g[i][j] == '0');
                } else {
                    ensure(g[i][j] == g[j][i]);
                }
            }
        }

        if (task == 1) {
            if (iter == 1) ensure(n == 1);
        } else if (task == 2) {
            for (int i = 0; i < n; ++i) rt[i] = i;
            for (int i = 0; i < n; ++i) {
                for (int j = i; j < n; ++j) {
                    if (g[i][j] == '1') {
                        ensure(dsu_find(i) != dsu_find(j));
                        rt[dsu_find(i)] = dsu_find(j);
                    }
                }
            }
            for (int i = 1; i < n; ++i) {
                ensure(dsu_find(0) == dsu_find(i));
            }
        } else if (task == 3) {
            int m = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = i; j < n; ++j) {
                    if (g[i][j] == '1') {
                        m++;
                    }
                }
            }
            ensure(m <= 4000);
        }
    }
    
    inf.readEof();
}