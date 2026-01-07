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
#define uni(c) c.resize(distance(c.begin(), unique(c.begin(), c.end())))
#define unisort(c) sort(c.begin(), c.end()), uni(c)
const int N = 1e5 + 5;
const int K = 21;
const int C = 1e9;
const int INF = (1 << 30);

int l[N], r[N];
ll dp[K][N];

vector<int> ls;

pii st[N << 3];
int tag[N << 3];
pii add(pii a, pii b) {
  if (a.F != b.F)
    return min(a, b);
  else
    return pii(a.F, a.S + b.S);
}
void build(int l, int r, int id) {
  tag[id] = 0;
  if (l == r)
    st[id] = {0, ls[l + 1] - ls[l]};
  else {
    int mid = (l + r) >> 1;
    build(l, mid, id << 1);
    build(mid + 1, r, id << 1 | 1);
    st[id] = add(st[id << 1], st[id << 1 | 1]);
  }
}
void givetag(int x, int id) {
  tag[id] += x;
  st[id].F += x;
}
void tagdown(int id) {
  if (tag[id] == 0)
    return;
  givetag(tag[id], id << 1);
  givetag(tag[id], id << 1 | 1);
  tag[id] = 0;
}
void upd(int l, int r, int ql, int qr, int x, int id) {
  if (ql <= l && r <= qr)
    givetag(x, id);
  else {
    tagdown(id);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      upd(l, mid, ql, qr, x, id << 1);
    if (qr > mid)
      upd(mid + 1, r, ql, qr, x, id << 1 | 1);
    st[id] = add(st[id << 1], st[id << 1 | 1]);
  }
}
pii qry(int l, int r, int ql, int qr, int id) {
  if (ql <= l && r <= qr)
    return st[id];
  else {
    tagdown(id);
    int mid = (l + r) / 2;
    pii res = pii(INF, 0);
    if (ql <= mid)
      res = add(res, qry(l, mid, ql, qr, id << 1));
    if (qr > mid)
      res = add(res, qry(mid + 1, r, ql, qr, id << 1 | 1));
    return res;
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  rep1(i, n) {
    cin >> l[i] >> r[i];
    ls.pb(l[i]);
    ls.pb(r[i] + 1);
  }
  unisort(ls);
  ll all = ls.back() - ls[0];
  rep1(i, n) {
    l[i] = lower_bound(ls.begin(), ls.end(), l[i]) - ls.begin();
    r[i] = lower_bound(ls.begin(), ls.end(), r[i] + 1) - ls.begin() - 1;
  }

  int sz = ls.size();
  const int B = 10;
  rep1(i, k) {
    build(0, sz - 2, 1);
    int cur = 1;
    auto getw = [&]() {
      ll w = (st[1].F == 0 ? all - st[1].S : all) + dp[i - 1][cur - 1];
      return w;
    };
    rep1(j, n) {
      upd(0, sz - 2, l[j], r[j], 1, 1);
      dp[i][j] = getw();
      int best = cur;
      rep(t, B) {
        if (cur >= j)
          break;
        ll w = getw();
        if (w > dp[i][j]) {
          dp[i][j] = w;
          best = cur;
        }
        upd(0, sz - 2, l[cur], r[cur], -1, 1);
        cur++;
      }
      int tmp = j;
      vector<pii> v;
      rep(t, B) {
        if (tmp <= 0)
          break;
        vector<pii> nxt;
        int L = l[tmp], R = r[tmp];
        int tot = 0;
        bool done = 0;
        for (auto [x, y] : v) {
          if (y < L) {
            nxt.pb({x, y});
            tot += ls[y + 1] - ls[x];
          } else if (x > R) {
            if (!done) {
              nxt.pb({L, R});
              done = 1;
              tot += ls[R + 1] - ls[L];
            }
            nxt.pb({x, y});
            tot += ls[y + 1] - ls[x];
          } else {
            L = min(L, x);
            R = max(R, y);
          }
        }
        if (!done) {
          nxt.pb({L, R});
          tot += ls[R + 1] - ls[L];
        }
        ll w = tot + dp[i - 1][tmp - 1];
        if (w > dp[i][j]) {
          dp[i][j] = w;
          best = tmp;
        }
        v = nxt;
        tmp--;
      }
      while (cur < best) {
        upd(0, sz - 2, l[cur], r[cur], -1, 1);
        cur++;
      }
      while (best < cur) {
        cur--;
        upd(0, sz - 2, l[cur], r[cur], 1, 1);
      }
    }
  }

  rep1(i, k) { cout << dp[i][n] << " \n"[i == k]; }
}
