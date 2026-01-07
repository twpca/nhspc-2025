#include <bits/stdc++.h>

using ll = long long;
using std::pair;
using std::vector;
using pll = pair<ll, ll>;
using ld = double;
#define X first
#define Y second

// #define DRAW

const ld MAX = 1e12;
struct Item {
  ld val = MAX;
  int label = -1, src = -1;
};
struct Info {
  Item items[2];
  void insert(Item item) {
    for (int i = 0; i < 2; i++) {
      if (item.label == items[i].label) {
        if (items[i].val <= item.val)
          return;
        else
          items[i] = Item();
      }
    }
    if (items[0].val > items[1].val)
      std::swap(items[0], items[1]);
    for (int i = 0; i < 2; i++) {
      if (item.val < items[i].val)
        std::swap(item, items[i]);
    }
  }
  Info add(ld v, int src) {
    Info tmp = *this;
    tmp.items[0].val += v;
    tmp.items[0].src = src;
    tmp.items[1].val += v;
    tmp.items[1].src = src;
    return tmp;
  }
  Item get_by_label(int label) {
    for (int i = 0; i < 2; i++)
      if (items[i].label == label)
        return items[i];
    return Item();
  }
};
Info operator+(Info a, Info b) {
  for (int i = 0; i < 2; i++)
    a.insert(b.items[i]);
  return a;
}

pll operator-(const pll &a, const pll &b) { return {a.X - b.X, a.Y - b.Y}; }
ll abs2(const pll &v) { return v.X * v.X + v.Y * v.Y; }
ld abs(const pll &v) { return sqrt(abs2(v)); }
ll eval(const pair<pll, pll> &p) { return abs2(p.X - p.Y); }

