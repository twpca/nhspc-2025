#include "testlib.h"

const int MAXN = 100000;
const int MAXM = 300000;
const int MAXD = 300000;
const int MAXC = 1'000'000'000;

int subtask(int argc, char **argv) {
    for (int i = 0; i + 1 < argc; i++) {
        if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
        }
   }
   abort();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int task = subtask(argc, argv);

    int n = inf.readInt(1, MAXN);
    inf.readSpace();
    int m = inf.readInt(1, MAXM);
    inf.readSpace();
    int d = inf.readInt(1, MAXD);
    inf.readEoln();

    if (task == 1) ensure(d == 1);
    if (task == 2) ensure(n <= 100);

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n);
        inf.readSpace();
        int v = inf.readInt(1, n);
        inf.readSpace();
        int w = inf.readInt(1, MAXC);
        inf.readSpace();
        int l = inf.readInt(0, d - 1);
        inf.readSpace();
        int r = inf.readInt(l + 1, d);
        inf.readEoln();

        ensure(u != v);

        if (task == 2 || task == 3) ensure(r == d);
        if (task == 4) ensure(w == 1);
    }
    inf.readEof();
}