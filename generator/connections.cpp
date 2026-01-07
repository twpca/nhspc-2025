#include "testlib.h"
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <set>
#include <cassert>
#include <cstdlib>
#include <cmath>

const int MAXC = 1'000'000'000;

class Mat2 {
public:
    int val[2][2];
    Mat2(int a, int b, int c, int d) {
        val[0][0] = a;
        val[0][1] = b;
        val[1][0] = c;
        val[1][1] = d;
    }
};

typedef std::pair<int, int> Point;

Point operator-(const Point &a, const Point &b) {
    return std::make_pair(a.first - b.first, a.second - b.second);
}

Point operator*(const Point &a, const int &b) {
    return std::make_pair(a.first * b, a.second * b);
}

long long cross(const Point &a, const Point &b) {
    return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

int sign(const long long &a) {
    return a == 0 ? 0 : a > 0 ? 1 : -1;
}

int ori(Point a, Point b, Point c) {
    return sign(cross(b - a, c - a)); 
}

class Testcase {
    int k;
    std::vector<Point> points;
    void resize(int n) {
        assert(n <= int(points.size()));
        points.resize(n);
    }
public:
    Testcase(): k(0) {}
    Testcase(int _k, std::vector<Point> _points): k(_k), points(_points) {
        shuffle(points.begin(), points.end());
    }
    Testcase(int _k, std::vector<Point> _points, int n): k(_k), points(_points) {
        shuffle(points.begin(), points.end());
        resize(n);
    }
    template<class InputIt>
    Testcase(int _k, InputIt first, InputIt last): k(_k), points(first, last) {
        shuffle(points.begin(), points.end());
    }
    template<class InputIt>
    Testcase(int _k, InputIt first, InputIt last, int n): k(_k), points(first, last) {
        shuffle(points.begin(), points.end());
        resize(n);
    }
    std::vector<Point> get_points() {
        return points;
    }
    void random_shift(int maxc) {
        int xl = -maxc, xr = maxc; 
        int yl = -maxc, yr = maxc;
        for (auto [x, y] : points) {
            xl = std::max(xl, -x);
            yl = std::max(yl, -y);
            xr = std::min(xr, maxc - x);
            yr = std::min(yr, maxc - y);
        }
        int dx = rnd.next(xl, xr);
        int dy = rnd.next(yl, yr);
        for (auto &[x, y] : points) {
            x += dx;
            y += dy;
        }
    }
    void mul(Mat2 mat) {
        for (auto &[x, y] : points) {
            int nx = x * mat.val[0][0] + y * mat.val[1][0];
            int ny = x * mat.val[0][1] + y * mat.val[1][1];
            x = nx, y = ny;
        }
    }
    void print() {
        std::ios::sync_with_stdio(0), std::cin.tie(0); 
        std::cout << points.size() << " " << k << "\n";
        for (auto [x, y] : points)
            std::cout << x << " " << y << "\n";
    }
};

Testcase generator_random() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int min_c = opt<int>("min_c", 0);
    int max_c = opt<int>("max_c", MAXC);

    if (1ll * (max_c - min_c + 1) * (max_c - min_c + 1) <= 10000000) {
        std::vector<Point> pool;
        pool.reserve((max_c - min_c + 1) * (max_c - min_c + 1));
        for (int x = min_c; x <= max_c; ++x)
            for (int y = min_c; y <= max_c; ++y)
                pool.emplace_back(x, y);
        return Testcase(k, pool, n);
    }
    else {
        std::set<Point> points;
        while (int(points.size()) < n) {
            int x = rnd.next(min_c, max_c);
            int y = rnd.next(min_c, max_c);
            points.emplace(x, y);
        }
        return Testcase(k, points.begin(), points.end());
    }
}

