#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct LCT {
  int ch[400005][2], pa[400005], rev[400005], _id;
  int mx[400005], w[400005];
  LCT() : _id(1) {}
  int new_node(int _w) {
    int x = _id++;
    ch[x][0] = ch[x][1] = pa[x] = rev[x] = 0;
    w[x] = _w;
    return x;
  }
  void pull(int v) {
    mx[v] = w[v];
    if (ch[v][0]) {
      mx[v] = std::max(mx[v], mx[ch[v][0]]);
    }
    if (ch[v][1]) {
      mx[v] = std::max(mx[v], mx[ch[v][1]]);
    }
  }
  void push(int v) {
    if (rev[v]) {
      reverse(ch[v][0]);
      reverse(ch[v][1]);
    }
    rev[v] = false;
  }
  void reverse(int v) {
    std::swap(ch[v][0], ch[v][1]);
    rev[v] ^= 1;
  }
  bool isrt(int v) {
    if (!pa[v])
      return true;
    return ch[pa[v]][0] != v && ch[pa[v]][1] != v;
  }
  void rotate(int v) {
    int p = pa[v], x = ch[p][1] == v;
    int c = ch[v][!x], gp = pa[p];
    if (ch[gp][0] == p)
      ch[gp][0] = v;
    else if (ch[gp][1] == p)
      ch[gp][1] = v;
    pa[v] = gp;
    ch[v][!x] = p;
    pa[p] = v;
    ch[p][x] = c;
    pa[c] = p;
    pull(p);
    pull(v);
  }
  void splay(int v) {
    std::vector<int> anc;
    anc.push_back(v);
    while (!isrt(anc.back())) {
      anc.push_back(pa[anc.back()]);
    }
    while (!anc.empty()) {
      push(anc.back());
      anc.pop_back();
    }
    while (!isrt(v)) {
      int p = pa[v];
      if (!isrt(p)) {
        if ((ch[p][1] == v) ^ (ch[pa[p]][1] == p)) {
          rotate(v);
        } else {
          rotate(p);
        }
      }
      rotate(v);
    }
  }
  void access(int v) {
    int lst = 0;
    while (v) {
      splay(v);
      ch[v][1] = lst;
      pull(v);
      lst = v;
      v = pa[v];
    }
  }
  void makert(int v) {
    access(v);
    splay(v);
    reverse(v);
  }
  void link(int u, int v) {
    makert(u);
    makert(v);
    pa[u] = v;
    pull(v);
  }
  void cut(int u, int v) {
    makert(u);
    access(v);
    splay(u);
    ch[u][1] = pa[v] = 0;
    pull(u);
  }
  int query(int u, int v) {
    makert(u);
    access(v);
    splay(u);
    return mx[u];
  }
  int find_root(int v) {
    access(v);
    splay(v);
    while (ch[v][0]) {
      push(v);
      v = ch[v][0];
    }
    splay(v);
    return v;
  }
} lct;

struct edge {
  int u, v, w, l, r;
  bool operator<(const edge &o) { return w < o.w; }
} ed[300005];

std::vector<int> add[300005 * 4];

void add_edge(int eid, int l, int r, int id) {
  if (ed[eid].l <= l && r <= ed[eid].r) {
    add[id].push_back(eid);
  } else {
    int m = (l + r) / 2;
    if (ed[eid].l < m)
      add_edge(eid, l, m, id * 2);
    if (m < ed[eid].r)
      add_edge(eid, m, r, id * 2 + 1);
  }
}

long long ans[300005];
void solve(int l, int r, int id, int cc, long long tot_cost, int n) {
  std::vector<int> cur_add, cur_del;
  for (int eid : add[id]) {
    if (lct.find_root(ed[eid].u) != lct.find_root(ed[eid].v)) {
      lct.link(ed[eid].u, eid + n);
      lct.link(ed[eid].v, eid + n);
      cc--;
      tot_cost += ed[eid].w;
      cur_add.push_back(eid);
    } else {
      int y = lct.query(ed[eid].u, ed[eid].v);
      if (eid < y) {
        lct.cut(ed[y].u, y + n);
        lct.cut(ed[y].v, y + n);
        tot_cost -= ed[y].w;
        cur_del.push_back(y);
        lct.link(ed[eid].u, eid + n);
        lct.link(ed[eid].v, eid + n);
        tot_cost += ed[eid].w;
        cur_add.push_back(eid);
      }
    }
  }
  if (r - l == 1)
    ans[l] = cc == 1 ? tot_cost : -1;
  else {
    int m = (l + r) / 2;
    solve(l, m, id * 2, cc, tot_cost, n);
    solve(m, r, id * 2 + 1, cc, tot_cost, n);
  }
  for (int eid : cur_add) {
    lct.cut(ed[eid].u, eid + n);
    lct.cut(ed[eid].v, eid + n);
  }
  for (int eid : cur_del) {
    lct.link(ed[eid].u, eid + n);
    lct.link(ed[eid].v, eid + n);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, d;
  std::cin >> n >> m >> d;
  for (int i = 1; i <= m; ++i) {
    std::cin >> ed[i].u >> ed[i].v >> ed[i].w >> ed[i].l >> ed[i].r;
  }
  std::sort(ed + 1, ed + m + 1);
  for (int i = 1; i <= m; ++i) {
    add_edge(i, 0, d, 1);
  }
  for (int i = 1; i <= n; ++i) {
    lct.new_node(-1);
  }
  for (int i = 1; i <= m; ++i) {
    lct.new_node(i);
  }
  solve(0, d, 1, n, 0, n);
  for (int i = 0; i < d; ++i) {
    std::cout << ans[i] << " \n"[i + 1 == d];
  }
}