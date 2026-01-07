#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 2000000000;
int rand_int(int lb, int ub) {
    return rnd.next(lb, ub);
}
class GenGraph {
   public:
    GenGraph(int n, int m, int g, int B, int b, int w_min, int w_max,
             bool can_reach)
        : n(n),
          m(m),
          B(B),
          g(g),
          b(b),
          w_min(w_min),
          w_max(w_max),
          can_reach(can_reach) {
        st = rand_int(1, n);
        do {
            ed = rand_int(1, n);
        } while (st == ed);

        mp = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));
        v = vector<vector<pair<int, int>>>(n + 1);
        id = vector<int>(n);
        dist = vector<long long>(n + 1, 0);
        cap = vector<int>(n + 1, 0);
        reachable = vector<bool>(n + 1, true);
    }
    void generate(int path_len) {
        // construct a path from st to ed
        for (int i = 0; i < n; i++) id[i] = i + 1;
        shuffle(id.begin(), id.end());
        for (int i = 0; i < n; i++)
            if (id[i] == st) {
                swap(id[0], id[i]);
                break;
            }
        for (int i = 0; i < n; i++)
            if (id[i] == ed) {
                swap(id[path_len - 1], id[i]);
                break;
            }
        // randomly pick a must be used charger
        int ch = -1;
        if (g > 0) {
            ch = rand_int(b == B ? 1 : 0, path_len - 2);
        }
        // fill edge weight of this path
        cap[st] = b;
        for (int i = 0; i < path_len - 1; i++) {
            int from = id[i];
            int to = id[i + 1];
            int lb = -cap[from];
            int ub = B - cap[from] - 1;
            //   some edges, except the one before ch, can exceed B
            if (i != ch - 1 && rand_int(0, 10) == 0) {
                ub += B / 10;
            }
            if (i == ch) {
                lb = -B;
                ub = -cap[from] - 1;
                charges.push_back(from);
            } else {
                lb = max(lb, w_min);
            }
            ub = min(ub, w_max);
            assert(lb <= ub);
            int w = rand_int(lb, ub);
            if (!can_reach && (rand_int(0, 5) == 0 || i == path_len / 2)) {
                w = -rand_int(cap[from], B);
            }
            if (i == ch) cap[from] = rand_int(-w, B);
            cap[to] = min(cap[from] + w, B);
            if (!can_reach) cap[to] = max(cap[to], 0);
            assert(!can_reach || (cap[to] >= 0 && cap[to] <= B));
            add_edge(from, to, w);
            dist[to] = dist[from] + w;
        }
        if (ch != -1) {
            for (int i = ch + 1; i < path_len; i++) {
                reachable[id[i]] = false;
            }
        }
        // fill tree
        for (int i = path_len; i < n; i++) {
            int from = id[rand_int(0, i - 1)];
            int to = id[i];
            int lb = -cap[from];
            int ub = B - cap[from];
            if (rand_int(0, 1) == 0) {
                ub += B / 10;
            }
            lb = max(lb, w_min);
            ub = min(ub, w_max);
            assert(lb <= ub);
            int w = rand_int(lb, ub);
            if (!can_reach && rand_int(0, 5) == 0) {
                w = -rand_int(cap[from], B);
            }
            cap[to] = min(cap[from] + w, B);
            if (!can_reach) cap[to] = max(cap[to], 0);
            assert(!can_reach || (cap[to] >= 0 && cap[to] <= B));
            add_edge(from, to, w);
            dist[to] = dist[from] + w;
        }
        //  add remaining edge
        for (int j = n - 1; j < m; j++) {
            int from, to, lb;
            do {
                from = id[rand_int(0, n - 1)];
                lb = can_reach ? -cap[from] : -B;
                to = id[rand_int(0, n - 1)];
            } while (from == to || mp[from][to] != INF ||
                     ((dist[to] - dist[from]) < lb));
            int ub = min((long long)B / 2 - cap[from], dist[to] - dist[from]);
            ub = min(ub, w_max);
            if (reachable[from] && !reachable[to]) lb = -B;
            if (reachable[from] && !reachable[to]) ub = min(ub, -cap[from]);
            assert(lb <= ub);
            int w = rand_int(lb, ub);
            add_edge(from, to, w);
        }
        // fill remaining charges
        shuffle(id.begin(), id.end());
        for (int i = 0; i < n; i++) {
            if (charges.size() == g) break;
            if (id.at(i) != charges.at(0)) charges.push_back(id[i]);
        }
        assert(!have_positive_cycle());

        sort(charges.begin(), charges.end());
    }
    void print() {
        printf("%d %d %d %d\n", n, m, st, ed);
        printf("%d %d\n", B, b);
        for (int i = 1; i <= n; i++)
            for (const auto& e : v[i]) {
                printf("%d %d %d\n", i, e.first, e.second);
            }
        printf("%d", g);
        for (int i = 0; i < g; i++) {
            printf(" %d", charges[i]);
        }
        printf("\n");
    }

   private:
    void add_edge(int from, int to, int w) {
        v[from].emplace_back(to, w);
        mp[from][to] = w;
    };
    bool have_positive_cycle() {
        vector<int> d(n + 1, -INF);
        d[1] = 0;
        for (int t = 0; t < n - 1; t++) {
            for (int i = 1; i <= n; i++)
                for (const auto& e : v[i]) {
                    d[e.first] = max(d[e.first], d[i] + e.second);
                }
        }
        for (int i = 1; i <= n; i++)
            for (const auto& e : v[i]) {
                if (d[e.first] < d[i] + e.second) return true;
            }
        return false;
    }
    int n, m, st, ed, g, B, b;
    int w_min, w_max;
    // ed is reachable from st or not.
    bool can_reach;
    vector<vector<int>> mp;
    vector<vector<pair<int, int>>> v;
    vector<int> id;
    vector<int> charges;
    vector<long long int> dist;
    vector<int> cap;
    vector<bool> reachable;
};

