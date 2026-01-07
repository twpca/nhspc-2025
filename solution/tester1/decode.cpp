#include <cassert>
#include <iostream>
#include <numeric>

int n, k;
long long p[6], val[1 << 6];

bool check(long long x) {
  long long cnt = 0;
  for (int s = 1; s < (1 << k); ++s) {
    if (__builtin_parity(s))
      cnt += x / val[s];
    else
      cnt -= x / val[s];
  }
  return cnt >= n;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  std::cin >> n >> k;
  for (int i = 0; i < k; ++i)
    std::cin >> p[i];
  __int128 tmp = 1;
  for (int i = 0; i < k; ++i) {
    tmp *= p[i];
    assert(tmp <= 1'000'000'000'000'000'000);
  }
  for (int s = 0; s < (1 << k); ++s) {
    val[s] = 1;
    for (int i = 0; i < k; ++i)
      if (s >> i & 1) {
        val[s] = std::lcm(val[s], p[i]);
      }
  }

  long long l = 0, r = 1ll << 60;
  while (r - l > 1) {
    long long mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  assert(r <= 1'000'000'000'000'000'000);
  std::cout << r << "\n";
}