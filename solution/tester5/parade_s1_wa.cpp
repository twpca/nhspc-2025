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
  int mn = 1 << 30, mx = -(1 << 30);
  rep1(i, n) {
    cin >> l[i] >> r[i];
    mn = min(mn, l[i]);
    mx = max(mx, r[i]);
  }
  cout << mx - mn + 1 << "\n";
}
