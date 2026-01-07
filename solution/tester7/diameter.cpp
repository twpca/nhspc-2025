#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <bitset>

#define mkp make_pair
#define pb push_back
#define F first
#define S second

using namespace std;

typedef pair<int, int> PII;

const int MOD = 1e9 + 7;
// 設定最大節點數，Bitset 需要編譯期常數
// 請根據題目實際 N 的範圍調整，例如 N <= 2000 或 N <= 5000
const int MAXN = 2005; 

// 廣度優先搜尋 (BFS)
// 優化：使用 Bitset 維護未訪問集合與鄰接矩陣
// 傳回：一個 pair，包含 (最遠距離, 遍歷過的節點數量)
PII bfs(int start_node, int n, const vector<bitset<MAXN> >& adj) {
    // 初始化距離陣列，-1 代表未訪問
    vector<int> dist(n + 1, -1);
    
    // 2. 維護一個 unvisited 的 bitset
    // 初始化：將 1~n 全部設為 1 (表示都在 unvisited 集合中)
    bitset<MAXN> unvisited;
    for(int i = 1; i <= n; i++) unvisited[i] = 1;

    queue<int> q;
    int max_dist = 0;
    int used_node_count = 0;

    // 設定起點
    dist[start_node] = 0;
    q.push(start_node);
    
    // 從 unvisited 移除起點
    unvisited[start_node] = 0; 
    used_node_count++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int current_dist = dist[u];
        if (current_dist > max_dist) max_dist = current_dist;

        // 3. 核心優化邏輯
        // 取出 u 的鄰居，並與 unvisited 做 AND 運算
        // 結果 new_candidates 中為 1 的 bit 就是「u 的鄰居」且「還沒被訪問過」
        bitset<MAXN> new_candidates = adj[u] & unvisited;

        // 使用 _Find_first() 和 _Find_next() 快速遍歷所有為 1 的 bit
        // 這些函數直接跳到下一個是 1 的位置，略過中間的 0
        for (int v = new_candidates._Find_first(); v < new_candidates.size(); v = new_candidates._Find_next(v)) {
            // 由於 new_candidates 是與 unvisited AND 出來的結果，
            // 這裡的 v 保證是未訪問過的，所以直接更新並加入 queue
            
            dist[v] = current_dist + 1;
            unvisited[v] = 0; // 關鍵：馬上從 unvisited 移除，避免重複入隊
            q.push(v);
            used_node_count++;
        }

        // for (int v = 1; v <= n; v++) {
        //     if (new_candidates[v]) { // 如果 v 是未訪問的鄰居
        //         dist[v] = current_dist + 1;
        //         unvisited[v] = 0; // 關鍵：標記為已訪問，防止重複處理
        //         q.push(v);
        //         used_node_count++;
        //     }
        // }
    }

    return mkp(max_dist, used_node_count);
}

// 處理單個圖的輸入與計算
// 回傳該圖的直徑，若不連通回傳 -1
int solve_graph() {
    int n;
    cin >> n;
    cin.ignore();

    // 1. 各個點維護一個鄰居的 bitset
    // adj[i] 的第 j 個 bit 為 1 代表 i 和 j 相連
    vector<bitset<MAXN> > adj(n + 1);
    
    for (int i = 1; i <= n; i++) {
        string row;
        getline(cin, row);
        for (int j = 1; j <= n; j++) {
            char c = row[j - 1];
            if (c == '1') {
                adj[i][j] = 1; 
                adj[j][i] = 1; // 無向圖
            }
        }
    }

    if (n == 1) return 0;

    int diameter = 0;
    
    // N 次 BFS 找出最大距離
    for (int u = 1; u <= n; u++) {
        PII result = bfs(u, n, adj);
        
        // 檢查連通性：如果遍歷的節點數不等於總節點數，代表圖不連通
        if (result.S != n) {
            return -1; 
        }
        diameter = max(diameter, result.F);
    }

    return diameter;
}

int main(void) {
    // 優化 IO 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 計算圖 G
    int diam_G = solve_graph();
    if (diam_G == -1) {
        cout << -1 << endl;
        return 0;
    }

    // 計算圖 H
    int diam_H = solve_graph();
    if (diam_H == -1) {
        cout << -1 << endl;
        return 0;
    }

    cout << (diam_G % MOD + diam_H % MOD) % MOD << endl;

    return 0;
}