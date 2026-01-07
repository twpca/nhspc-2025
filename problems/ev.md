# 電動車充電規劃問題 (EV)

## 問題描述

小明買了一台電動車，其電池容量為$B$。小明知道電動車的初始電量$b$，他要規劃從起點開到終點的路線，使得所需的充電費用越少越好。電動車在一些路段會耗電（如平路或是上坡），在一些路段會充電（如下坡）。**這些充電路段是不會收費的**。我們用一個有向圖表示地圖，邊的權重代表電動車開過此邊會讓電量增加或減少，如果開過此邊會充電，則邊的權重為一個正數，反之如果開過此邊會耗電，則邊的權重為一個負數。我們假設圖沒有正環。

電動車在行駛時，電量需要永遠大於等於$0$，而且無論充電量多大，電量最多為$B$。更明確地說，令$p$為電動車目前電量，並考慮一個權重為$w$的邊：如果$w$非負數，則電動車一定可以開過此邊（即使電量$p=0$），且剩餘電量為$\min(B, p+w)$；如果$w$是負數，且$p+w \ge 0$，則電動車可以開過此邊，且開過此邊後的剩餘電量為$p+w$；然而，如果$p+w<0$，則電動車無法開過此邊。

地圖上有一些節點是充電站，小明可以經過多個充電站，因為充電要花時間找充電樁，小明決定路途中**最多只用一個充電站充電**。充電一單位的價格是一塊錢，小明的目標是花最少的錢到達目的地。

舉例來說，考慮以下三個圖，我們用方形節點代表充電站，圓形節點則無法充電。假設電池容量$B=100$，起點為$s$，終點為$t$，且初始電量為$20$。

在下圖中，電動車可以從$s$抵達$t$，且最小充電費用為$0$。
\begin{center}
\begin{tikzpicture}[
    node distance=0.6cm and 1.8cm, inner sep=0pt, minimum size=5mm,
    >=stealth
]

\node[draw,circle ] (s) {$s$};
\node[draw,circle ] (a) [right=of s] {};
\node[draw,circle ] (b) [right=of a] {};
\node[draw,rectangle ] (c) [right=of b] {};
\node[draw,circle ] (d) [right=of c] {};
\node[draw,circle ] (t) [right=of d] {$t$};

\path[->] (s) edge node[above]{\small $-5$} (a);
\path[->] (a) edge node[above]{\small $10$} (b);
\path[->] (b) edge node[above]{\small $-25$} (c);
\path[->] (c) edge node[above]{\small $5$} (d);
\path[->] (d) edge node[above]{\small $-5$} (t);

\end{tikzpicture}
\end{center}

在下圖中，電動車無法從$s$抵達$t$。
\begin{center}
\begin{tikzpicture}[
    node distance=0.6cm and 1.8cm,inner sep=0pt, minimum size=5mm,
    >=stealth
]

\node[draw,circle ] (s) {$s$};
\node[draw,circle ] (a) [right=of s] {};
\node[draw,circle ] (b) [right=of a] {};
\node[draw,circle ] (c1) [above right=0.6cm and 1.1cm of b] {};
\node[draw,circle ] (c2) [below right=0.6cm and 1.1cm of b] {};
\node[draw,rectangle ] (d) [right=2.5cm of b] {};
\node[draw,circle ] (t) [right=of d] {$t$};

\path[->] (s) edge node[above]{\small $-15$} (a);
\path[->] (a) edge node[above]{\small $200$} (b);
\path[->] (b) edge node[above left]{\small $-60$} (c1);
\path[->] (b) edge node[below left]{\small $-80$} (c2);
\path[->] (c1) edge node[above right]{\small $-70$} (d);
\path[->] (c2) edge node[below right]{\small $-40$} (d);
\path[->] (d) edge node[above]{\small $20$} (t);
\end{tikzpicture}
\end{center}

在下圖中，電動車可以從$s$抵達$t$，且最小充電費用為$35$。
\begin{center}
\begin{tikzpicture}[
    node distance=0.6cm and 1.8cm,inner sep=0pt, minimum size=5mm,
    >=stealth
]

\node[draw,circle ] (s) {$s$};
\node[draw,circle ] (a) [right=of s] {};
\node[draw,rectangle ] (b) [right=of a] {};
\node[draw,circle ] (c1) [above right=0.6cm and 1.1cm of b] {};
\node[draw,circle ] (c2) [below right=0.6cm and 1.1cm of b] {};
\node[draw,circle ] (d) [right=2.5cm of b] {};
\node[draw,circle ] (t) [right=of d] {$t$};

\path[->] (s) edge node[above]{\small $-10$} (a);
\path[->] (a) edge node[above]{\small $-5$} (b);
\path[->] (b) edge node[above left]{\small $-20$} (c1);
\path[->] (b) edge node[below left]{\small $-30$} (c2);
\path[->] (c1) edge node[above right]{\small $-40$} (d);
\path[->] (c2) edge node[below right]{\small $-10$} (d);
\path[->] (d) edge node[above]{\small $20$} (t);

\end{tikzpicture}
\end{center}

## 輸入格式

\begin{format}
\f{
$n$ $m$ $s$ $t$
$B$ $b$
$u_1$ $v_1$ $w_1$
$u_2$ $v_2$ $w_2$
$\vdots$
$u_m$ $v_m$ $w_m$
$g$ $p_1$ $p_2$ $\cdots$ $p_g$
}
\end{format}

- $n$ 為節點數。
- $m$ 為邊數。
- $s$ 為起點編號。
- $t$ 為終點編號。
- $B$ 為電池容量。
- $b$ 為電池初始電量。
- $u_i, v_i, w_i$ 代表圖中有一個邊由節點$u_i$至節點$v_i$，且權重為$w_i$。
- $g$ 為充電站個數。
- $p_i$ 為第$i$個充電站的節點編號。

## 輸出格式

\begin{format}
\f{
$a$
}
\end{format}

- $a$ 代表最少所需的充電費用。如果不存在路徑抵達終點，則$a = -1$。

## 測資限制

* $1 \le n\le 10^3$。
* $1 \le m\le 10^4$。
* $1 \le s,t\le n$。
* $1 \le B\le 10^9$。
* $0 \le b\le B$。
* $1 \le u_i, v_i\le n$，且 $u_i \neq v_i$。
* $-10^9 \le w_i\le 10^9$。
* $0 \le g\le n$。
* $1 \le p_i \le n$。
* 保證圖沒有正環。
* 輸入的數皆為整數。

## 範例測試

## 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | {{score.subtask1}} | 輸入滿足所有路段都不會充電，即 $w_i\le 0$， 且沒有充電站，即 $g = 0$。 |
| 2 | {{score.subtask2}} | 輸入滿足所有路段都不會充電，即 $w_i\le 0$。 |
| 3 | {{score.subtask3}} | 輸入滿足沒有充電站，即 $g = 0$。 |
| 4 | {{score.subtask4}} | 無額外限制。 |

