// subtask4_simpler.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll LIM = (ll)1e18;

ll lcm_ll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return a / std::gcd(a, b) * b;   
}

ll countValid(ll x, const vector<ll>& p) {
    int k = (int)p.size();
    ll ans = 0;

    for (int mask = 1; mask < (1 << k); ++mask) {
        ll L = 1;
        int bits = 0;
        for (int i = 0; i < k; ++i) {
            if (mask & (1 << i)) {
                ++bits;
                L = lcm_ll(L, p[i]);
                if (L > x) break;
            }
        }
        if (L > x) continue;
        ll cnt = x / L;
        if (bits & 1) ans += cnt;    
        else ans -= cnt;   
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int k;
    cin >> n >> k;
    vector<ll> p(k);
    for (int i = 0; i < k; ++i) cin >> p[i];

    ll L = 1, R = LIM;
    while (L < R) {
        ll mid = L + (R - L) / 2;
        if (countValid(mid, p) >= n) R = mid;
        else L = mid + 1;
    }
    cout << L << "\n";
    return 0;
}

