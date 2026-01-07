#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::string s;
  std::cin >> n >> s;
  int ans = n, cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(')
      cnt++;
    else if (cnt)
      ans -= 2, cnt--;
  }
  std::cout << ans << "\n";
}