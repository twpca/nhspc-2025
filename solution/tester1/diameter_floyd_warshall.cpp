#include <iostream>

short dis[2001][2001];

int solve() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      std::cin >> c;
      dis[i][j] = i == j ? 0 : n;
      if (c == '1') {
        dis[i][j] = 1;
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dis[i][j] = std::min<short>(dis[i][j], dis[k][i] + dis[k][j]);
      }
    }
  }

  short ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ans = std::max(ans, dis[i][j]);
    }
  }

  if (ans >= n) {
    std::cout << "-1\n";
    exit(0);
  }

  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cout << solve() + solve() << "\n";
}