Testcase pattern_long_path(int k, int base_length = opt<int>("base_length", 1)) {
    int current_length = base_length;
    std::vector<Point> points;
    Point left_point(0, 0);
    Point right_point(current_length, 0);
    points.emplace_back(left_point);
    points.emplace_back(right_point);
    double alter = base_length;
    while (int(points.size()) < 2 * k) {
        current_length = (int)ceil(alter);
        left_point = std::make_pair(left_point.first - 1, left_point.second - current_length);
        right_point = std::make_pair(right_point.first + 1, right_point.second + current_length);
        alter = -alter;
        alter += 2 * sqrt((long long)current_length * current_length + 1);
        points.emplace_back(left_point);
        points.emplace_back(right_point);
        current_length = (int)ceil(alter);
        left_point = std::make_pair(left_point.first - current_length, left_point.second);
        right_point = std::make_pair(right_point.first + current_length, right_point.second);
        alter = -alter;
        alter += 2 * current_length;
        points.emplace_back(left_point);
        points.emplace_back(right_point);
    }
    points.resize(2 * k);
    return Testcase(k, points);
}

Testcase pattern_many_long_path(int real_k, 
        int num = opt<int>("num"), 
        int total_k = opt<int>("total_k"), 
        int base_length = opt<int>("base_length", 1), 
        int distance = opt<int>("distance", 1000)) {
    std::vector<int> k = rnd.partition(num, total_k, 1);
    std::vector<std::pair<int, int>> pts;
    for (int i = 0; i < num; i++) {
        auto t = pattern_long_path(k[i], base_length);
        for (auto p : t.get_points())
            pts.emplace_back(std::make_pair(p.first, p.second + i * distance));
    }
    return Testcase(real_k, pts);
}

Testcase pattern_flip_path(int k, int base_length = opt<int>("base_length", 1)) {
    int current_length = base_length;
    std::vector<std::pair<int, int>> points;
    std::pair<int, int> left_point(0, 0);
    std::pair<int, int> right_point(current_length, 0);
    points.emplace_back(left_point);
    points.emplace_back(right_point);
    while (int(points.size()) < 2 * k) {
        left_point = std::make_pair(left_point.first - 1, left_point.second - current_length);
        right_point = std::make_pair(right_point.first + 1, right_point.second + current_length);
        points.emplace_back(left_point);
        points.emplace_back(right_point);
        left_point = std::make_pair(left_point.first - current_length, left_point.second);
        right_point = std::make_pair(right_point.first + current_length, right_point.second);
        points.emplace_back(left_point);
        points.emplace_back(right_point);
        current_length += 1;
    }
    points.resize(2 * k);
    return Testcase(k, points);
}

Testcase pattern_many_flip_path(int real_k, 
        int num = opt<int>("num"), 
        int fix_k = opt<int>("fix_k"), 
        int base_length = opt<int>("base_length", 1), 
        int distance = opt<int>("distance", 1000)) {
    std::vector<std::pair<int, int>> pts;
    for (int i = 0; i < num; i++) {
        auto t = pattern_flip_path(fix_k, base_length);
        for (auto p : t.get_points())
            pts.emplace_back(std::make_pair(p.first, p.second + i * distance));
    }
    return Testcase(real_k, pts);
}

Testcase generator_long_path() {
    int k = opt<int>("k");
    return pattern_long_path(k);
}

Testcase generator_grid() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int d = opt<int>("d");
    int radius = opt<int>("radius");
    int grid_c = opt<int>("grid_c", MAXC / 10);
    std::string pattern_name = opt<std::string>("pattern_name", "");

    Testcase special_pattern;
    if (pattern_name == "long_path") special_pattern = pattern_long_path(k);
    if (pattern_name == "many_long_path") special_pattern = pattern_many_long_path(k);
    if (pattern_name == "flip_path") special_pattern = pattern_flip_path(k);
    if (pattern_name == "many_flip_path") special_pattern = pattern_many_flip_path(k);
   
    special_pattern.random_shift(grid_c);
    auto points = special_pattern.get_points();
    std::set<Point> banned;
    for (auto [x, y] : points) {
        banned.emplace(x / d, y / d); 
        banned.emplace((x + d - 1) / d, y / d); 
        banned.emplace(x / d, (y + d - 1) / d); 
        banned.emplace((x + d - 1) / d, (y + d - 1) / d);
    }

    while (int(points.size()) < n) {
        int x, y;
        do {
            x = rnd.next(0, grid_c / d);
            y = rnd.next(0, grid_c / d);
        } while (!banned.emplace(x, y).second);
        x *= d;
        x += rnd.next(-radius, radius);
        y *= d;
        y += rnd.next(-radius, radius);
        points.emplace_back(x, y);
    }

    return Testcase(k, points.begin(), points.end());
}

