#include <bits/stdc++.h>
using namespace std;

const int MX_N = 100'000;

struct Gen{
    Gen() = default;
    constexpr void next() noexcept{
        ++subtask, file = 0;
    }
    void gen(const string& input){
        char fn[32];
        sprintf(fn, "%d_%02d.in", subtask, ++file);
        FILE *fout = fopen(fn, "wb");
        fprintf(fout, "%ld\n", input.length());
        fprintf(fout, "%s\n", input.c_str());
        fclose(fout);
    }
    int subtask = 0, file = 0;
};

mt19937_64 Rng(107);
using Unif = std::uniform_int_distribution<>;
string simple_regular_randomize(int n) {
    assert(n % 2 == 0 && n >= 0);
    bernoulli_distribution coin(0.49);

    string s;
    int half = n / 2;
    int open = 0, close = 0;
    for (int i = 0; i < n; ++i) {
        bool can_open = open < half;
        bool can_close = close < open;

        if (can_open && (can_close ? coin(Rng) : true))
            s += '(', ++open;
        else
            s += ')', ++close;
    }

    assert(open == close);
    return s;
}

int main() {
    Gen g;
    g.next();

    // 1
    {
        vector<int> n_left({16237, 99219, 0, 73864, 236, 84464, 44986, MX_N, 26178, 62922});
        for (int i : n_left)
            g.gen(string(i, '(') + string(Unif(0, MX_N - i)(Rng), ')'));

        g.next();
    }

    // 2
    {
        vector<string> inputs;
        inputs.emplace_back(simple_regular_randomize(9802));
        inputs.emplace_back(simple_regular_randomize(66156));
        inputs.emplace_back(simple_regular_randomize(MX_N));

        for (string todo : {")(", "((", "))"}) {
            for (int i = 0; i < 2; ++i) {
                while (1) {
                    int sz = MX_N - Unif(1, 3000)(Rng) * 2;
                    string tmp = simple_regular_randomize(sz);
                    int u = Unif(0, sz - 1)(Rng), v = Unif(u + 1, sz)(Rng);
                    tmp.insert(tmp.begin() + v, todo[1]);
                    tmp.insert(tmp.begin() + u, todo[0]);


                    int removed = 0, cnt = 0;
                    for (char ch : tmp) {
                        if (ch == '(') ++cnt;
                        else --cnt;
                        if (cnt < 0) ++removed, ++cnt;
                    }

                    if (removed + cnt != 0) {
                        inputs.emplace_back(tmp);
                        break;
                    }
                }
            }
        }

        shuffle(inputs.begin(), inputs.end(), Rng);
        for (string input : inputs)
            g.gen(input);

        g.next();
    }

    // 3
    {
        Unif len_dist(MX_N - 1000, MX_N);
        bernoulli_distribution coin(0.5);

        for (int t = 0; t < 10; ++t) {
            int n = len_dist(Rng);
            string s;
            s.resize(n);
            for (int i = 0; i < n; ++i)
                s[i] = coin(Rng) ? '(' : ')';
            g.gen(s);
        }
    }
}
