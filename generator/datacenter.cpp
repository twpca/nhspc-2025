#include "jngen.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>

const int MAXN = 100000;
const int MAXM = 300000;
const int MAXD = 300000;
const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
    parseArgs(argc, argv);
    
    int n = getOpt("n");
    int m = getOpt("m");
    int d = getOpt("d");
    int c = getOpt("c");
    std::string treetype = getOpt("treetype");
    std::string edgetype = getOpt("edgetype");
    std::string weighttype = getOpt("weighttype");
    std::string timetype = getOpt("timetype");

    std::vector<std::pair<int, int>> eds;
    std::vector<int> weights;
    std::vector<std::pair<int, int>> rgs;

    if (treetype == "none") {

    } else {
        Tree tree;
        if (treetype == "random") {
            tree = Tree::random(n);
        } else if (treetype == "star") {
            tree = Tree::star(n);
        } else if (treetype == "line") {
            tree = Tree::bamboo(n);
        } else if (treetype == "prim1") {
            int treev = getOpt("treev");
            tree = Tree::randomPrim(n, treev);
        } else if (treetype == "prim2") {
            int treev = getOpt("treev");
            tree = Tree::randomPrim(n, -treev);
        } else if (treetype == "caterpillar") {
            int treelen = getOpt("treelen");
            tree = Tree::caterpillar(n, treelen);
        }
        for (auto [u, v] : tree.edges()) {
            eds.emplace_back(u + 1, v + 1);
        }
        int l = getOpt("treeweightl", 0);
        int r = getOpt("treeweightr", 100);
        for (int i = 0; i < n - 1; ++i) {
            weights.push_back(rnd.next(c / 100 * l + 1, std::min((c + 99) / 100 * r, c)));
            rgs.emplace_back(0, d);
        }
    }

    int k = (int)eds.size();

    if (edgetype == "random") {
        for (int i = k; i < m; ++i) {
            int u, v;
            do {
                u = rnd.next(1, n);
                v = rnd.next(1, n);
            } while (u == v);
            eds.emplace_back(u, v);
        }
    } else if (edgetype == "connected") {
        int block = getOpt("block", m);
        for (int i = 0; i < m; i += block) {
            auto g = Graph::random(n, block).connected().allowMulti().g();
            for (auto [u, v] : g.edges()) {
                eds.emplace_back(u + 1, v + 1);
            }
        }
    } else {
        assert(false);
    }

    if (weighttype == "random") {
        for (int i = k; i < m; ++i) {
            weights.push_back(rnd.next(1, c));
        }
    } else if (weighttype == "decreasing") {
        for (int i = k; i < m; ++i) {
            weights.push_back(rnd.next(1, c));
        }
        sort(begin(weights) + k, end(weights), std::greater());
    } else {
        assert(false);
    }

    if (timetype == "random") {
        int mxlen = getOpt("mxlen", d);
        auto f = [&](int len) { return 1ll * d * len - 1ll * len * (len - 1) / 2; };
        for (int i = k; i < m; ++i) {
            long long x = rnd.next(0ll, f(mxlen) - 1);
            int l = 0, r = mxlen;
            while (r - l > 1) {
                int mid = (l + r) / 2;
                if (f(mid) <= x) l = mid;
                else r = mid;
            }
            rgs.emplace_back(x - f(l), x - f(l) + r);
        }
    } else if (timetype == "distinct") {
        for (int i = k; i < m; ) {
            std::vector <int> ord(d + 1);
            std::iota(begin(ord), end(ord), 0);
            shuffle(begin(ord), end(ord));
            for (int j = 0; i < m && j + 1 < (int)ord.size(); j += 2) {
                int l = ord[j];
                int r = ord[j + 1];
                if (l > r) std::swap(l, r);
                rgs.emplace_back(l, r);
                i++;
            }
        }
    } else if (timetype == "end") {
        int distinct = getOpt("distinct", 0);
        for (int i = k; i < m; ++i) {
            if (distinct) rgs.emplace_back(i - k + (k > 0), d);
            else rgs.emplace_back(rnd.next(0, d - 1), d);
        }
    } else if (timetype == "intersect") {
        int block = getOpt("block", m);
        for (int i = 0; i < m; i += block) {
            int l = i, r = i + block;
            int t = rnd.next(l, r - 1);
            for (int j = i; j < i + block; ++j) {
                int rgt = rnd.next(t + 1, r);
                int lft = rnd.next(l, t);
                rgs.emplace_back(lft, rgt);
            }
        }
    } else {
        assert(false);
    }

    std::vector <int> ord(m);
    std::iota(begin(ord), end(ord), 0);
    shuffle(begin(ord), end(ord));
    std::cout << n << " " << m << " " << d << "\n";
    for (int i = 0; i < m; ++i) {
        int id = ord[i];
        std::cout << eds[id].first << " " << eds[id].second << " " << weights[id] << " " << rgs[id].first << " " << rgs[id].second << "\n";
    }
}
