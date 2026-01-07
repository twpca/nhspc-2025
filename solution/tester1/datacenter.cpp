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
} dsu1, dsu2;

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
};

long long ans[300005];
void dfs(int l, int r, std::vector<edge> ed, int cc, long long tot_cost) {
  std::vector<edge> tmp;
  for (edge i : ed) {
    if (i.r <= l || r <= i.l)
      continue;
    tmp.push_back(i);
  }
  ed = tmp;
  dsu1.reset();
  dsu2.reset();
  for (edge i : ed) {
    if (l < i.l || i.r < r) {
      dsu1.union_root(i.u, i.v);
    }
  }
  for (edge i : ed) {
    if (dsu1.union_root(i.u, i.v)) {
      dsu2.union_root(i.u, i.v);
      tot_cost += i.w;
      cc--;
    }
  }
  dsu1.reset();
  tmp.clear();
  for (edge i : ed) {
    i.u = dsu2.find_root(i.u);
    i.v = dsu2.find_root(i.v);
    if (l < i.l || i.r < r || dsu1.union_root(i.u, i.v))
      tmp.push_back(i);
  }

  if (r - l == 1) {
    ans[l] = cc == 1 ? tot_cost : -1;
  } else {
    dfs(l, (l + r) / 2, tmp, cc, tot_cost);
    dfs((l + r) / 2, r, tmp, cc, tot_cost);
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
  std::sort(begin(ed), end(ed));
  dfs(0, d, ed, n, 0);
  for (int i = 0; i < d; ++i) {
    std::cout << ans[i] << " \n"[i + 1 == d];
  }
}