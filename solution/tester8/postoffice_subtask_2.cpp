#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define int long long

void Ado_Is_The_Best() {
    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    for (auto &[x, y] : a) cin >> x >> y;

    sort(a.begin(), a.end());

    auto check = [&](int m) {
        vector<int> used;
        vector<bool> vis(n + 1);

        for (auto &[x, s] : a) {
            int cnt = 0;
            for (int &j : used)
                if (abs(x - j) <= m) cnt += 1;

            if (cnt > s)
                continue;

            for (int i = n - 1; i >= 0 && cnt <= s; i--) {
                if (vis[i] == 0 && abs(a[i].first - x) <= m) {
                    used.emplace_back(a[i].first);
                    cnt += 1;
                    vis[i] = 1;
                }
            }

            if (cnt <= s)
                return false;
        }

        return (int) used.size() <= k;
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
        Ado_Is_The_Best();
    }
}
