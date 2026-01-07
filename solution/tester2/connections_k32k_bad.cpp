#include <algorithm>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

const double INF = 9e18;

int main() {
  std::ios::sync_with_stdio(0), std::cin.tie(0);

  auto distance2 = [&](std::pair<int, int> u, std::pair<int, int> v) {
    return 1ll * (u.first - v.first) * (u.first - v.first) +
           1ll * (u.second - v.second) * (u.second - v.second);
  };

  auto distance = [&](std::pair<int, int> u, std::pair<int, int> v) {
    return sqrtl(distance2(u, v));
  };

  std::vector<std::pair<int, int>> points;

  auto solve_closest_pair =
      [&](const std::vector<int> &current) -> std::pair<int, int> {
    std::vector<int> idx(current);
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
    divide_and_conquer(divide_and_conquer, 0, int(idx.size()) - 1);
    return ans_pair;
  };

  std::vector<std::pair<int, int>> matching;
  auto alter = [&]() {
    int k = matching.size();
    std::vector<double> dis(k);
    std::vector<int> pts, current, vis(points.size());
    for (int i = 0; i < k; ++i) {
      pts.push_back(matching[i].first);
      vis[matching[i].first] = 1;
      pts.push_back(matching[i].second);
      vis[matching[i].second] = 1;
      dis[i] = distance(points[pts[i * 2]], points[pts[i * 2 + 1]]);
    }
    for (int i = 0; i < int(points.size()); ++i)
      if (!vis[i])
        current.push_back(i);
    std::vector<std::pair<int, int>> best(2 * k, std::make_pair(-1, -1));
    auto try_update = [&](int u, int p, std::pair<int, int> &best_pair) {
      if (best_pair.first == -1 ||
          distance2(points[u], points[p]) <
              distance2(points[u], points[best_pair.first]))
        best_pair.second = best_pair.first, best_pair.first = p;
      else if (best_pair.second == -1 ||
               distance2(points[u], points[p]) <
                   distance2(points[u], points[best_pair.second]))
        best_pair.second = p;
    };
    std::vector<std::pair<int, int>> next_matching(matching);
    next_matching.push_back(solve_closest_pair(current));
    double best_increase = distance(points[next_matching.back().first],
                                    points[next_matching.back().second]);
    for (int i = 0; i < k; ++i) {
      auto [u, v] = matching[i];
      for (int p : current) {
        try_update(u, p, best[i * 2]);
        try_update(v, p, best[i * 2 + 1]);
      }
    }
    for (int i = 0; i < 2 * k; ++i) {
      std::vector<std::vector<double>> dp(1 << k,
                                          std::vector<double>(2 * k, INF));
      std::vector<std::vector<int>> pi(1 << k, std::vector<int>(2 * k, -1));
      dp[1 << (i / 2)][i ^ 1] = -dis[i / 2];
      for (int mask = (1 << (i / 2)); mask < (1 << k); ++mask) {
        for (int j = 0; j < 2 * k; ++j) {
          if (dp[mask][j] == INF)
            continue;
          for (int p = 0; p < k; ++p)
            if (!(mask >> p & 1)) {
              double val = dp[mask][j] - dis[p];
              if (dp[mask | (1 << p)][p * 2] >
                  val + distance(points[pts[j]], points[pts[p * 2 + 1]])) {
                dp[mask | (1 << p)][p * 2] =
                    val + distance(points[pts[j]], points[pts[p * 2 + 1]]);
                pi[mask | (1 << p)][p * 2] = j;
              }
              if (dp[mask | (1 << p)][p * 2 + 1] >
                  val + distance(points[pts[j]], points[pts[p * 2]])) {
                dp[mask | (1 << p)][p * 2 + 1] =
                    val + distance(points[pts[j]], points[pts[p * 2]]);
                pi[mask | (1 << p)][p * 2 + 1] = j;
              }
            }
          int lft = best[i].first;
          int rgt = best[j].first;
          if (lft == rgt) {
            if (distance(points[pts[i]], points[lft]) +
                    distance(points[pts[j]], points[best[j].second]) <
                distance(points[pts[i]], points[best[i].second]) +
                    distance(points[pts[j]], points[rgt])) {
              rgt = best[j].second;
            } else {
              lft = best[i].second;
            }
          }
          double delta = distance(points[pts[i]], points[lft]) +
                         distance(points[pts[j]], points[rgt]);
          if (dp[mask][j] + delta < best_increase) {
            best_increase = dp[mask][j] + delta;
            next_matching.clear();
            next_matching.emplace_back(rgt, pts[j]);
            for (int mm = mask, jj = j; pi[mm][jj] != -1;
                 std::tie(mm, jj) =
                     std::make_pair(mm ^ (1 << (jj / 2)), pi[mm][jj])) {
              next_matching.emplace_back(pts[jj ^ 1], pts[pi[mm][jj]]);
            }
            next_matching.emplace_back(pts[i], lft);
          }
        }
      }
    }
    matching.swap(next_matching);
  };

  int n, k;
  std::cin >> n >> k;
  points.resize(n);
  for (auto &[x, y] : points)
    std::cin >> x >> y;
  while (k--) {
    alter();
  }
  double ans = 0;
  for (auto [u, v] : matching) {
    ans += distance(points[u], points[v]);
    // std::cerr << "(" << u << ", " << v << ")\n";
  }

  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}
