#include <algorithm>
#include <iostream>
#include <numeric>

struct Dsu {
  int rt[100005], sz[100005];
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
    return true;
  }
} dsu;

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
} ed[300005];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, d;
  std::cin >> n >> m >> d;
  for (int i = 0; i < m; ++i) {
    std::cin >> ed[i].u >> ed[i].v >> ed[i].w >> ed[i].l >> ed[i].r;
  }
  std::sort(ed, ed + m);
  int cc = n;
  long long tot_cost = 0;
  for (int i = 0; i < m; ++i) {
    if (dsu.union_root(ed[i].u, ed[i].v)) {
      tot_cost += ed[i].w;
      cc--;
    }
  }
  std::cout << (cc == 1 ? tot_cost : -1) << "\n";
}