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
    vector<vector<int>> ed(n);
    rep(i, n) rep(j, n) {
      char x;
      cin >> x;
      if (x == '1')
        ed[i].pb(j);
    }
    int ans = 0;
    // ll c=0;
    rep(i, n) {
      vector<int> dist(n, INF);
      queue<int> q;
      q.push(i);
      dist[i] = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : ed[u])
          if (dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
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
