#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string p;
    cin >> n >> p;

    int removed = 0, cnt = 0;
    for (char ch : p) {
        if (ch == '(') ++cnt;
        else --cnt;

        if (cnt == -1) {
            ++removed;
            ++cnt;
        }
    }

    cout << removed << '\n';
    return 0;
}
