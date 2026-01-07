#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map> // 由於頂點編號從 1 開始，這裡依然保留 PII
#include <set> // 同上

#define mkp std::make_pair
#define pb push_back
#define F first
#define S second

using namespace std;

// 定義類型別名
typedef pair<int, int> PII;

// 定義模數
const int MOD = 1e9 + 7;

// 使用 vector<vector<int>> 作為鄰接列表
// VG 是頂點數。由於頂點編號從 1 開始，vector 的大小為 VG + 1。
using AdjList = std::vector<std::vector<int> >;

int cnt = 0;

/**
 * @brief 深度優先搜尋，用於尋找樹中距離起點最遠的頂點。
 * * @param u 當前節點。
 * @param parent 父節點。
 * @param current_dist 當前節點 u 的深度/距離。
 * @param adj 圖的鄰接列表。
 * @return 一個 pair，包含 (最遠距離, 最遠頂點的編號)。
 */
PII dfs(
    int u, 
    int parent, 
    int current_dist, 
    const AdjList& adj
) {
    // 初始化：最遠點是 u 自己，距離是 current_dist
    int max_dist = current_dist;
    int farthest_node = u;
    cnt++;
    
    // 遍歷所有相鄰節點
    for (int v : adj[u]) {
        // 避免走回父節點
        if (v != parent) {
            PII result = dfs(v, u, current_dist + 1, adj);
            
            // 更新最遠距離和對應的頂點
            if (result.F > max_dist) {
                max_dist = result.F;
                farthest_node = result.S;
            }
        }
    }
    return mkp(max_dist, farthest_node);
}

/**
 * @brief 從給定起始節點計算樹的直徑的第一步。
 * * @param start_node 起始節點。
 * @param adj 圖的鄰接列表。
 * @return 一個 pair，包含 (從 start_node 出發的最遠距離, 最遠頂點的編號)。
 */
PII find_farthest_node(int start_node, const AdjList& adj) {
    // 執行 DFS，從 start_node 開始，距離為 0
    return dfs(start_node, -1, 0, adj);
}

/**
 * @brief 計算樹的直徑 (最長路徑的長度)。
 * @param VG 頂點數 (1 到 VG)。
 * @param EG 邊的集合。
 * @return 樹的直徑。
 */
int tree_diameter(const int VG, const AdjList& adj) {
    // 對於空圖或單點圖
    if (VG <= 1) return 0; 
    
    // 樹是連通的，任取一個有效的頂點作為起點
    int start_node = 1; // 假設頂點編號從 1 開始

    // 1. 第一次 DFS：找到距離任一點最遠的點 u
    cnt = 0;
    PII result1 = find_farthest_node(start_node, adj);
    if (cnt != VG) {
        // 如果 DFS 沒有訪問所有頂點，說明圖不連通
        return -1; 
    }

    int u = result1.S; // u 是距離 start_node 最遠的頂點

    // 2. 第二次 DFS：從 u 開始找到最遠的點，其距離即為直徑
    PII result2 = find_farthest_node(u, adj);
    int diameter = result2.F; // result2.F 是從 u 出發的最遠距離，即為直徑

    return diameter;
}

int main(void){
    // 禁用同步，加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 讀取圖 G
    int n_G;
    cin >> n_G;
    cin.ignore();

    AdjList adj_list_G(n_G + 1);

    // 讀取 n*n 的鄰接矩陣
    for(int i = 1; i <= n_G; i++) {
        string row;
        getline(cin, row);
        for(int j = 1; j <= n_G; j++) {
            char c = row[j - 1];
            if (c == '1') {
                adj_list_G[i].push_back(j);
            }
        }
    }
    
    int n_H;
    cin >> n_H;
    cin.ignore();

    AdjList adj_list_H(n_H + 1);

    // 讀取 n*n 的鄰接矩陣
    for(int i = 1; i <= n_H; i++) {
        string row;
        getline(cin, row);
        for(int j = 1; j <= n_H; j++) {
            char c = row[j - 1];
            if (c == '1') {
                adj_list_H[i].push_back(j);
            }
        }
    }

    // 1. 計算 G 的直徑
    int diam_G = tree_diameter(n_G, adj_list_G);
    if (diam_G == -1) {
        // 如果 G 不是連通圖，輸出 -1 並結束
        cout << -1 << endl;
        return 0;
    }

    // 2. 計算 H 的直徑
    int diam_H = tree_diameter(n_H, adj_list_H);
    if (diam_H == -1) {
        // 如果 H 不是連通圖，輸出 -1 並結束
        cout << -1 << endl;
        return 0;
    }

    // 輸出結果： (diam_G + diam_H) % MOD
    // 由於直徑為非負整數，直接相加再取模即可
    long long total_diameter = (1LL * diam_G + diam_H) % MOD;
    cout << total_diameter << endl;

    return 0;
}