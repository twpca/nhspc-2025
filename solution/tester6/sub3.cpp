// subtask3.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long LIM = (long long)1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int k;
    cin >> n >> k;
    vector<ll> p(k);
    for (int i = 0; i < k; ++i) cin >> p[i];

    vector<ll> v;
    v.reserve((size_t)k * (size_t)n);

    for (int i = 0; i < k; ++i) {
        for (ll m = 1; m <= n; ++m) {
            __int128 t = (__int128)p[i] * m;
            if (t > LIM) break;           
            v.push_back((ll)t);
        }
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    cout << v[n - 1] << "\n";
    return 0;
}

