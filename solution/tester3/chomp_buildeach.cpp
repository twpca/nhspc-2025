#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

vector<bool> dp(2<<27, false);
vector<vector<int>> f(501, vector<int>(501, 0));

int getIdx(int i, int j, int k){
    return i | (j << 9) | (k << 18);
}

void init(int n) {
    dp.clear();
    dp.resize(2<<27, false);
    f.clear();
    f.resize(n+1, vector<int>(n+1, 0));
    dp[getIdx(0, 0, 0)] = true;
    for (int i=1;i<=n;++i) {
        for (int j=0;j<=i;++j) {
            for (int k=0;k<=j;++k) {
                dp[getIdx(i, j, k)] = true;
            }
        }
    } 

    f[0][0] = 1;
    int cnt[503] = {0}, cntid = 1;

    for (int q=0;q<=n;++q) {
        for (int r=0;r<=n;++r) {
            if (r > q) {
                f[q][r] = f[q][q];
                continue;
            }

            if (q==0 && r==0) f[q][r] = 1;
            else if (f[q-1][r] < q) f[q][r] = f[q-1][r];
            else {
                cntid++;
                for (int a=0;a<q;++a) cnt[f[a][r]] = cntid;
                for (int b=0;b<r;++b) cnt[f[q][b]] = cntid;

                int mex = 1;
                while (cnt[mex] == cntid) mex++;
                // we do not care p > 500
                mex = min(n+1, mex); 
                f[q][r] = mex;
            }
            if (f[q][r] >= q) dp[getIdx(f[q][r], q, r)] = false;
        }
    }
}

void solve () {
    int n, x, y, z;
    int p, q, r;

    cin >> n >> x >> y >> z;
    init(n);
    
    r = x;
    q = x + y;
    p = x + y + z;

    vector<tuple<int,int>> sol;

    for (int t=0;t<r;++t) if (!dp[getIdx(p, q, t)]) sol.emplace_back(3, t+1);
    for (int t=0;t<q;++t) if (!dp[getIdx(p, t, min(t, r))]) sol.emplace_back(2, t+1);
    for (int t=0;t<p;++t) if (!dp[getIdx(t, min(t, q), min(t, r))]) sol.emplace_back(1, t+1);

    sort(sol.begin(), sol.end());
    cout << sol.size() << '\n';
    for (int i = 0; i < sol.size(); i++) {
        auto [x, y] = sol[i];
        cout << x << ' ' << y << ((i < sol.size()-1) ? ' ' : '\n');
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}