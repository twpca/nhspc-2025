#include <algorithm>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0), std::cin.tie(0);

  auto distance2 = [&](std::pair<int, int> u, std::pair<int, int> v) {
    return 1ll * (u.first - v.first) * (u.first - v.first) +
           1ll * (u.second - v.second) * (u.second - v.second);
  };

  auto distance = [&](std::pair<int, int> u, std::pair<int, int> v) {
    return sqrtl(distance2(u, v));
  };

  auto solve_closest_pair = [&](const std::vector<std::pair<int, int>> &points)
      -> std::pair<int, int> {
    std::vector<int> idx(points.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),
              [&](int a, int b) { return points[a] < points[b]; });
    double ans_dis = 9e18;
    std::pair<int, int> ans_pair(-1, -1);
    auto try_update = [&](int u, int v) {
      double d = distance(points[u], points[v]);
      if (d < ans_dis) {
        ans_dis = d;
        ans_pair = std::make_pair(u, v);
      }
    };
    auto divide_and_conquer = [&](auto self, int l, int r) {
      if (l == r)
        return;
      int mid = (l + r) >> 1;
      double midline = points[idx[mid]].first;
      self(self, l, mid);
      self(self, mid + 1, r);
      std::vector<int> merged;
      std::merge(idx.begin() + l, idx.begin() + mid + 1, idx.begin() + mid + 1,
                 idx.begin() + r + 1, std::back_inserter(merged),
                 [&](int a, int b) {
                   if (points[a].second != points[b].second)
                     return points[a].second < points[b].second;
                   return points[a].first < points[b].first;
                 });
      std::copy(merged.begin(), merged.end(), idx.begin() + l);
      std::deque<int> dq;
      for (int i = l; i <= r; ++i) {
        if (abs(points[idx[i]].first - midline) < ans_dis) {
          for (int p : dq)
            try_update(p, idx[i]);
          dq.push_back(idx[i]);
          if (int(dq.size()) > 5)
            dq.pop_front();
        }
      }
    };
    divide_and_conquer(divide_and_conquer, 0, int(points.size()) - 1);
    return ans_pair;
  };

  int n, k;
  std::cin >> n >> k;
  std::vector<std::pair<int, int>> points(n);
  for (auto &[x, y] : points)
    std::cin >> x >> y;
  double ans = 0;
  while (k--) {
    auto [l, r] = solve_closest_pair(points);
    if (l > r)
      std::swap(l, r);
    ans += distance(points[l], points[r]);
    points.erase(points.begin() + r);
    points.erase(points.begin() + l);
  }

  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}
