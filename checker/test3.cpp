#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

string answers[] = {
    "2",
    "3",
    "1",
    "8.5",
    "82641735",
    "2367156",
    "728"
};
int special[] = {
    0,
    0,
    0,
    0,
    2,
    1,
    0
};

bool same_charset(string out, string ans) {
    set<char> co, ca;
    for (int i=0; i<(int)ans.length(); i++) {
        ca.insert(ans[i]);
    }
    for (int i=0; i<(int)out.length(); i++) {
        co.insert(out[i]);
    }

    return ca == co && out.length() == ans.length();
}

double pair_ord(string out, string ans) {
    if (!same_charset(out, ans)) {
        return 0.0;
    }

    int n = ans.length();
    map<char, int> pos;
    for (int i=0; i<n; i++) {
        pos[ans[i]] = i + 1;
    }


    int cnt = 0;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            int pi = pos[out[i]];
            int pj = pos[out[j]];
            if (pi < pj) {
                cnt++;
            }
        }
    }
    return (double)cnt / (double)(n*(n-1)/2);
}

double calc_ord(string out, string ans) {
    if (!same_charset(out, ans)) {
        return 0.0;
    }

    int n = out.length();
    int cnt = 0;
    for (int i=0; i<n; i++) {
        if (out[i] == ans[i]) {
            cnt++;
        }
    }
    return (double)cnt / (double)n;
}

int main(int argc, char * argv[]) {
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("Check for test3");
    registerTestlibCmd(argc, argv);

    int task = inf.readInt();
    string ans = answers[task - 1];
    string out = ouf.readToken();

    double score;
    switch (special[task - 1]) {
    case 1:
        score = calc_ord(out, ans);
        if (score == 1.0) {
            quitf(_ok, "%s is correct", out.c_str());
        }
        if (score == 0.0) {
            quitf(_wa, "%s is incorrect", out.c_str());
        }
        printf("%.9lf\n", score);
        quitp(score, "score = %.9lf", score);
        break;
    case 2:
        score = pair_ord(out, ans);
        if (score == 1.0) {
            quitf(_ok, "%s is correct", out.c_str());
        }
        if (score == 0.0) {
            quitf(_wa, "%s is incorrect", out.c_str());
        }
        printf("%.9lf\n", score);
        quitp(score, "score = %.9lf", score);
        break;
    default:
        if (ans != out) {
            quitf(_wa, "%s is incorrect.", out.c_str());
        } else {
            quitf(_ok, "%s is correct.", out.c_str());
        }
        break;
    }
}
