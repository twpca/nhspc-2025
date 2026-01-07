#include <iostream>
#include <vector>

bool dp[500][500][500];
int ns[1001], ps[1001], qs[1001], rs[1001];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t;
  std::cin >> t;
  int n = 0;
  for (int i = 0; i < t; ++i) {
    std::cin >> ns[i] >> ps[i] >> qs[i] >> rs[i];
    n = std::max(n, ns[i]);
  }

  for (int i = 0; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      for (int k = j; k <= n; ++k) {
        for (int p = 0; p < i; ++p) {
          if (!dp[p][j][k])
            dp[i][j][k] = true;
        }
        for (int p = 0; p < j; ++p) {
          if (!dp[std::min(p, i)][p][k])
            dp[i][j][k] = true;
        }
        for (int p = 1; p < k; ++p) {
          if (!dp[std::min(p, i)][std::min(p, j)][p])
            dp[i][j][k] = true;
        }
      }
    }
  }

  for (int _ = 0; _ < t; ++_) {
    int x = ps[_], y = ps[_] + qs[_], z = ps[_] + qs[_] + rs[_];
    if (!dp[x][y][z]) {
      std::cout << 0 << "\n";
    } else {
      std::vector<std::pair<int, int>> ans;
      for (int i = 1; i < z; ++i) {
        if (!dp[std::min(i, x)][std::min(i, y)][i])
          ans.emplace_back(1, i + 1);
      }
      for (int i = 0; i < y; ++i) {
        if (!dp[std::min(i, x)][i][z])
          ans.emplace_back(2, i + 1);
      }
      for (int i = 0; i < x; ++i) {
        if (!dp[i][y][z])
          ans.emplace_back(3, i + 1);
      }

      std::cout << (int)ans.size() << "\n";
      for (int i = 0; i < (int)ans.size(); ++i) {
        std::cout << ans[i].first << " " << ans[i].second
                  << " \n"[i + 1 == (int)ans.size()];
      }
    }
  }
}