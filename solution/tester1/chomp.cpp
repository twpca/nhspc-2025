#include <algorithm>
#include <iostream>
#include <vector>

int dp[501][501], vis[501];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  for (int j = 1; j <= 500; ++j) {
    dp[0][j] = j == 1 ? 0 : -1;
  }
  for (int i = 1; i <= 500; ++i) {
    for (int j = i; j <= 500; ++j) {
      dp[i][j] = -1;
      int bound = i;
      for (int k = 0; k <= 500; ++k)
        vis[k] = 0;
      for (int k = 0; k < i; ++k) {
        if (dp[k][j] != -1) {
          vis[dp[k][j]] = 1;
          if (dp[k][j] == k)
            bound = std::min(bound, k);
        }
      }
      for (int k = 1; k < j; ++k) {
        if (dp[std::min(i, k)][k] != -1)
          vis[dp[std::min(i, k)][k]] = 1;
      }
      for (int k = 0; k <= bound; ++k) {
        if (!vis[k]) {
          dp[i][j] = k;
          break;
        }
      }
    }
  }

  int t;
  std::cin >> t;
  while (t-- > 0) {
    int n, p, q, r;
    std::cin >> n >> p >> q >> r;
    int x = p, y = p + q, z = p + q + r;
    if (dp[y][z] == x) {
      std::cout << 0 << "\n";
    } else {
      std::vector<std::pair<int, int>> ans;
      for (int i = 1; i < z; ++i) {
        if (dp[std::min(i, y)][i] == std::min(i, x))
          ans.emplace_back(1, i + 1);
      }
      for (int i = 0; i < y; ++i) {
        if (dp[i][z] == std::min(i, x))
          ans.emplace_back(2, i + 1);
      }
      for (int i = 0; i < x; ++i) {
        if (dp[y][z] == i)
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