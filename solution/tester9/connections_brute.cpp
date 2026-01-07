#include <bits/stdc++.h>

using ll = long long;
using std::pair;
using std::vector;
using pll = pair<ll, ll>;
using ld = double;
#define X first
#define Y second

const ld MAX = 1e12;
pll operator-(pll a, pll b) { return {a.X - b.X, a.Y - b.Y}; }
ll abs2(pll v) { return v.X * v.X + v.Y * v.Y; }
ld abs(pll v) { return sqrt(abs2(v)); }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;

  vector<pll> pts(n);
  for (int i = 0; i < n; i++)
    std::cin >> pts[i].X >> pts[i].Y;
  sort(pts.begin(), pts.end());

  vector<ld> dp(1 << n, MAX);
  vector<pair<int, int>> src(1 << n);
  dp[0] = 0;
  ld ans = MAX;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
      if (1 << i & mask)
        continue;
      for (int j = i + 1; j < n; j++) {
        if (1 << j & mask)
          continue;
        int nxt = mask | (1 << i) | (1 << j);
        ld cost = dp[mask] + abs(pts[i] - pts[j]);
        if (cost < dp[nxt]) {
          dp[nxt] = cost;
          src[nxt] = std::make_pair(i, j);
        }
      }
    }
    if (__builtin_popcount(mask) == 2 * k) {
      if (dp[mask] < ans) {
        ans = dp[mask];
      }
    }
  }
  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}
