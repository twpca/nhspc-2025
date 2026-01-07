#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string p;
    cin >> n >> p;

    bool ok = 1;
    int cnt = 0;
    for (char ch : p) {
        if (ch == '(') ++cnt;
        else --cnt;
    }

    if (cnt != 0)
        ok = 0;

    if (ok)
        cout << 0 << '\n';
    else
        cout << 2 << '\n';

    return 0;
}
