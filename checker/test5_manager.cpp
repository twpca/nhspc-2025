#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <algorithm>
using namespace std;

FILE *ain, *aout, *bin, *bout;

int RAND(int x) {
    return (rand()*32768 + rand()) % x;
}
int main(int argc, char *argv[]) {
    ain = fopen(argv[1], "w");
	aout = fopen(argv[2], "r");
    bin = fopen(argv[3], "w");
	bout = fopen(argv[4], "r");
    int n, seed;
    scanf("%d %d", &n, &seed);
    srand(seed);

    // secret token to identify the processes
    fprintf(ain, "A\n"); fflush(ain);
    fprintf(bin, "B\n"); fflush(bin);

    int mxl = 0;
    int correct = 0;
    int tests = 100000;
    char buf[1005];
    for (int i=0; i<tests; i++) {
        int x = RAND(n);
        int y = RAND(n);

        // A()
        fprintf(ain, "%d\n", x);
        fflush(ain);
        fscanf(aout, "%s", buf); // "01101"

        // B()
        int is_same = -1;
        fprintf(bin, "%d %s\n", y, buf); // 2 "01101"
        fflush(bin);
        fscanf(bout, "%d", &is_same);

        if ((bool)is_same == (x == y)) {
            correct++;
        }
        mxl = std::max((int)strlen(buf)-2, mxl);
    }

    double f = 1.0 / (double)std::max(1, mxl-20);
    printf("%.10lf\n", (double)correct/tests * f);
    fprintf(stderr, "correctness: %d/%d max_length=%d\n", correct, tests, mxl);

    fclose(ain);
    fclose(aout);
    fclose(bin);
    fclose(bout);
}
