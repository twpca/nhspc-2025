#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

constexpr int MIN_N = 1;
constexpr int MAX_N = 100'000;

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}

int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readChar('\n');

    string P;
    if (s == 1)
        P = inf.readLine("\\(*\\)*", "P");
    else
        P = inf.readLine("[()]+", "P");

    ensure(P.length() == n);

    if (s == 2) {
        int removed = 0, cnt = 0;
        for (char ch : P) {
            if (ch == '(') ++cnt;
            else --cnt;

            if (cnt == -1) {
                ++removed;
                ++cnt;
            }
        }
        int ans = removed + cnt;
        ensure(ans == 0 || ans == 2);
    }

    inf.readEof();
}
