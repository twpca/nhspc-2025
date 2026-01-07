#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#include "../../generator/testlib.h"
using namespace std;
using pii = pair<int, int>;

int subtask(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp("--testcase", argv[i - 1])) {
            return atoi(argv[i]);
        }
    }
    exit(0);
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = subtask(argc, argv);
    int n = inf.readInt(2, 1000000);
    inf.readSpace();
    int k = inf.readInt(1, n);
    inf.readChar('\n');

    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        a[i].first = inf.readInt(1, 1000000000);
        inf.readSpace();
        a[i].second = inf.readInt(0, 1000000);
        if (i != n - 1)
            inf.readSpace();
        else
            inf.readChar('\n');
    }
    inf.readEof();

    if (c == 1) {

        ensuref(n >= 1 && n <= 1000, "for task1 n must in [1, 1000]");
        ensuref(k == 1, "for task1 k must equal to 1");

        for (auto& [x, y] : a) {
            ensuref(x > 0 && x <= 1e9, "for task1 x_i must in [1, 1e9]");
            ensuref(y >= 0 && y < k, "for task1 s_i must equal to 0");
        }

    } else if (c == 2) {

        ensuref(n >= 1 && n <= 1000, "for task2 n must in [1, 1000]");
        ensuref(k >= 1 && k <= n, "k must in [1, n]");

        for (auto& [x, y] : a) {
            ensuref(x > 0 && x <= 1e9, "for task2 x_i must in [1, 1e9]");
            ensuref(y >= 0 && y < k, "y must in [0, k)");
        }

    } else if (c == 3) {

        ensuref(n >= 1 && n <= 100000, "for task3 n must in [1, 1e5]");
        ensuref(k >= 1 && k <= n, "k must in [1, n]");

        for (auto &[x, y] : a) {
            ensuref(x > 0 && x <= 1e6, "for task3 x_i must in [1, 1e6]");
            ensuref(y == 0, "y_i must equal to 0");
        }
    } else if (c == 4) {

        ensuref(n >= 1 && n <= 100000, "for task4 n must in [1, 1e5]");
        ensuref(k >= 1 && k <= n, "k must in [1, n]");

        for (auto &[x, y] : a) {
            ensuref(x > 0 && x <= 1e6, "for task4 x_i must in [1, 1e6]");
            ensuref(0 <= y && y < k, "y_i must in [0, k)");
        }
    } else {
        ensuref(n >= 1 && n <= 1000000, "for task5 n must in [1, 1e6]");
        ensuref(k >= 1 && k <= n, "k must in [1, n]");
        for (auto &[x, y] : a) {
            ensuref(x > 0 && x <= 1e9, "for task5 x_i must in [1, 1e9]");
            ensuref(0 <= y && y < k, "y_i must in [0, k)");
        }

    }
}

