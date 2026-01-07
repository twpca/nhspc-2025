#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string p;
    cin >> n >> p;

    int left = count(p.begin(), p.end(), '('), right = n - left;
    cout << right - left << '\n';
    return 0;
}
