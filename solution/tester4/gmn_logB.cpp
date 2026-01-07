#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 2000000000;
typedef vector<vector<pair<int, int>>> Graph;
int main(void) {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    int B, b;
    scanf("%d%d", &B, &b);
    Graph v(n + 1);
    for (int i = 0; i < m; i++) {
        int from, to, w;
        scanf("%d%d%d", &from, &to, &w);
        v[from].emplace_back(to, -w);
    }
    int g;
    scanf("%d", &g);
    vector<int> charges(g);
    for (int i = 0; i < g; i++) scanf("%d", &charges[i]);
    v[0].emplace_back(s, B - b);
    s = 0;

    vector<int> dist(n + 1, inf);
    auto bellman_ford = [n, B](const Graph& v, vector<int>& dist, int s) {
        dist[s] = 0;
        for (int j = 0; j < n - 1; j++) {
            bool relaxed = false;
            for (int i = 0; i <= n; i++)
                for (const auto& [to, w] : v[i]) {
                    long long nw = (long long)dist[i] + w;
                    if (nw > B) continue;
                    if (nw < 0) nw = 0;
                    if (dist[to] > nw) {
                        dist[to] = nw;
                        relaxed = true;
                    }
                }
            if (!relaxed) break;
        }
    };
    bellman_ford(v, dist, 0);
    int ans = inf;
    if (dist[t] != inf) {
        ans = 0;
    } else {
        for (int ch : charges) {
            if (dist[ch] == inf) continue;
            int lb = 0, rb = B + 1;
            while (lb != rb) {
                int mid = (lb + rb) / 2;
                v[0].clear();
                v[0].emplace_back(ch, B - mid);
                vector<int> dist2(n + 1, inf);
                bellman_ford(v, dist2, 0);
                if (dist2[t] == inf)
                    lb = mid + 1;
                else
                    rb = mid;
            }
            if (lb == B + 1) continue;
            ans = min(ans, max(lb - (B - dist[ch]), 0));
        }
    }
    printf("%d\n", ans == inf ? -1 : ans);
    return 0;
}
