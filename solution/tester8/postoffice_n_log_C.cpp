#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define int long long

void Solve() {
    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    for (auto &[x, y] : a) cin >> x >> y;
    sort(a.begin(), a.end());

    auto check = [&](int m) -> bool {
        int cnt = 0;
        int cur = 0;

        int l = 0;
        int r = 0;
        vector<pii> aval;
        vector<int> vis(n);

        for (auto [x, s] : a) {
            while (r + 1 < n && abs(a[r + 1].first - x) <= m) r++;
            while (l < n && abs(a[l].first - x) > m) {
                cur -= vis[l];
                l++;
            }

            int p = r;
            while (cur <= s && p >= 0 && abs(a[p].first - x) <= m) {
                if ((int)aval.size() > 0 && aval.back().second == p) {
                    p = aval.back().first;
                    aval.pop_back();
                    continue;
                }
                if (vis[p])
                    return false;
                vis[p] = 1;
                cur += 1;
                cnt += 1;
                p--;
            }
            aval.emplace_back(p, r);
            if (cur <= s)
                return false;
        }

        return cnt <= k;
    };

    int l = -1, r = a.back().first - a[0].first;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m)) {
            r = m;
        } else {
            l = m;
        }
    }

    cout << r << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    //    cin >> t;
    while (t--) {
        Solve();
    }
}
