#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <climits>

#define mkp make_pair
#define pb push_back
#define F first
#define S second

using namespace std;

typedef pair<int, int> PII;

const int MOD = 1e9 + 7;

void debug(
    const int nGH,
    const vector<PII>& GH_node_map,
    const vector<PII>& EGH
){
        // 輸出結果
    cout << "--- 笛卡兒乘積 G x H 的結果 ---" << endl;
    cout << "頂點總數 (|V(G x H)|): " << nGH << endl;
    cout << "邊總數 (|E(G x H)|): " << EGH.size() << endl;

    cout << "\n頂點列表 (索引 -> (u, v)):" << endl;
    for (int i = 0; i < nGH; ++i) {
        cout << i << " -> (" << GH_node_map[i].F << ", " << GH_node_map[i].S << ")" << endl;
    }

    cout << "\n邊列表 (使用 G x H 的索引):" << endl;
    for (const auto& edge : EGH) {
        // 邊: (i, j)
        cout << "(" << edge.F << ", " << edge.S << ")  <->  ";
        // 原始頂點: ((u, v), (u', v'))
        cout << "((" << GH_node_map[edge.F].F << ", " << GH_node_map[edge.F].S << "), ";
        cout << "(" << GH_node_map[edge.S].F << ", " << GH_node_map[edge.S].S << "))" << endl;
    }
}

// 輔助函式：將邊集轉換為距離矩陣的初始狀態
vector<vector<int> > build_initial_distance_matrix(int n, const vector<PII>& edges) {
    // 初始化距離矩陣 dist[i][j]
    vector<vector<int> > dist(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0; // 自己到自己的距離為 0
    }

    // 設置初始邊權重為 1
    for (const auto& edge : edges) {
        // 由於 EGH 已經包含了 (i, j) 和 (j, i)，我們只需要設置一次
        // 確保不會覆蓋已經設置的 0 (dist[i][i])
        if (edge.F != edge.S && dist[edge.F][edge.S] == INT_MAX) {
            dist[edge.F][edge.S] = 1;
        }
    }
    return dist;
}


// 函式：計算圖直徑 (使用 Floyd-Warshall 演算法)
int calculate_diameter_fw(int n, vector<vector<int> > dist) {
    // Floyd-Warshall 的三重迴圈 O(N^3)
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 檢查溢位
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 計算直徑：所有最短路徑中的最大值
    int max_distance = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX) {
                // 如果圖不連通，直徑為無窮大（這裡簡單回傳 -1 表示不連通）
                return -1; 
            }
            max_distance = max(max_distance, dist[i][j]);
        }
    }

    return max_distance % MOD;
}

void cartesian_product(
    const set<PII>& EG, const int nG,
    const set<PII>& EH, const int nH
) {
    int nGH = nG * nH;  // |V(G x H)|

    // 2. 建立新圖的頂點到原始對 (u, v) 的反向映射 (方便輸出)
    // 頂點 (u, v) 在 G x H 中的索引為 i * nH + j
    // 其中 i = G_index[u], j = H_index[v]
    vector<PII> GH_node_map(nGH); // (u, v) 
    int current_index = 0;
    for (int u = 1; u <= nG; ++u) {
        for (int v = 1; v <= nH; ++v) {
            GH_node_map[current_index++] = mkp(u, v);
        }
    }
    
    // 3. 建立邊集 (E(G x H))
    vector<PII> EGH; // 儲存 (u, v) 和 (u', v') 之間的邊

    // 遍歷所有可能的邊 (u, v) - (u', v')
    for (int i = 0; i < nGH; ++i) {
        for (int j = i + 1; j < nGH; ++j) {
            const PII& node1 = GH_node_map[i]; // (u, v)
            const PII& node2 = GH_node_map[j]; // (u', v')
            
            int u = node1.F;
            int v = node1.S;
            int u_prime = node2.F;
            int v_prime = node2.S;

            bool is_edge = false;

            // 情況一：u = u' 且 (v, v') 在 H 中是邊
            if (u == u_prime && EH.count(mkp(v, v_prime))) {
                is_edge = true;
            }

            // 情況二：v = v' 且 (u, u') 在 G 中是邊
            if (v == v_prime && EG.count(mkp(u, u_prime))) {
                is_edge = true;
            }

            if (is_edge) {
                EGH.pb(mkp(i, j)); // 這裡使用 G x H 中的索引 i 和 j 作為新邊
                EGH.pb(mkp(j, i));
                // 如果需要輸出原始頂點，則用 mkp(node1, node2) 
            }
        }
    }

    // debug(nGH, GH_node_map, EGH);

    // 4. 計算圖直徑 (使用 Floyd-Warshall)
    vector<vector<int> > dist_matrix = build_initial_distance_matrix(nGH, EGH);
    int diameter = calculate_diameter_fw(nGH, dist_matrix);

    cout << diameter << endl;
}

int main(void){
    // 讀取圖 G
    int n_G;
    cin >> n_G;
    cin.ignore();
    // 讀取 G 的鄰接矩陣
    vector<vector<int> > adj_G(n_G+1, vector<int>(n_G+1, 0));
    for(int i = 1; i <= n_G; i++){
        string row;
        getline(cin, row);
        for (int j = 1; j <= n_G; j++) {
            adj_G[i][j] = row[j - 1] - '0';
        }
    }

    set<PII> EG;

    for (int i = 1; i <= n_G; ++i) {
        for (int j = i + 1; j <= n_G; ++j) {
            // 讀取到的矩陣是 0-based 索引 [i][j]
            if (adj_G[i][j] == 1) {
                // 將 0-based 索引 i, j 轉換為 1-based 頂點 i+1, j+1
                EG.insert(mkp(i, j));
                EG.insert(mkp(j, i)); // 無向圖
            }
        }
    }

    // 讀取圖 H
    int n_H;
    cin >> n_H;
    cin.ignore();
    
    // 讀取 H 的鄰接矩陣
    vector<vector<int> > adj_H(n_H+1, vector<int>(n_H+1));
    for(int i = 1; i <= n_H; i++){
        string row;
        getline(cin, row);
        for (int j = 1; j <= n_H; j++) {
            adj_H[i][j] = row[j - 1] - '0';
        }
    }

    set<PII> EH;

    for (int i = 1; i <= n_H; ++i) {
        for (int j = i + 1; j <= n_H; ++j) {
            // 讀取到的矩陣是 0-based 索引 [i][j]
            if (adj_H[i][j] == 1) {
                // 將 0-based 索引 i, j 轉換為 1-based 頂點 i+1, j+1
                EH.insert(mkp(i, j));
                EH.insert(mkp(j, i)); // 無向圖
            }
        }
    }

    // 進行笛卡兒乘積計算
    cartesian_product(EG, n_G, EH, n_H);

    return 0;
}