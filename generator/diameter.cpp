#include "testlib.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>

const int MAXN = 2001;

bool g[MAXN][MAXN];

void clique(int l, int r) {
    for (int i = l; i < r; ++i) {
        for (int j = i + 1; j < r; ++j) {
            g[i][j] = g[j][i] = 1;
        }
    }
}
void edge(int l1, int r1, int l2, int r2) {
    for (int i = l1; i < r1; ++i) {
        for (int j = l2; j < r2; ++j) {
            g[i][j] = g[j][i] = 1;
        }
    }
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

    int ms = rnd.next(0, 1);
    for (int gg = 0; gg < 2; ++gg) {
        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                g[i][j] = 0;
            }
        }
        std::string type = opt<std::string>("type");
        std::string stype = opt<std::string>("stype", "none");

        if (stype != "none" && gg == ms) {
            type = "handmade1";
        }

        int n = opt<int>("n");
        if (type == "cycle") {
            int len = opt<int>("len");
            int ed = opt<int>("ed");
            int large_sub = opt<int>("large_sub", 0);
            std::string fix_type = opt<std::string>("fix_type", "none");
            int large = n - len - ed + 1;
            assert(n <= 2000);
            std::vector<int> vec(len, 1);
            vec[0] = large;
            vec.push_back(ed);

            if (fix_type == "clique") {
                std::vector<int> occ = rnd.partition(len, 2000 - n, 0);
                for (int i = 0; i < len; ++i) {
                    vec[i] += occ[i];
                }
                n = 2000;
            }

            std::vector<int> st(len + 2);
            for (int i = 1; i <= len + 1; ++i) {
                st[i] = st[i - 1] + vec[i - 1];
            }
            for (int i = 0; i <= len; ++i) {
                int l = st[i], r = st[i + 1];
                clique(l, r);
                if (i == 0 && large_sub) {
                    for (int iter = 0; iter < 100; ++iter) {
                        int u, v;
                        do {
                            u = rnd.next(l, r - 1);
                            v = rnd.next(l, r - 1);
                        } while (u == v);
                        g[u][v] = g[v][u] = 0;
                    }
                }
            }
            for (int i = 1; i < len; ++i) {
                edge(st[i - 1], st[i], st[i], st[i + 1]);
            }
            edge(st[0], st[1], st[len - 1], st[len]);
            int att;
            do {
                att = rnd.next(1, len - 1);
            } while (std::min(att, n - att) == len / 2);
            edge(st[att], st[att + 1], st[len], st[len + 1]);

            if (fix_type == "attach") {
                assert(len % 2 == 0);
                int opp = (att + len / 2) % len;
                clique(n, n + ed);
                edge(st[opp], st[opp + 1], n, n + ed);
                n += ed;

                int s = opt<int>("s");
                if (att > opp) std::swap(att, opp);
                while (n + s <= 2000) {
                    int to;
                    do {
                        to = rnd.next(0, len - 1);
                    } while (abs(to - att) <= 1 || abs(to - opp) <= 1 || (att <= to && to <= opp) || 
                             abs(to - att) == len - 1 || abs(to - opp) == len - 1);
                    edge(st[to], st[to + 1], n, n + s);
                    n += s;
                }
            }
        } else if (type == "path") {
            int len = opt<int>("len");
            int ed1 = opt<int>("ed1");
            int ed2 = opt<int>("ed2");
            int large_sub = opt<int>("large_sub", 0);
            std::string fix_type = opt<std::string>("fix_type", "none");
            int large = n - len - ed1 - ed2 + 3;
            assert(n <= 2000);
            std::vector<int> vec(len, 1);
            vec[0] = ed1;
            vec.back() = ed2;
            int pos = rnd.next(1, len - 2);
            vec[pos] = large;

            if (fix_type == "clique") {
                std::vector<int> occ = rnd.partition(len - 3, 2000 - n, 0);
                for (int i = 0; i < len - 3; ++i) {
                    vec[i + 1 + (i >= pos - 1)] += occ[i];
                }
                n = 2000;
            }

            std::vector<int> st(len + 1);
            for (int i = 1; i <= len; ++i) {
                st[i] = st[i - 1] + vec[i - 1];
            }
            for (int i = 0; i < len; ++i) {
                int l = st[i], r = st[i + 1];
                clique(l, r);
                if (i == pos && large_sub) {
                    for (int iter = 0; iter < 100; ++iter) {
                        int u, v;
                        do {
                            u = rnd.next(l, r - 1);
                            v = rnd.next(l, r - 1);
                        } while (u == v);
                        g[u][v] = g[v][u] = 0;
                    }
                }
            }
            for (int i = 1; i < len; ++i) {
                edge(st[i - 1], st[i], st[i], st[i + 1]);
            }

            if (fix_type == "attach") {
                int s = opt<int>("s");
                while (n + s <= 2000) {
                    int to;
                    do {
                        to = rnd.next(2, len - 3);
                    } while (vec[to] != 1);
                    clique(n, n + s);
                    edge(st[to], st[to + 1], n, n + s);
                    n += s;
                }
            }
        } else if (type == "handmade1") {
            for (int st = 0; st < 2000; st += 1000) {
                g[st][st + 1] = g[st + 1][st] = 1;
                g[st][st + 2] = g[st + 2][st] = 1;
                g[st + 999][st + 1] = g[st + 1][st + 999] = 1;
                g[st + 999][st + 2] = g[st + 2][st + 999] = 1;
                clique(st + 3, st + 999);
                edge(st, st + 1, st + 3, st + 999);
                edge(st + 999, st + 1000, st + 3, st + 999);
            }
            g[999][1999] = g[1999][999] = 1;
        } else if (type == "handmade2") {
            for (int i = 2; i < n; ++i) {
                int x = rnd.next(0, 1);
                g[i][0] = g[0][i] = x;
                g[i][1] = g[1][i] = !x;
                for (int j = i + 1; j < n; ++j) {
                    g[i][j] = g[j][i] = rnd.next(0, 1);
                }
            }
        } else if (type == "handmade3") {
            int ed = opt<int>("ed");
            clique(0, ed);
            edge(0, ed, ed, n);
        }

        std::vector <int> ord(n);
        iota(begin(ord), end(ord), 0);
        shuffle(begin(ord), end(ord));

        std::cout << n << "\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // if (g[i][j] && i < j) std::cerr << i << " " << j << std::endl;
                std::cout << g[ord[i]][ord[j]];
            }
            std::cout << "\n";
        }
    }
}