pair<pll, pll> closest_pair(vector<pll> pts) {
  sort(pts.begin(), pts.end());
  auto compY = [&](pll a, pll b) { return a.Y != b.Y ? a.Y < b.Y : a.X < b.X; };
  auto compAns = [&](pair<pll, pll> a, pair<pll, pll> b) {
    return eval(a) < eval(b);
  };

  vector<pll> buf(pts.size());
  vector<pll> tmp;
  tmp.reserve(pts.size());
  pair<pll, pll> ans(pll(-1, -1), pll(1e9, 1e9));
  auto dc = [&](auto self, int l, int r) -> void {
    if (r - l <= 1)
      return;
    int mid = (l + r) / 2;
    int x_mid = pts[mid].X;
    self(self, l, mid);
    self(self, mid, r);
    ll d = eval(ans);
    merge(pts.begin() + l, pts.begin() + mid, pts.begin() + mid,
          pts.begin() + r, buf.begin() + l, compY);
    copy(buf.begin() + l, buf.begin() + r, pts.begin() + l);
    for (int i = l; i < r; i++)
      if ((pts[i].X - x_mid) * (pts[i].X - x_mid) < d)
        tmp.emplace_back(pts[i]);
    for (int i = 0; i < int(tmp.size()); i++) {
      for (int j = i + 1; j < int(tmp.size()) &&
                          (tmp[j].Y - tmp[i].Y) * (tmp[j].Y - tmp[i].Y) < d;
           j++) {
        ans = min(ans, make_pair(tmp[i], tmp[j]), compAns);
      }
    }
    tmp.clear();
  };
  dc(dc, 0, pts.size());
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;

  vector<pll> pts(n);
  for (int i = 0; i < n; i++)
    std::cin >> pts[i].X >> pts[i].Y;
  sort(pts.begin(), pts.end());

#ifdef DRAW
  std::cout << n << "\n";
  for (auto [x, y] : pts)
    std::cout << x << " " << y << "\n";
#endif

  vector<pair<int, int>> matching;
  vector<bool> matched(n);

  auto convert = [&](int num) {
    int id = num / 2;
    return std::make_pair(id, num % 2 == 0 ? matching[id].first
                                           : matching[id].second);
  };
  auto get_edge_val = [&](pair<int, int> p) {
    auto [u, v] = p;
    return abs(pts[u] - pts[v]);
  };

  auto augment = [&]() {
    vector<int> todo;
    vector<int> path;
    ld all_best = MAX;

    {
      vector<pll> remain;
      for (int i = 0; i < n; i++)
        if (!matched[i])
          remain.emplace_back(pts[i]);
      auto [v1, v2] = closest_pair(remain);
      int id1 = lower_bound(pts.begin(), pts.end(), v1) - pts.begin();
      int id2 = lower_bound(pts.begin(), pts.end(), v2) - pts.begin();
      path.emplace_back(id1);
      path.emplace_back(id2);
      all_best = abs(v1 - v2);
    }

    int t = matching.size();
    if (t)
      [&]() {
        vector dp(2 * t, vector<Info>(1 << t));
        vector<Info> closest(2 * t);
        for (int i = 0; i < 2 * t; i++) {
          auto [id, v] = convert(i);
          for (int j = 0; j < n; j++) {
            if (matched[j])
              continue;
            closest[i].insert(Item({abs(pts[v] - pts[j]), j}));
          }
          dp[i ^ 1][1 << id] = closest[i];
        }
        for (int mask = 1; mask < (1 << t); mask++) {
          for (int end = 0; end < 2 * t; end++) {
            auto [id, v] = convert(end);
            if (!(1 << id & mask))
              continue;
            for (int go = 0; go < 2 * t; go++) {
              auto [go_id, go_v] = convert(go);
              if (1 << go_id & mask)
                continue;
              int nxt = 1 << go_id | mask;
              dp[go ^ 1][nxt] =
                  dp[go ^ 1][nxt] +
                  dp[end][mask].add(abs(pts[v] - pts[go_v]) -
                                        get_edge_val(matching[id]),
                                    end);
            }
          }
        }
        ld best = MAX;
        int best_end = -1;
        int best_src = -1;
        int best_lst = -1;
        int best_mask = -1;
        for (int mask = 0; mask < (1 << t); mask++) {
          for (int end = 0; end < 2 * t; end++) {
            auto [id, v] = convert(end);
            if (!(1 << id & mask))
              continue;
            for (Item cand : dp[end][mask].items) {
              if (cand.label == -1)
                continue;
              for (Item lst : closest[end].items) {
                if (lst.label == -1)
                  continue;
                if (lst.label == cand.label)
                  continue;
                ld cost = cand.val + lst.val - get_edge_val(matching[id]);
                if (cost >= best)
                  continue;
                best = cost;
                best_end = end;
                best_src = cand.label;
                best_lst = lst.label;
                best_mask = mask;
              }
            }
          }
        }
        if (best >= all_best)
          return;
        all_best = best;

        path.clear();
        todo.clear();
        path.emplace_back(best_lst);
        int cur = best_mask;
        int cur_end = best_end;
        while (cur) {
          auto [id, v] = convert(cur_end);
          todo.emplace_back(id);
          path.emplace_back(v);
          path.emplace_back(convert(cur_end ^ 1).second);
          Item tmp = dp[cur_end][cur].get_by_label(best_src);
          int pre = tmp.src;
          cur ^= 1 << id;
          cur_end = pre;
        }

        path.emplace_back(best_src);
        reverse(path.begin(), path.end());
      }();
    matched[path[0]] = true;
    matched[path.back()] = true;
    vector<pair<int, int>> new_matching;
    ld change = 0;
#ifdef DRAW
    std::cout << "frame\n";
#endif
    for (int i = 0; i + 1 < int(path.size()); i += 2) {
      new_matching.emplace_back(path[i], path[i + 1]);
      change += get_edge_val(new_matching.back());
#ifdef DRAW
      std::cout << "+ " << path[i] << " " << path[i + 1] << "\n";
#endif
    }
    for (int i : todo) {
      change -= get_edge_val(matching[i]);
#ifdef DRAW
      std::cout << "- " << matching[i].first << " " << matching[i].second
                << "\n";
#endif
    }
    assert(int(new_matching.size()) == int(todo.size()) + 1);
    for (int i = 0; i < int(todo.size()); i++)
      matching[todo[i]] = new_matching[i];
    matching.emplace_back(new_matching.back());
  };

  for (int i = 1; i <= k; i++)
    augment();

#ifdef DRAW
  std::cout << "end\n";
#else
  ld ans = 0;
  for (auto [u, v] : matching) {
    ans += abs(pts[u] - pts[v]);
  }
  std::cout << std::fixed << std::setprecision(10) << ans << "\n";
#endif
}
