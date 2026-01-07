#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

int bit[1000005];

void reset() { std::fill_n(bit, 1000005, 0); }
void modify(int p, int v) {
  for (p += 3; p < 1000005; p += p & (-p))
    bit[p] += v;
}
int query(int p) {
  int ans = 0;
  for (p += 3; p > 0; p -= p & (-p))
    ans += bit[p];
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i].first >> a[i].second;
  std::sort(begin(a), end(a));

  auto check = [&](int len) -> bool {
    int l = 0, r = 0;
    std::vector<int> opened(n);
    std::deque<int> closed_store;
    reset();
    for (int i = 0; i < n; ++i) {
      auto [x, s] = a[i];
      s++;
      int cur_left = x - len, cur_right = x + len;
      while (r < n && a[r].first <= cur_right) {
        closed_store.push_back(r);
        r++;
      }
      while (l < n && a[l].first < cur_left) {
        if (!closed_store.empty() && closed_store.front() == l)
          closed_store.pop_front();
        l++;
      }
      int cnt = query(r - 1) - query(l - 1);
      while (cnt < s) {
        if (closed_store.empty())
          return false;
        cnt++;
        opened[closed_store.back()] = 1;
        modify(closed_store.back(), 1);
        closed_store.pop_back();
      }
    }
    return std::accumulate(begin(opened), end(opened), 0) <= k;
  };

  int l = -1, r = 1 << 30;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  std::cout << r << "\n";
}