import random
import sys
import argparse

# --- 輔助函數：生成樹 (N-1 邊，連通無環) ---
def generate_tree(n):
    """
    生成一個具有 n 個節點的隨機樹 (連通且無環)。
    """
    if n <= 0:
        return 0, 0, []
    if n == 1:
        return 1, 0, []
        
    m = n - 1
    edges = set()
    
    nodes = list(range(1, n + 1))
    
    # 建立連通骨架 (長鏈)
    random.shuffle(nodes) 
    for i in range(n - 1):
        u = nodes[i]
        v = nodes[i+1]
        edge = (u, v)
        edges.add(edge)
        
    return n, m, list(edges)

def generate_k_component_graph(n, k_val):
    """
    生成一個由 (N-K 完全圖) 與 (K 長鏈) 連接而成的圖。
    
    K-Component 結構要求：
    1. 節點 N-K 形成完全圖 (K_{N-K})。
    2. 節點 K 形成長鏈。
    3. 長鏈的一端連接到完全圖的一個點上。
    """
        
    edges = set()
    all_nodes = list(range(1, n + 1))
    random.shuffle(all_nodes) # 隨機分配節點
    
    # 1. 分配節點
    n_minus_k = n - k_val
    complete_nodes = all_nodes[:n_minus_k] # 形成完全圖的節點 (N-K 個)
    chain_nodes = all_nodes[n_minus_k:]    # 形成長鏈的節點 (K 個)
    
    # 2. 結構 A: 建立完全圖 K_{N-K}
    # 邊數 M_complete = (N-K) * (N-K - 1) / 2
    for i in range(n_minus_k):
        for j in range(i + 1, n_minus_k):
            u = complete_nodes[i]
            v = complete_nodes[j]
            edges.add(tuple((u, v)))

    # 3. 結構 B: 建立 K 節點長鏈
    # 邊數 M_chain = K - 1 (如果 K >= 2)
    if k_val >= 2:
        # 隨機排列長鏈節點
        random.shuffle(chain_nodes)
        for i in range(k_val - 1):
            u = chain_nodes[i]
            v = chain_nodes[i+1]
            edges.add(tuple((u, v)))
    
    # 4. 連接: 將長鏈的一個點連接到完全圖的一個點
    # 選擇長鏈的任一端點 (例如第一個點)
    chain_endpoint = chain_nodes[0]
    # 隨機選擇完全圖中的一個點
    complete_node_anchor = random.choice(complete_nodes)
    
    # 建立連接邊
    u = chain_endpoint
    v = complete_node_anchor
    edges.add(tuple((u, v)))
        
    # 5. 計算總邊數
    m = len(edges)
    # print(f"--- 成功生成 K-Component 圖：完全圖節點數={n_minus_k}, 長鏈節點數={k_val}, 總邊數 M={m} ---", file=sys.stderr)
    return n, m, list(edges)