string gen_filename(int c1, int c2) {
    char f[40];
    sprintf(f, "%d_%02d.in", c1, c2);
    return f;
}

void manual1(int g) {
    int r = 333;
    int n = r * 3 + 1;
    int m = 9000;
    int B = 20;
    int b = 15;
    g = g == 0 ? 0 : rand_int(1, n / 2);
    vector<int> id(n);
    for (int i = 0; i < n; i++) id[i] = i + 1;
    shuffle(id.begin(), id.end());
    printf("%d %d %d %d\n", n, m, id[0], id[n - 1]);
    printf("%d %d\n", B, b);
    for (int i = 0; i < r * 3; i += 3) {
        int x = rand_int(1, 5);
        printf("%d %d %d\n", id[i], id[i + 1], -10);
        printf("%d %d %d\n", id[i], id[i + 2], -6);
        printf("%d %d %d\n", id[i + 1], id[i + 2], 10 - x);
        printf("%d %d %d\n", id[i + 2], id[i + 3], x);
    }
    for (int i = r * 4; i < m; i++) {
        int x = rand_int(0, n - 1);
        int y = rand_int(1, n / 2);
        printf("%d %d %d\n", id[x], id[(x + y) % n], rand_int(-B, -11));
    }
    shuffle(id.begin(), id.end());
    printf("%d", g);
    for (int i = 0; i < g; i++) printf(" %d", id[i]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    assert(argc == 2);
    int case_num = atoi(argv[1]);
    registerGen(argc, argv, 1);

    int w_max = (case_num == 1 || case_num == 2) ? 0 : 1'000'000'000;

    int sub_case = 0;

    for (int B : {10'000, 1'000'000'000})
        for (int b : {B * 0.2, B * 0.7})
            for (int scale : {2, 4, 8}) {
                int n = rand_int(900, 1000);
                int m = rand_int(8000, 10000);

                int path_len = n / scale;
                bool can_reach = scale == 4 ? false : true;
                int w_min = (case_num == 1 || case_num == 2) ? (-b / path_len)
                                                             : -1'000'000'000;
                int g =
                    (case_num == 1 || case_num == 3) ? 0 : rand_int(100, n / 2);

                GenGraph graph(n, m, g, B, b, w_min, w_max, can_reach);
                graph.generate(path_len);

                assert(freopen(gen_filename(case_num, sub_case++).c_str(), "w",
                               stdout));
                graph.print();
                fclose(stdout);
            }
    if (case_num == 3 || case_num == 4) {
        int g = case_num == 3 ? 0 : -1;
        assert(
            freopen(gen_filename(case_num, sub_case++).c_str(), "w", stdout));
        manual1(g);
        fclose(stdout);
    }
    if (case_num == 2 || case_num == 4) {
        int n = 1000;
        int m = 10000;
        int g = 1000;
        int B = 1'000'000'000;
        int b = 500'000'000;
        int w_min = (case_num == 2) ? (-b / n) : -1'000'000'000;
        w_max = (case_num == 2) ? 0 : 100;

        GenGraph graph(n, m, g, B, b, w_min, w_max, true);
        graph.generate(n);

        assert(
            freopen(gen_filename(case_num, sub_case++).c_str(), "w", stdout));
        graph.print();
        fclose(stdout);
    }
    return 0;
}
