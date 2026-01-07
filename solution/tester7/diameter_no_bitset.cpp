#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <queue> 

#define mkp make_pair
#define pb push_back
#define F first
#define S second

using namespace std;

typedef pair<int, int> PII;

const int MOD = 1e9 + 7;

// 廣度優先搜尋 (BFS)
// 接收：起始節點 start_node, 節點數量 VG, 鄰接列表 adj
// 傳回：一個 pair，包含 (最遠距離, 是否連通)
PII bfs(int start_node, int VG, vector<vector<int> >& adj) {
    // 儲存節點到起始點的距離
    int dist[VG + 1];
    // 使用 queue 進行 BFS
    queue<int> q;

    int max_dist = 0;
    int used_node = 0;

    // 1. 初始化距離
    for (int i = 1; i <= VG; ++i) {
        dist[i] = -1; 
    }

    // 2. 設定起點
    dist[start_node] = 0;
    q.push(start_node);
    used_node++;

    // 3. 執行 BFS
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int current_dist = dist[u];
        
        // 更新最遠距離和節點
        max_dist = max(max_dist, current_dist);
        
        // 遍歷所有相鄰節點
        for(int v : adj[u]) {
            // 如果 v 尚未訪問
            if (dist[v] == -1) {
                // 標記 v 的距離
                dist[v] = current_dist + 1;
                // 計數已使用的節點
                used_node++;
                // 將 v 推入 queue
                q.push(v);
            }
        }
    }

    // 傳回 (最遠距離, 是否連通)
    return mkp(max_dist, used_node == VG);
}

// 圖直徑計算函數：使用 N 次 BFS
int graph_diameter(const int VG, vector<vector<int> >& adj) {
    // 對於單點圖，如果圖中確實只有一個頂點，直徑為 0
    if (VG == 1) return 0; 

    // N 次 BFS 找出最大距離
    int diameter = 0;
    for(int u = 1; u <= VG; u++){
        PII result = bfs(u, VG, adj);
        if(!result.S){
            // 如果圖不連通，回傳 -1 表示無效直徑
            return -1;
        }
        diameter = max(diameter, result.F);
    }

    return diameter % MOD;
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // 讀取圖 G
    int n_G;
    cin >> n_G;
    cin.ignore();
    
    vector<vector<int> > adj_G(n_G + 1); 
    for(int i = 1; i <= n_G; i++) {
        string row;
        getline(cin, row);
        for(int j = 1; j <= n_G; j++) {
            char c = row[j - 1];
            if (c == '1') {
                adj_G[i].push_back(j); 
            }
        }
    }

    // 讀取圖 H
    int n_H;
    cin >> n_H;
    cin.ignore();
    
    vector<vector<int> > adj_H(n_H + 1); 
    for(int i = 1; i <= n_H; i++) {
        string row;
        getline(cin, row);
        for(int j = 1; j <= n_H; j++) {
            char c = row[j - 1];
            if (c == '1') {
                adj_H[i].push_back(j); 
            }
        }
    }

    // 1. 計算 G 的直徑
    int diam_G = graph_diameter(n_G, adj_G);
    if(diam_G == -1){
        // 如果 G 不連通，輸出 -1 並結束
        cout << -1 << endl;
        return 0;
    }

    // 2. 計算 H 的直徑
    int diam_H = graph_diameter(n_H, adj_H);
    if(diam_H == -1){
        // 如果 H 不連通，輸出 -1 並結束
        cout << -1 << endl;
        return 0;
    }

    // 輸出結果
    cout << (diam_G%MOD + diam_H%MOD) % MOD << endl;

    return 0;
}