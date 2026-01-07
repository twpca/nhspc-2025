#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int rt[100005];

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
  rt[u] = v;
  return true;
}

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
} ed[300005];

std::vector<int> add[300005], del[300005];

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
    del[ed[i].r].push_back(i);
  }

  std::set<int> cur;
  for (int i = 0; i < d; ++i) {
    for (int id : add[i])
      cur.insert(id);
    for (int id : del[i])
      cur.erase(id);
    for (int j = 1; j <= n; ++j)
      rt[j] = j;
    long long ans = 0;
    int cnt = 0;
    if ((int)cur.size() >= n - 1) {
      for (int id : cur) {
        if (union_root(ed[id].u, ed[id].v)) {
          ans += ed[id].w;
          cnt++;
        }
      }
    }
    if (cnt != n - 1)
      ans = -1;
    std::cout << ans << " \n"[i + 1 == d];
  }
}