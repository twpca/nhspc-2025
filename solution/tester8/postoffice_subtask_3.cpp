#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define int long long

// BIT 0 base
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) { return sum(r) - sum(l); }

    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void Ado_Is_The_Best() {
    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    for (auto &[x, y] : a) cin >> x >> y;

    sort(a.begin(), a.end());
    vector<int> rec;
    for (int i = 0; i < n; i++) 
        rec.emplace_back(a[i].first);
    rec.emplace_back(2e9 + 1);

    auto check = [&](int m) {
        Fenwick<int> fw(n);

       

        for (auto &[x, s] : a) {
            int r = upper_bound(rec.begin(), rec.end(), x + m) - rec.begin();
            int l = lower_bound(rec.begin(), rec.end(), x - m) - rec.begin();



            if (r - l <= s)
                return false;
            int cnt = fw.rangeSum(l, r);
            for (int i = r - 1; i >= l && cnt <= s; i--) {
                if (fw.rangeSum(i, i+1) == 1)
                    continue;
                fw.add(i, 1);
                cnt += 1;
            }

            if (cnt <= s)
                return false;
        }

        return fw.rangeSum(0, n) <= k;
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
