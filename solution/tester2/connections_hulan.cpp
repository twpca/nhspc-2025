#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

constexpr int T = 10;
constexpr int S = 1000000;
constexpr int A = 10;

int main() {
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int n, k;
  std::cin >> n >> k;
  std::vector<std::pair<int, int>> points(n);
  for (auto &[x, y] : points)
    std::cin >> x >> y;

  auto distance2 = [&](int u, int v) {
    return 1ll * (points[u].first - points[v].first) *
               (points[u].first - points[v].first) +
           1ll * (points[u].second - points[v].second) *
               (points[u].second - points[v].second);
  };

  auto distance = [&](int u, int v) { return sqrtl(distance2(u, v)); };

  std::mt19937 rng(2025);
  std::vector<std::pair<int, int>> pairs;

  auto create_pairs = [&]() {
    int x = rng() % (A * 2 + 1) - A;
    int y = rng() % (A * 2 + 1) - A;

    auto measure = [&](int u) {
      return 1ll * points[u].first * x + 1ll * points[u].second * y;
    };

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), rng);
    std::sort(idx.begin(), idx.end(),
              [&](int u, int v) { return measure(u) < measure(v); });

    for (int i = 1; i < n; ++i)
      for (int j = i - 1; j >= 0 && j > i - S / n; --j)
        pairs.emplace_back(idx[i], idx[j]);
  };

  for (int _t = 0; _t < T; ++_t)
    create_pairs();
  std::sort(pairs.begin(), pairs.end(), [&](auto pa, auto pb) {
    auto ma = distance2(pa.first, pa.second);
    auto mb = distance2(pb.first, pb.second);
    if (ma != mb)
      return ma < mb;
    return pa < pb;
  });
  pairs.resize(std::unique(pairs.begin(), pairs.end()) - pairs.begin());
  double ans = 0;
  std::vector<int> vis(n);
  for (auto [u, v] : pairs) {
    if (vis[u] || vis[v])
      continue;
    vis[u] = vis[v] = 1;
    ans += distance(u, v);
    if (--k == 0)
      break;
  }
  std::cout << std::fixed << std::setprecision(15) << ans << "\n";
}
