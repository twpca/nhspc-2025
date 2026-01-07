#include <iostream>
#include <map>

long long dp[100005];

namespace segment_tree {
long long val[100005 * 4], tag[100005 * 4];
void give_tag(int id, long long v) {
  tag[id] += v;
  val[id] += v;
}
void push(int id) {
  give_tag(id * 2, tag[id]);
  give_tag(id * 2 + 1, tag[id]);
  tag[id] = 0;
}
void pull(int id) { val[id] = std::max(val[id * 2], val[id * 2 + 1]); }
void build(int l, int r, int id) {
  tag[id] = 0;
  if (r - l > 1) {
    int m = (l + r) / 2;
    build(l, m, id * 2);
    build(m, r, id * 2 + 1);
    pull(id);
  } else {
    val[id] = dp[l];
  }
}
void add(int a, int b, long long v, int l, int r, int id) {
  if (a <= l && r <= b)
    give_tag(id, v);
  else {
    int m = (l + r) / 2;
    push(id);
    if (a < m)
      add(a, b, v, l, m, id * 2);
    if (m < b)
      add(a, b, v, m, r, id * 2 + 1);
    pull(id);
  }
}
long long query(int a, int b, int l, int r, int id) {
  if (a <= l && r <= b)
    return val[id];
  long long res = -1'000'000'000'000'000;
  int m = (l + r) / 2;
  push(id);
  if (a < m)
    res = std::max(res, query(a, b, l, m, id * 2));
  if (m < b)
    res = std::max(res, query(a, b, m, r, id * 2 + 1));
  return res;
}
} // namespace segment_tree

int range_left[100005], range_right[100005];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    std::cin >> range_left[i] >> range_right[i];
    --range_left[i];
  }

  for (int i = 1; i <= n; ++i)
    dp[i] = -1'000'000'000'000'000'000;
  for (int iter = 1; iter <= k; ++iter) {
    segment_tree::build(0, n, 1);
    std::map<std::pair<int, int>, int> mp;
    mp[std::make_pair(0, 1'000'000'000)] = 0;
    auto cut = [&](int p) {
      auto it = prev(mp.lower_bound(std::make_pair(p + 1, -1)));
      auto [l, r] = it->first;
      int mx = it->second;
      if (l < p && p < r) {
        mp.erase(it);
        mp[std::make_pair(l, p)] = mx;
        mp[std::make_pair(p, r)] = mx;
      }
    };
    for (int i = 1; i <= n; ++i) {
      cut(range_left[i]);
      cut(range_right[i]);
      while (true) {
        auto it = mp.lower_bound(std::make_pair(range_left[i], -1));
        auto [l, r] = it->first;
        int mx = it->second;
        if (it == mp.end() || l >= range_right[i])
          break;
        segment_tree::add(mx, i, r - l, 0, n, 1);
        mp.erase(it);
      }
      dp[i] = segment_tree::query(0, i, 0, n, 1);
      mp[std::make_pair(range_left[i], range_right[i])] = i;
    }
    std::cout << dp[n] << " \n"[iter == k];
  }
}