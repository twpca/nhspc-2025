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
        priority_queue<int, vector<int>, greater<int>> used;

        int r = 0;
        deque<int> aval;

        for (auto [x, s] : a) {
            // remove expired elements
            while ((int)used.size() > 0 && abs(x - used.top()) > m)
                used.pop();
            while ((int)aval.size() > 0 && abs(x - aval.front()) > m)
                aval.pop_front();

            // add new elements
            while (r < n && a[r].first < x - m) r++;
            while (r < n && abs(a[r].first - x) <= m)
                aval.emplace_back(a[r++].first);

            while ((int)aval.size() > 0 && (int)used.size() <= s) {
                used.emplace(aval.back());
                aval.pop_back();
                cnt += 1;
            }

            if ((int)used.size() <= s) return 0;
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
