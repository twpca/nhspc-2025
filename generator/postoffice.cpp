#include <bits/stdc++.h>

#include "testlib.h"

using ll = long long;
using namespace std;

void gen(char fn[], int max_n, int max_s, int max_k, int max_x) {
    FILE *f = fopen(fn, "w");

    int n = rnd.next(2, max_n);
    int k;
    if (max_s == 0) {
        k = rnd.next(1, min(max_k, n));
    } else {
        k = rnd.next(1, min(max_k, n));
    }

    fprintf(f, "%d %d\n", n, k);
    set<int> vis;
    vector<int> a(n);

    for (int &i : a) {
        do {
            i = rnd.next(1, max_x);
        } while (vis.count(i) || i % 10 == 1);
        vis.emplace(i);
    }

    vector<int> b(n);
    for (int &i : b) {
        if (max_s != 0)
            i = rnd.next(0, k - 1);
        else
            i = 0;
    }


    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            fprintf(f, "%d %d ", a[i], b[i]);
        else
            fprintf(f, "%d %d\n", a[i], b[i]);
    }

    return;
}

void gen_mx(char fn[], int max_n, int max_s, int max_k, int max_x) {
    FILE *f = fopen(fn, "w");

    int n = max_n;
    int k = n - 1;

    fprintf(f, "%d %d\n", n, k);
    set<int> vis;
    vector<int> a(n);

    for (int &i : a) {
        do {
            i = rnd.next(1, max_x);
        } while (vis.count(i));
        vis.emplace(i);
    }

    vector<int> b(n);
    for (int &i : b) {
        i = sqrt(k) * 2;
    }


    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            fprintf(f, "%d %d ", a[i], b[i]);
        else
            fprintf(f, "%d %d\n", a[i], b[i]);
    }

    return;
}

void gen_mxx(char fn[], int max_n, int max_s, int max_k, int max_x) {
    FILE *f = fopen(fn, "w");

    int n = max_n;
    int k = n - 1;
    fprintf(f, "%d %d\n", n, k);
    set<int> vis;
    vector<int> a(n);

    int cnt = 0;
    int cur = 1;

    for (int &i : a) {
        i = 1;
    }
    a.back() = max_x;

    vector<int> b(n);
    for (int &i : b) {
        i = cnt++;
    }
    b.back() -= 1;
    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            fprintf(f, "%d %d ", a[i], b[i]);
        else
            fprintf(f, "%d %d\n", a[i], b[i]);
    }

    return;
}

void gen_mi(char fn[], int max_n, int max_s, int max_k, int max_x) {
    FILE *f = fopen(fn, "w");

    int n = max_n;
    int k = 1;

    fprintf(f, "%d %d\n", n, k);
    set<int> vis;
    vector<int> a(n);

    for (int &i : a) {
        do {
            i = rnd.next(1, max_x);
        } while (vis.count(i));
        vis.emplace(i);
    }

    vector<int> b(n);
    for (int &i : b) {
        i = 0;
    }


    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            fprintf(f, "%d %d ", a[i], b[i]);
        else
            fprintf(f, "%d %d\n", a[i], b[i]);
    }

    return;
}
void gen0(char fn[], int max_n, int max_s, int max_k, int max_x) {
    FILE *f = fopen(fn, "w");

    int n = max_n;
    int k = sqrt(min(max_k, max_s + 1));

    fprintf(f, "%d %d\n", n, k);
    set<int> vis;
    vector<int> a(n);

    for (int &i : a) {
        i = rnd.next(1, k);
    }

    vector<int> b(n);
    for (int &i : b) {
        i = 0;
    }


    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            fprintf(f, "%d %d ", a[i], b[i]);
        else
            fprintf(f, "%d %d\n", a[i], b[i]);
    }

    return;
}



int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int c = atoi(argv[1]);
    int max_n = atoi(argv[2]);
    int max_s = atoi(argv[3]);
    int max_k = atoi(argv[4]);
    int max_x = atoi(argv[5]);

    char f[40];
    for (int i = 1; i <= 15; i++) {
        sprintf(f, "%d_%02d.in", c, i);
        gen(f, max_n, max_s, max_k, max_x);
    }

    if (max_k != 1 && max_s != 0){
        sprintf(f, "%d_%02d.in", c, 16);
        gen_mx(f, max_n, max_s, max_k, max_x);
        sprintf(f, "%d_%02d.in", c, 17);
        gen_mi(f, max_n, max_s, max_k, max_x);
        sprintf(f, "%d_%02d.in", c, 18);
        gen_mxx(f, max_n, max_s, max_k, max_x);
        sprintf(f, "%d_%02d.in", c, 19);
        gen0(f, max_n, max_s, max_k, max_x);
    } else if (max_s != 0) {
        sprintf(f, "%d_%02d.in", c, 16);
        gen0(f, max_n, max_s, max_k, max_x);
    }

}

