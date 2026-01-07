#include <bits/stdc++.h>

#include "testlib.h"
using namespace std;

constexpr int MIN_N = 1;
constexpr int MAX_N = 1000;
constexpr int MIN_M = 1;
constexpr int MAX_M = 10000;
constexpr int MIN_Q = 0;
constexpr int MAX_Q[5] = {MAX_N, 0, MAX_N, 0, MAX_N};
constexpr int MIN_B = 1;
constexpr int MAX_B = 1000000000;
constexpr int MIN_W = -1000000000;
constexpr int MAX_W[5] = {1000000000, 0, 0, 1000000000, 1000000000};
constexpr int INF = 2000000000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = atoi(argv[2]);
    int n = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int m = inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
    int s = inf.readInt(1, n);
    inf.readSpace();
    int t = inf.readInt(1, n);
    inf.readChar('\n');

    int B = inf.readInt(MIN_B, MAX_B);
    inf.readSpace();
    int b = inf.readInt(0, B);
    inf.readChar('\n');

    vector<tuple<int, int, int>> edges(m);

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n);
        inf.readSpace();
        int v = inf.readInt(1, n);
        inf.readSpace();
        ensuref(u != v, "u(%d) and v(%d) are same", u, v);
        int w = inf.readInt(MIN_W, MAX_W[c]);
        inf.readChar('\n');
        edges[i] = make_tuple(u, v, w);
    }

    auto has_positive_cycle = [&]() {
        vector<int> dist(n + 1, -INF);
        dist[1] = 0;
        for (int i = 0; i < n - 1; i++)
            for (const auto& [u, v, w] : edges) {
                dist[v] = max(dist[v], dist[u] + w);
            }
        for (const auto& [u, v, w] : edges) {
            if (dist[v] < dist[u] + w) return true;
        }
        return false;
    };

    ensuref(!has_positive_cycle(), "graph contains positive cycle");

    int q = inf.readInt(MIN_Q, min(MAX_Q[c], n));

    for (int i = 0; i < q; i++) {
        inf.readSpace();
        int g = inf.readInt(1, n);
    }
    inf.readChar('\n');
    inf.readEof();

    return 0;
}