# --- 核心圖生成函數 ---
def generate_fixed_graph(n, m, is_connected=False, is_acyclic=False, is_list=False, is_circle=False, k_val=0, input_seed=None):
    """
    主要圖生成函數，接受固定 N 和 M。
    
    Args:
        n (int): 確切的節點數量 N。
        m (int): 確切的邊數量 M。
        is_connected (bool): 圖是否必須連通。
        is_acyclic (bool): 圖是否必須無環 (即生成樹或森林)。
        input_seed (int | None): 隨機數種子。
        
    Returns:
        tuple: (n, m, edges)
    """
    # 設置隨機數種子
    if input_seed is not None:
        random.seed(input_seed)
        # print(f"--- 使用種子 {input_seed}，結果固定 ---", file=sys.stderr)
    else:
        # print("--- 未設定種子，每次結果可能不同 ---", file=sys.stderr)
        pass
        
    if k_val > 0:
        if n > 0 and k_val < n:
            # print(f"警告：啟用 K-Component 模式 (K={k_val})，將忽略 M、--connected、--acyclic、--list 和 --Circle。", file=sys.stderr)
            return generate_k_component_graph(n, k_val)
        else:
            # print(f"警告：K 值 K={k_val} 不合法 (需滿足 0 < K < N={n})，將忽略 K-Component 模式。", file=sys.stderr)
            k_val = 0 # 繼續執行下面的邏輯

    # 1. 基本檢查和限制
    if n <= 0:
        return 0, 0, []
    
    if m == 0:
        return n, 0, []
    
    max_possible_edges = n * (n - 1) // 2
        
    # 2. 處理特殊條件 (連通性/無環性) 
    # M_min 是保持連通性所需的最小邊數
    m_min_connected = n - 1 if n > 0 else 0 
    
    # M_max 是保持無環性所需的最大邊數 (也是森林的最大邊數)
    m_max_acyclic = n - 1 if n > 0 else 0
    
    if is_connected and m < m_min_connected:
        # print(f"警告：N={n} 的圖至少需要 M={m_min_connected} 才能連通，但您指定 M={m}。將無法保證連通性。", file=sys.stderr)
        m = random.randint(m_min_connected, max_possible_edges) # 隨機調整 M 到合理範圍
        # print(f"警告：將 M 調整為 M={m} 以嘗試保持連通性。", file=sys.stderr)
        
        
    if is_acyclic and m > m_max_acyclic:
        # print(f"警告：N={n} 的圖至多能有 M={m_max_acyclic} 條邊才能無環，但您指定 M={m}。", file=sys.stderr)
        m = random.randint(m_max_acyclic//2, m_max_acyclic) # 隨機調整 M 到合理範圍
        # print(f"警告：將 M 調整為 M={m} 以嘗試保持無環性。", file=sys.stderr)

    # 3. 根據模式生成圖
    
    if is_list:
        # 生成一條長鏈
        edges = []
        nodes = list(range(1, n+1))
        random.shuffle(nodes)
        for i in range(n-1):
            edges.append((nodes[i], nodes[i+1]))
        random.shuffle(edges)
        
        return n, len(edges), edges
    
    elif is_circle:
        # 生成一個大圓圈
        edges = []
        nodes = list(range(1, n+1))
        random.shuffle(nodes)
        for i in range(n):
            u = nodes[i]
            v = nodes[(i+1) % n]  # 環狀連接
            edges.append((u, v))
        random.shuffle(edges)
        
        return n, len(edges), edges
    
    elif is_connected and is_acyclic:
        # A. 樹：N-1 條邊 (必須 M == N-1)
        if m != n - 1:
            # 雖然上面已經警告，但這裡仍應生成 N-1 邊的樹，否則無法保證屬性
            # print(f"警告：強制將 M 設定為 N-1={n-1} 條以生成樹。", file=sys.stderr)
            return generate_tree(n)
        return generate_tree(n)
        
    elif is_connected:
        # B. 連通圖 (M >= N-1)
        # 生成連通骨架 (樹)
        _, _, edges_list = generate_tree(n)
        
        # 添加剩餘的 M - (N-1) 條邊
        edges_to_add = m - (n - 1)
        
        while edges_to_add > 0:
            u = random.randint(1, n)
            v = random.randint(1, n)
            
            if u != v:
                edge = (u, v)
                edges_list.append(edge)
                edges_to_add -= 1
        
        return n, len(edges_list), edges_list
        
    elif is_acyclic:
        # C. 森林 (M <= N-1)
        # 生成 N-1 邊的樹，然後隨機移除邊
        _, _, all_tree_edges = generate_tree(n)
        
        # 隨機抽取 M 條邊，確保無環
        edges = random.sample(all_tree_edges, m) 
        
        return n, m, edges

    else:
        # D. 非連通圖，不管有無環 (M 任意)
        if n < 2:
            return n, 0, []
        
        # 至少留下 N2 = 1 個節點作為孤立點或獨立分量
        n1 = random.randint(1, n - 1) 
        n2 = n - n1
                    
        # 2. 分配 M 條邊到 M1 和 M2
        # 將所有節點隨機分配到兩組
        all_nodes = list(range(1, n + 1))
        random.shuffle(all_nodes)
        nodes1 = set(all_nodes[:n1])
        nodes2 = set(all_nodes[n1:])
        
        edges = list()
        m_remaining = m
        
        # 策略：將 M1 分配為 M 條邊的一個比例 (例如 80%)，剩下的給 M2
        # 確保 M1 至少是 M 剩餘的邊數
        m1 = random.randint(1, m_remaining-1)
        m2 = m_remaining - m1
        
        # 3. 在子圖 1 內部生成 M1 條邊
        while m1 > 0:
            u = random.choice(list(nodes1))
            v = random.choice(list(nodes1))
            
            if u != v:
                edge = (u, v)
                edges.append(edge)
                m1 -= 1
        
        # 4. 在子圖 2 內部生成 M2 條邊
        while m2 > 0:
            # 僅當 N2 >= 2 時才生成邊
            if n2 < 2:
                # print("警告：N2 < 2，無法在子圖 2 內生成邊，將邊轉移到子圖 1。", file=sys.stderr)
                # 這是無法解決的矛盾，因為我們已經用盡了 M1 的 quota
                # 如果發生，表示一開始分配 M1/M2 時就應該更偏向 M1
                break
                
            u = random.choice(list(nodes2))
            v = random.choice(list(nodes2))
            
            if u != v:
                edge = (u, v)
                edges.append(edge)
                m2 -= 1
        
        # 5. 輸出結果
        final_m = len(edges)
        if final_m != m:
            # print(f"注意：由於隨機分配失敗，實際邊數 M={final_m}，小於要求 M={m}。", file=sys.stderr)
            pass

        return n, final_m, list(edges)
        

def output_graph(n, m, edges, output_file_stream=sys.stdout):
    """
    將圖的資訊寫入指定的檔案流 (或預設的 sys.stdout)。
    """
    # 寫入 N 和 M
    output_file_stream.write(f"{n}\n")
    
    adj_matrix = [[0] * n for _ in range(n)]
    for u, v in edges:
        adj_matrix[u-1][v-1] = 1
        adj_matrix[v-1][u-1] = 1  # 無向圖
        
    for row in adj_matrix:
        output_file_stream.write("".join(map(str, row)) + "\n")

# --- 參數解析與主執行區塊 ---
def main():
    parser = argparse.ArgumentParser(
        description='一個用於生成具有特定屬性 (連通性/環/固定 N/M) 的隨機圖的工具。',
        formatter_class=argparse.RawTextHelpFormatter
    )

    # 必填參數：兩組 N 和 M
    parser.add_argument('n1', type=int, help='第一張圖的節點數量 N1。')
    parser.add_argument('m1', type=int, help='第一張圖的邊的數量 M1。')
    parser.add_argument('n2', type=int, help='第二張圖的節點數量 N2。')
    parser.add_argument('m2', type=int, help='第二張圖的邊的數量 M2。')
    
    # 可選參數
    parser.add_argument('--seed', type=int, default=None, help='隨機數種子，用於固定輸出結果。')
    parser.add_argument('-o', '--output', type=str, default=None, help='指定輸出檔案的路徑。如果不設定，則輸出到標準輸出 (stdout)。')
    parser.add_argument('-k', '--k-component', type=int, default=0, help='啟用 K-Component 特殊結構模式。指定 K 值 (0 < K < N)。\n')
    
    # 旗標參數 (Flags)
    parser.add_argument('-c', '--connected', action='store_true', 
                        help='如果設定，則圖必須連通 (要求 M >= N-1)。\n'
                             '如果 M < N-1，此屬性會被忽略。')
    parser.add_argument('-C', '--Circle', action='store_true', 
                        help='如果設定，則圖是一個大圓圈。\n')
    parser.add_argument('-a', '--acyclic', action='store_true', 
                        help='如果設定，則圖必須無環 (森林或樹，要求 M <= N-1)。\n'
                             '如果 M > N-1，此屬性會被忽略。')
    parser.add_argument('-l', '--list', action='store_true', 
                        help='如果設定，則產生的圖會是一條長鏈。\n')

    args = parser.parse_args()

    # 輸出參數信息
    # print("--- 參數設定 ---", file=sys.stderr)
    # print(f"圖 G1: N1={args.n1}, M1={args.m1}", file=sys.stderr)
    # print(f"圖 G2: N2={args.n2}, M2={args.m2}", file=sys.stderr)
    # print(f"Seed (種子): {args.seed}", file=sys.stderr)
    # print(f"要求連通 (-c): {args.connected}", file=sys.stderr)
    # print(f"要求無環 (-a): {args.acyclic}", file=sys.stderr)
    # print(f"要求長鏈 (-l): {args.list}", file=sys.stderr)
    # print(f"要求大圓圈 (-C): {args.Circle}", file=sys.stderr)
    # print(f"輸出檔案 (-o): {args.output if args.output else '標準輸出 (stdout)'}", file=sys.stderr)
    # print("-" * 30, file=sys.stderr)

    # 產生圖形
    # 注意：現在會有重邊的問題～，但因為改成鄰接矩陣輸出後，重邊不影響結果
    # 1. 生成第一張圖 G1
    N1, M1, EDGES1 = generate_fixed_graph(
        n=args.n1, 
        m=args.m1, 
        is_connected=args.connected, 
        is_acyclic=args.acyclic,
        is_list=args.list,
        is_circle=args.Circle,
        k_val=args.k_component,
        input_seed=args.seed
    )
    # 2. 生成第二張圖 G2
    N2, M2, EDGES2 = generate_fixed_graph(
        n=args.n2,
        m=args.m2,
        is_connected=args.connected,
        is_acyclic=args.acyclic,
        is_list=args.list,
        is_circle=args.Circle,
        k_val=args.k_component,
        input_seed=(args.seed + 1) if args.seed is not None else None
    )
    
    # 3. 處理輸出到檔案或 stdout
    if args.output:
        try:
            with open(args.output, 'w') as f:
                # 順序輸出 G1
                output_graph(N1, M1, EDGES1, output_file_stream=f)
                # 順序輸出 G2
                output_graph(N2, M2, EDGES2, output_file_stream=f)
            # print(f"\n[圖形統計] 成功寫入檔案: {args.output}", file=sys.stderr)
        except IOError as e:
            # print(f"\n[錯誤] 無法寫入檔案 {args.output}: {e}", file=sys.stderr)
            sys.exit(1)
    else:
        # 輸出到標準輸出
        output_graph(N1, M1, EDGES1, output_file_stream=sys.stdout)
        output_graph(N2, M2, EDGES2, output_file_stream=sys.stdout)
        # print(f"\n[圖形統計] 輸出到標準輸出完成。", file=sys.stderr)

    # 輸出統計資訊 (到 stderr)
    # print(f"[圖形統計] G1: 實際節點 N={N1}, 實際邊 M={M1}", file=sys.stderr)
    # print(f"[圖形統計] G2: 實際節點 N={N2}, 實際邊 M={M2}", file=sys.stderr)

if __name__ == "__main__":
    # 將舊的範例執行區塊替換為 main 函數
    main()