/*
 * .
 *  .
 *   .
 *    . .
 *    ^  .
 *    |   .
 *   mid   .
 */
Testcase generator_slope() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int gap = opt<int>("gap");
    int mid = opt<int>("mid"); // 0-based
    
    std::vector<Point> pts;
    int y = 0;
    for (int i = 0; i < n; i++) {
        pts.emplace_back(std::make_pair(i * gap, y * gap));
        if (i != mid) y--;
    }

    return Testcase(k, pts);
}

Testcase luogu_hack() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int lx = opt<int>("lx", 158);
    int ly = opt<int>("ly", 158);
    int rndcosl = opt<int>("rndcosl", 1);
    int rndcosr = opt<int>("rndcosr", 1);
    int rndsinl = opt<int>("rndsinl", 0);
    int rndsinr = opt<int>("rndsinr", 0);

    std::vector<Point> points;

    for (int i = 0, x = -3 * lx; i < 2 * lx + 1; ++i, x += 3)
        for (int j = 0, y = 2; j < ly; ++j, y += 3)
            points.emplace_back(x, y);
    for (int i = 0, x = -3 * lx; i < 2 * lx + 1; ++i, x += 3)
        for (int j = 0, y = -2; j < ly; ++j, y -= 3)
            points.emplace_back(x, y);
    std::cerr << points.size() << "\n";
    if (int(points.size()) > n - 2) {
        shuffle(points.begin(), points.end());
        points.resize(n - 2);
    }
    points.emplace_back(-1, 0);
    points.emplace_back(1, 0);

    int cosv = rnd.next(rndcosl, rndcosr);
    int sinv = rnd.next(rndsinl, rndsinr);
    Testcase res = Testcase(k, points);
    res.mul(Mat2(cosv, -sinv, sinv, cosv));
    return res;
}

struct Interval {
    double l, r;
    Interval(double _l, double _r): l(_l), r(_r) {}
    bool operator<(const Interval &rhs) const {
        return std::make_pair(l, r) < std::make_pair(rhs.l, rhs.r);
    }
};

Testcase cover_hack() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int C = opt<int>("C", 1000);
    int upper = opt<int>("upper", 1000);
    double ratio = opt<double>("ratio", 0.9);
    int rndcosl = opt<int>("rndcosl", 1);
    int rndcosr = opt<int>("rndcosr", 1);
    int rndsinl = opt<int>("rndsinl", 0);
    int rndsinr = opt<int>("rndsinr", 0);

    std::vector<std::pair<Interval, Point>> pool;

    Point base(0, 0), dir(-1, 0);

    auto get_angle = [&](Point d) {
        return atan2(d.second, d.first);  
    };

    auto add_point = [&](int x, int y) {
        Point pt = Point(x, y);
        int d = ori(base, pt, dir);
        if (d == 0) return false;
        if (d > 0) {
            pool.emplace_back(Interval(get_angle(pt - dir), get_angle(pt - base)), pt);
        }
        else {
            pool.emplace_back(Interval(get_angle(pt - base), get_angle(pt - dir)), pt);
        }
        return true;
    };

    for (int i = -C; i <= C; i += 2)
        for (int j = -C; j <= C; j += 2)
            add_point(i, j);
    for (auto [itv, pt] : pool)
        assert(itv.l <= itv.r);
    std::sort(pool.begin(), pool.end());
    std::vector<Point> points({base, dir});
    const double pi = acos(-1);
    for (int u = 0; u < upper; ++u) {
        std::vector<std::pair<Interval, Point>> nxtpool;
        int count = 0, flag = 0;
        double sum = 0;
        double ing = pi * (1 - ratio);
        double cur = -pi + ing;
        for (int i = 0, j = 0; i < int(pool.size()) && int(points.size()) < n; i = j) {
            int best = j++;
            while (j < int(pool.size()) && pool[j].first.l <= cur) {
                if (pool[best].first.r < pool[j].first.r)
                    best = j;
                ++j;
            }
            if (pool[best].first.l <= cur)
                sum += pool[best].first.r - cur;
            else
                sum += pool[best].first.r - pool[best].first.l;
            cur = pool[best].first.r;
            if (!flag && cur > -ing) { 
                cur = ing;
                flag = 1;
            }
            if (flag == 1 && cur > pi - ing) {
                 j = pool.size();
            }
            points.push_back(pool[best].second);
            for (int p = i; p < j; ++p)
                if (p != best)
                    nxtpool.push_back(pool[p]);
            ++count;
        }
        pool.swap(nxtpool);
        //std::cerr << sum << " " << count << "\n";
        if (int(points.size()) >= n) break;
    }

    int cosv = rnd.next(rndcosl, rndcosr);
    int sinv = rnd.next(rndsinl, rndsinr);
    Testcase res = Testcase(k, points);
    res.mul(Mat2(cosv, -sinv, sinv, cosv));
    return res;
}

