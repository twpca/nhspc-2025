#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define int long long

void Ado_Is_The_Best() {
    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    for (auto &[x, y] : a)
        cin >> x >> y;

    sort(a.begin(), a.end());

    int ans = 1e9;

    for (auto &[x, y] : a) {
        int tmp = 0;
        for (auto &[xx, yy] : a) {
            tmp = max(tmp, (ll)abs(xx - x)); 
        }
        ans = min(ans, tmp);
    }

    cout << ans << "\n";


}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
//    cin >> t;
    while (t --) {
        Ado_Is_The_Best();

    }

}
