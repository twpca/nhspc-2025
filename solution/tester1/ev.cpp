#include <iostream>

struct edge {
  int u, v, w;
} ed[10001];

int dis1[1001], dis2[1001];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, s, t;
  std::cin >> n >> m >> s >> t;
  int B, b;
  std::cin >> B >> b;
  for (int i = 1; i <= m; ++i) {
    std::cin >> ed[i].u >> ed[i].v >> ed[i].w;
  }
  for (int i = 1; i <= n; ++i) {
    dis1[i] = (i == s ? b : -1);
    dis2[i] = (i == t ? 0 : B + 1);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (dis1[ed[j].u] >= 0) {
        dis1[ed[j].v] =
            std::max(dis1[ed[j].v], std::min(B, dis1[ed[j].u] + ed[j].w));
      }
      if (dis2[ed[j].v] <= B) {
        dis2[ed[j].u] =
            std::min(dis2[ed[j].u], std::max(0, dis2[ed[j].v] - ed[j].w));
      }
    }
  }
  if (dis1[t] >= 0) {
    std::cout << 0 << "\n";
  } else {
    int g;
    std::cin >> g;
    int ans = B + 1;
    for (int i = 0; i < g; ++i) {
      int x;
      std::cin >> x;
      if (dis1[x] >= 0 && dis2[x] <= B) {
        ans = std::min(ans, dis2[x] - dis1[x]);
      }
    }
    if (ans == B + 1)
      ans = -1;
    std::cout << ans << "\n";
  }
}