Testcase construct_hack() {
    int n = opt<int>("n");
    int k = opt<int>("k");
    int C = opt<int>("C", 100);
    int D = opt<int>("D", 400);
    int rndcosl = opt<int>("rndcosl", 1);
    int rndcosr = opt<int>("rndcosr", 1);
    int rndsinl = opt<int>("rndsinl", 0);
    int rndsinr = opt<int>("rndsinr", 0);
    int option = opt<int>("option", 1);

    std::vector<Point> angle;
    if (option == 1) {
        angle.emplace_back(0, 1);
        angle.emplace_back(1, 0);
        angle.emplace_back(1, 1);
        angle.emplace_back(1, -1);
        angle.emplace_back(0, -1);
        angle.emplace_back(-1, 0);
        angle.emplace_back(-1, 1);
        angle.emplace_back(-1, -1);
    }
    else if (option == 2) {
        angle.emplace_back(0, 1);
        angle.emplace_back(1, 0);
        angle.emplace_back(2, 1);
        angle.emplace_back(1, 2);
        angle.emplace_back(2, -1);
        angle.emplace_back(-1, 2);
        angle.emplace_back(0, -1);
        angle.emplace_back(-1, 0);
        angle.emplace_back(-2, 1);
        angle.emplace_back(1, -2);
        angle.emplace_back(-2, -1);
        angle.emplace_back(-1, -2);
    }
    else {
        assert(0);
    }
    int asz = angle.size();

    std::vector<Point> points;
    for (auto &dir : angle) {
        for (int i = 1; i <= (n - 2 + asz - 1) / asz; ++i)
            points.push_back(dir * i * D);  
    }
    std::cerr << points.size() << "\n";
    if (int(points.size()) > n - 2) {
        shuffle(points.begin(), points.end());
        points.resize(n - 2);
    }
    points.emplace_back(-C, -C + 1);
    points.emplace_back(C, C - 1);

    int cosv = rnd.next(rndcosl, rndcosr);
    int sinv = rnd.next(rndsinl, rndsinr);
    Testcase res = Testcase(k, points);
    res.mul(Mat2(cosv, -sinv, sinv, cosv));
    return res;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    std::string generator_str = argv[1];

    std::map<std::string, std::function<Testcase()>> generator_func;
    generator_func["random"] = generator_random;
    generator_func["grid"] = generator_grid;
    generator_func["long_path"] = generator_long_path;
    generator_func["slope"] = generator_slope;
    generator_func["luogu_hack"] = luogu_hack;
    generator_func["cover_hack"] = cover_hack;
    generator_func["construct_hack"] = construct_hack;

    auto testcase = generator_func[generator_str]();
    testcase.random_shift(MAXC);
    testcase.print();
}
