#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct RollbackDsu {
  int rt[100005], sz[100005];
  std::vector<std::pair<int, int>> vec;
  RollbackDsu() {
    std::iota(rt, rt + 100005, 0);
    std::fill(sz, sz + 100005, 1);
  }
  int find_root(int v) {
    if (rt[v] == v)
      return v;
    return find_root(rt[v]);
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
    vec.emplace_back(u, v);
    return true;
  }
  void rollback(int k) {
    while ((int)vec.size() > k) {
      auto [u, v] = vec.back();
      vec.pop_back();
      rt[u] = u;
      sz[v] -= sz[u];
    }
  }
} dsu;

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
};

std::vector<edge> ed[300005 * 4];

void add_edge(edge e, int l, int r, int id) {
  if (e.l <= l && r <= e.r) {
    ed[id].push_back(e);
  } else {
    int m = (l + r) / 2;
    if (e.l < m)
      add_edge(e, l, m, id * 2);
    if (m < e.r)
      add_edge(e, m, r, id * 2 + 1);
  }
}

int ans[300005];
void solve(int l, int r, int id, int cc) {
  int k = (int)dsu.vec.size(), old_cc = cc;
  for (edge i : ed[id]) {
    cc -= dsu.union_root(i.u, i.v);
  }
  if (r - l == 1)
    ans[l] = cc;
  else {
    int m = (l + r) / 2;
    solve(l, m, id * 2, cc);
    solve(m, r, id * 2 + 1, cc);
  }
  dsu.rollback(k);
  cc = old_cc;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, d;
  std::cin >> n >> m >> d;
  for (int i = 0; i < m; ++i) {
    edge e;
    std::cin >> e.u >> e.v >> e.w >> e.l >> e.r;
    add_edge(e, 0, d, 1);
  }
  solve(0, d, 1, n);
  for (int i = 0; i < d; ++i) {
    std::cout << (ans[i] == 1 ? n - 1 : -1) << " \n"[i + 1 == d];
  }
}