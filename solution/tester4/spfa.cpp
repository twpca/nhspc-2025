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
    auto spfa = [B](const Graph& v, vector<int>& dist, int s) {
        priority_queue<pair<int, int>> pq;
        pq.push(make_pair(0, s));
        while (!pq.empty()) {
            auto [d, now] = pq.top();
            pq.pop();
            if (-d >= dist[now]) continue;
            dist[now] = -d;
            for (const auto& [to, w] : v[now]) {
                long long nw = (long long)dist[now] + w;
                if (nw > B) continue;
                if (nw < 0) nw = 0;
                if (dist[to] > nw) {
                    pq.push(make_pair(-nw, to));
                }
            }
        }
    };
    spfa(v, dist, 0);
    int ans = inf;
    if (dist[t] != inf) {
        ans = 0;
    } else {
        Graph v2(n + 1);
        for (int i = 1; i <= n; i++)
            for (const auto& [to, w] : v[i]) v2[to].emplace_back(i, w);
        vector<int> dist2(n + 1, inf);
        spfa(v2, dist2, t);
        for (int ch : charges) {
            if (dist2[ch] == inf || dist[ch] == inf) continue;
            ans = min(ans, dist2[ch] - (B - dist[ch]));
        }
    }
    printf("%d\n", ans == inf ? -1 : ans);
    return 0;
}
