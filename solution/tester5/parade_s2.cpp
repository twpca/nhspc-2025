#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, n) for (int i = 1; i <= n; i++)
#define F first
#define S second
#define pb push_back

const int N = 505;
const int K = 21;
const int C = 1e9;
const ll INF = 1e18;

ll l[N], r[N], dp[K][N];
ll w[N][N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  rep1(i, n) cin >> l[i] >> r[i];

  rep1(i, n) {
    vector<pll> cur;
    for (int j = i; j <= n; j++) {
      vector<pll> nxt;
      ll L = l[j], R = r[j];
      ll tot = 0;
      bool done = 0;
      for (auto [x, y] : cur) {
        if (y < L) {
          nxt.pb({x, y});
          tot += y - x + 1;
        } else if (x > R) {
          if (!done) {
            nxt.pb({L, R});
            done = 1;
            tot += R - L + 1;
          }
          nxt.pb({x, y});
          tot += y - x + 1;
        } else {
          L = min(L, x);
          R = max(R, y);
        }
      }
      if (!done) {
        nxt.pb({L, R});
        tot += R - L + 1;
      }
      rep(i, (int)nxt.size() - 1) assert(nxt[i].S < nxt[i + 1].F);
      w[i][j] = tot;
      cur = nxt;
    }
  }

  rep1(i, k) {
    rep1(j, n) {
      rep1(x, j) dp[i][j] = max(dp[i][j], dp[i - 1][x - 1] + w[x][j]);
    }
    cout << dp[i][n] << " \n"[i == k];
  }
}
