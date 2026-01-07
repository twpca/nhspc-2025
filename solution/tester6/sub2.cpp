#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int k;
    cin >> n >> k;
    vector<ll> p(k);
    for (int i = 0; i < k; ++i) cin >> p[i];

    vector<ll> v;

    if (k == 1) {
        cout << n * p[0] << "\n";
        return 0;
    }

    if (k == 2) {
        for (ll i = 1; i <= n; ++i) {
            v.push_back(p[0] * i);
            v.push_back(p[1] * i);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        cout << v[n - 1] << "\n";
        return 0;
    }

    return 0;
}
