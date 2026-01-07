#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

double start_time;

int solve(double running_time) {
  int n;
  std::cin >> n;
  int m = n;
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      std::cin >> c;
      if (c == '1') {
        g[i].push_back(j);
        m += i < j;
      }
    }
  }

  int ans = 0;
  std::vector<int> vis(n);
  auto upd = [&](int s) {
    vis[s] = 1;
    std::vector<int> dis(n, -1), que;
    que.push_back(s);
    dis[s] = 0;
    for (int i = 0; i < (int)que.size(); ++i) {
      int v = que[i];
      ans = std::max(ans, dis[v]);
      for (int u : g[v]) {
        if (dis[u] == -1) {
          dis[u] = dis[v] + 1;
          que.push_back(u);
        }
      }
    }
    if ((int)que.size() != n) {
      std::cout << -1 << "\n";
      exit(0);
    }
  };

  std::vector<int> ord(n);
  std::iota(begin(ord), end(ord), 0);
  std::sort(begin(ord), end(ord),
            [&](int i, int j) { return (int)g[i].size() < (int)g[j].size(); });

  for (int iter = 0;
       (clock() - start_time) / CLOCKS_PER_SEC < running_time && iter < n;
       ++iter) {
    int s = ord[iter];
    upd(s);
  }

  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  start_time = clock();
  std::cout << solve(0.49) + solve(0.98) << "\n";
}