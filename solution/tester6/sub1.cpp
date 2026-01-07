// subtask1.cpp
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

    ll cnt = 0;
    for (ll x = 1; x <= 1000000; ++x) { 
        bool ok = false;
        for (int i = 0; i < k; ++i) {
            if (x % p[i] == 0) {
                ok = true;
                break;
            }
        }
        if (ok) {
            ++cnt;
            if (cnt == n) {
                cout << x << "\n";
                return 0;
            }
        }
    }
}

