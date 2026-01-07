#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, n) for (int i = 1; i <= n; i++)
#define F first
#define S second
#define pb push_back

const int N = 1e5 + 5;
const int K = 21;
const int C = 1e5 + 5;
const ll INF = 1e18;

ll l[N], r[N], dp[K][N];

ll st[N << 2], tag[N << 2];
void build(int l, int r, int id) {
  tag[id] = st[id] = 0;
  if (l == r)
    return;
  else {
    int mid = (l + r) >> 1;
    build(l, mid, id << 1);
    build(mid + 1, r, id << 1 | 1);
  }
}
void givetag(ll x, int id) {
  tag[id] += x;
  st[id] += x;
}
void tagdown(int id) {
  if (tag[id] == 0)
    return;
  givetag(tag[id], id << 1);
  givetag(tag[id], id << 1 | 1);
  tag[id] = 0;
}
void upd(int l, int r, int ql, int qr, ll x, int id) {
  if (ql <= l && r <= qr)
    givetag(x, id);
  else {
    tagdown(id);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      upd(l, mid, ql, qr, x, id << 1);
    if (qr > mid)
      upd(mid + 1, r, ql, qr, x, id << 1 | 1);
    st[id] = max(st[id << 1], st[id << 1 | 1]);
  }
}
ll qry(int l, int r, int ql, int qr, int id) {
  if (ql <= l && r <= qr)
    return st[id];
  else {
    tagdown(id);
    int mid = (l + r) / 2;
    ll res = -INF;
    if (ql <= mid)
      res = max(res, qry(l, mid, ql, qr, id << 1));
    if (qr > mid)
      res = max(res, qry(mid + 1, r, ql, qr, id << 1 | 1));
    return res;
  }
}

int last[C];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  rep1(i, n) cin >> l[i] >> r[i];

  vector<vector<pll>> events(n + 1);
  rep1(i, n) {
    events[i].pb({last[l[i]] + 1, 1});
    last[l[i]] = i;
  }

  rep1(i, k) {
    build(1, n, 1);
    rep1(j, n) {
      upd(1, n, j, j, dp[i - 1][j - 1], 1);
      for (auto [L, x] : events[j])
        upd(1, n, L, j, x, 1);
      dp[i][j] = qry(1, n, 1, j, 1);
    }
    cout << dp[i][n] << " \n"[i == k];
  }
}
