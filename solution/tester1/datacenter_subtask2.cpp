#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Dsu {
  int rt[100005], sz[100005];
  std::vector<int> vec;
  Dsu() { std::iota(rt, rt + 100005, 0); }
  int find_root(int v) {
    if (rt[v] == v)
      return v;
    return rt[v] = find_root(rt[v]);
  }
  bool union_root(int u, int v) {
    u = find_root(u);
    v = find_root(v);
    if (u == v)
      return false;
    if (sz[u] > sz[v])
      std::swap(u, v);
    rt[u] = v;
    sz[v] += sz[u];
    vec.push_back(u);
    return true;
  }
  void reset() {
    for (int v : vec) {
      rt[v] = v;
      sz[v] = 1;
    }
    vec.clear();
  }
} dsu;

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
} ed[300005];

std::vector<int> add[300005];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, d;
  std::cin >> n >> m >> d;
  for (int i = 0; i < m; ++i) {
    std::cin >> ed[i].u >> ed[i].v >> ed[i].w >> ed[i].l >> ed[i].r;
  }
  std::sort(ed, ed + m);
  for (int i = 0; i < m; ++i) {
    add[ed[i].l].push_back(i);
  }
  std::vector<int> tree;
  for (int i = 0; i < d; ++i) {
    tree.insert(end(tree), begin(add[i]), end(add[i]));
    sort(begin(tree), end(tree));
    dsu.reset();
    long long tot_cost = 0;
    std::vector<int> nxt;
    for (int id : tree) {
      if (dsu.union_root(ed[id].u, ed[id].v)) {
        tot_cost += ed[id].w;
        nxt.push_back(id);
      }
    }
    std::cout << ((int)nxt.size() == n - 1 ? tot_cost : -1)
              << " \n"[i + 1 == d];
    tree = nxt;
  }
}