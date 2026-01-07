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

std::vector<int> add[300005];

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
    add[ed[i].l].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    lct.new_node(-1);
  }
  for (int i = 1; i <= m; ++i) {
    lct.new_node(i);
  }
  int cc = n;
  long long tot_cost = 0;
  for (int i = 0; i < d; ++i) {
    for (int id : add[i]) {
      if (lct.find_root(ed[id].u) != lct.find_root(ed[id].v)) {
        lct.link(ed[id].u, id + n);
        lct.link(ed[id].v, id + n);
        cc--;
        tot_cost += ed[id].w;
      } else {
        int y = lct.query(ed[id].u, ed[id].v);
        if (id < y) {
          lct.cut(ed[y].u, y + n);
          lct.cut(ed[y].v, y + n);
          tot_cost -= ed[y].w;
          lct.link(ed[id].u, id + n);
          lct.link(ed[id].v, id + n);
          tot_cost += ed[id].w;
        }
      }
    }
    std::cout << (cc == 1 ? tot_cost : -1) << " \n"[i + 1 == d];
  }
}