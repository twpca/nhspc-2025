#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int n, k;
  std::cin >> n >> k;
  std::vector<std::pair<int, int>> points(n);
  for (auto &[x, y] : points)
    std::cin >> x >> y;

  auto distance = [&](int u, int v) -> double {
    return sqrtl(1ll * (points[u].first - points[v].first) *
                     (points[u].first - points[v].first) +
                 1ll * (points[u].second - points[v].second) *
                     (points[u].second - points[v].second));
  };

  auto chmin = [&](auto &x, auto v) { x = std::min(x, v); };

  double ans = 9e18;
  std::vector<double> dp(1 << n, ans);
  dp[0] = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    int popcount = __builtin_popcount(mask);
    if (popcount > k * 2)
      continue;
    if (popcount == k * 2) {
      chmin(ans, dp[mask]);
      continue;
    }
    for (int i = 0; i < n; ++i)
      if ((mask >> i & 1) == 0)
        for (int j = i + 1; j < n; ++j)
          if ((mask >> j & 1) == 0)
            chmin(dp[mask | (1 << i) | (1 << j)], dp[mask] + distance(i, j));
  }

  std::cout << std::fixed << std::setprecision(15) << ans << "\n";
}
