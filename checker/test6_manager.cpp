#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>
#include <string>
using namespace std;

int n;
FILE *ain, *aout, *bin, *bout;

int RAND(int x) {
    return (rand()*32768 + rand()) % x;
}
pair<int,int> test(int t) {
    char buf[1005];
    vector<int> xs;
    vector<int> ys;
    vector<string> results;
    for (int i=0; i<t; i++) {
        xs.push_back(RAND(n));
        ys.push_back(RAND(n));
    }

    fprintf(ain, "%d\n", t);
    for (int i=0; i<t; i++) {
        fprintf(ain, "%d\n", xs[i]);
    }
    fflush(ain);

    for (int i=0; i<t; i++) {
        fscanf(aout, "%s", buf);
        results.push_back(string(buf));
    }

    // B
    fprintf(bin, "%d\n", t);
    for (int i=0; i<t; i++) {
        fprintf(bin, "%d %s\n", ys[i], results[i].c_str());
    }
    fflush(bin);

    int correct = 0;
    int is_same = -1;
    int mxl = 0;
    for (int i=0; i<t; i++) {
        fscanf(bout, "%d", &is_same);
        if ((bool)is_same == (xs[i] == ys[i])) {
            correct++;
        }
        mxl = std::max((int)results[i].length()-2, mxl);
    }
    return pair<int,int> (correct, mxl);
}
int main(int argc, char *argv[]) {
    ain = fopen(argv[1], "w");
	aout = fopen(argv[2], "r");
    bin = fopen(argv[3], "w");
	bout = fopen(argv[4], "r");
    int seed;
    scanf("%d %d", &n, &seed);
    srand(seed);

    // secret token to identify the processes
    fprintf(ain, "A\n"); fflush(ain);
    fprintf(bin, "B\n"); fflush(bin);

    int block = 10000;
    int mxl = 0;
    int correct = 0;
    int tests = 100000;

    for (int i=0; i<tests / block; i++) {
        int x, y;
        tie(x, y) = test(block);
        correct += x;
        mxl = max(mxl, y);
    }

    double f = 1.0 / (double)std::max(1, mxl-20);
    printf("%.10lf\n", (double)correct/tests * f);
    fprintf(stderr, "correctness: %d/%d max_length=%d\n", correct, tests, mxl);

    fclose(ain);
    fclose(aout);
    fclose(bin);
    fclose(bout);
}
