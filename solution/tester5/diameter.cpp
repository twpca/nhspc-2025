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

const int N = 2000;
const int INF = 998244353;

void solve() {
  auto calc = [&]() {
    int n;
    cin >> n;
    vector<bitset<N>> ed(n);
    rep(i, n) rep(j, n) {
      char c;
      cin >> c;
      if (c == '1')
        ed[i][j] = 1;
    }
    int ans = 0;
    rep(i, n) {
      bitset<N> unvis;
      rep(j, n) unvis[j] = 1;
      vector<int> dist(n, INF);
      queue<int> q;
      q.push(i);
      dist[i] = 0;
      unvis[i] = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        auto tmp = ed[u] & unvis;
        for (int v = tmp._Find_first(); v < N; v = tmp._Find_next(v)) {
          dist[v] = dist[u] + 1;
          unvis[v] = 0;
          q.push(v);
        }
      }
      rep(j, n) ans = max(ans, dist[j]);
    }
    return ans;
  };
  int a = calc();
  int b = calc();
  if (a >= INF || b >= INF)
    cout << "-1\n";
  else
    cout << a + b << "\n";
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
