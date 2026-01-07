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
};

long long ans[300005];
void dfs(int l, int r, std::vector<edge> ed, int cc) {
  std::vector<edge> tmp;
  for (edge i : ed) {
    if (i.r <= l || r <= i.l)
      continue;
    tmp.push_back(i);
  }
  ed = tmp;
  tmp.clear();
  dsu.reset();
  for (edge i : ed) {
    if (i.l <= l && r <= i.r) {
      if (dsu.union_root(i.u, i.v)) {
        cc--;
      }
    } else {
      tmp.push_back(i);
    }
  }
  for (edge &i : tmp) {
    i.u = dsu.find_root(i.u);
    i.v = dsu.find_root(i.v);
  }

  if (r - l == 1) {
    ans[l] = cc;
  } else {
    dfs(l, (l + r) / 2, tmp, cc);
    dfs((l + r) / 2, r, tmp, cc);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, d;
  std::cin >> n >> m >> d;
  std::vector<edge> ed(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> ed[i].u >> ed[i].v >> ed[i].w >> ed[i].l >> ed[i].r;
  }
  dfs(0, d, ed, n);
  for (int i = 0; i < d; ++i) {
    std::cout << (ans[i] == 1 ? n - 1 : -1) << " \n"[i + 1 == d];
  }
}