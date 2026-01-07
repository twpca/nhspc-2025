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

int l[N], r[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  rep1(i, n) cin >> l[i] >> r[i];

  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 1);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return l[i] < l[j]; });

  int ans = 0;
  int curl = 0, curr = -1;
  for (int i : ord) {
    if (l[i] <= curr)
      curr = max(curr, r[i]);
    else {
      ans += curr - curl + 1;
      curl = l[i];
      curr = r[i];
    }
  }
  ans += curr - curl + 1;
  cout << ans << "\n";
}
