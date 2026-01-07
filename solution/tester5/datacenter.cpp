#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, n) for (int i = 1; i <= n; i++)
#define F first
#define S second
#define pb push_back

const int N = 1e5 + 5;
const int M = 3e5 + 5;
const int Q = 3e5 + 5;

int p[N], sz[N];
void init(int n) { rep(i, n) p[i] = i, sz[i] = 1; }
int fp(int x) { return x == p[x] ? x : p[x] = fp(p[x]); }
bool unite(int u, int v) {
  u = fp(u), v = fp(v);
  if (u == v)
    return false;
  if (sz[u] < sz[v])
    swap(u, v);
  sz[u] += sz[v];
  p[v] = u;
  return true;
}

int w[M], l[M], r[M];
bool used[M];
int new_id[N];
ll ans[Q];

void calc(int ql, int qr, int n, vector<array<int, 3>> &e,
          ll cur) // edges are {u,v,l,r,w} sorted by w
{
  init(n);
  int esz = e.size();
  rep(i, esz) used[i] = 0;
  for (auto [u, v, id] : e) {
    if (l[id] <= ql && qr <= r[id])
      continue;
    unite(u, v);
  }

  rep(i, esz) {
    auto [u, v, id] = e[i];
    if (l[id] <= ql && qr <= r[id]) {
      if (unite(u, v))
        cur += w[id], used[i] = 1;
    }
  }

  int cnt = 0;
  rep(i, n) if (fp(i) == i) cnt++;
  if (cnt > 1) {
    // can never be a tree
    for (int i = ql; i <= qr; i++)
      ans[i] = -1;
    return;
  }

  init(n);
  rep(i, esz) if (used[i]) {
    auto [u, v, id] = e[i];
    unite(u, v);
  }

  rep(i, n) new_id[i] = -1;
  int sz = 0;
  rep(i, n) if (fp(i) == i) {
    new_id[i] = sz;
    sz++;
  }

  if (ql == qr) {
    ans[ql] = cur;
  } else {
    int mid = (ql + qr) / 2;
    for (auto &[u, v, id] : e) {
      u = new_id[fp(u)];
      v = new_id[fp(v)];
    }
    vector<array<int, 3>> el, er;
    init(sz);
    rep(i, esz) {
      auto [u, v, id] = e[i];
      if (l[id] <= ql && qr <= r[id] && !unite(u, v))
        continue; // remove useless edges (not on reduced MST)

      if (l[id] <= mid)
        el.pb(e[i]);
      if (r[id] > mid)
        er.pb(e[i]);
    }
    calc(ql, mid, sz, el, cur);
    calc(mid + 1, qr, sz, er, cur);
  }
}

void solve() {
  int n, m, d;
  cin >> n >> m >> d;
  vector<array<int, 3>> e(m);
  rep(i, m) {
    int u, v;
    cin >> u >> v >> w[i] >> l[i] >> r[i];
    u--, v--, r[i]--;
    e[i] = {u, v, i};
  }
  sort(e.begin(), e.end(), [&](auto i, auto j) { return w[i[2]] < w[j[2]]; });
  calc(0, d - 1, n, e, 0);
  rep(i, d) cout << ans[i] << " \n"[i + 1 == d];
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  // cin>>t;
  while (t--) {
    solve();
  }
}
