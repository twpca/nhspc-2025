#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

string secret = "SECRET!!!!";

int main(int argc, char * argv[]) {
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("Check for test4");
    registerTestlibCmd(argc, argv);


    string oc = ouf.readToken(secret);
    string validation = ouf.readToken();
    double score = ouf.readDouble();
    if (validation != "ok") {
        quitf(_wa, "wa");
    }

    if (validation == "ok" && score == 1.0) {
        quitf(_ok, "ok");
    } else {
        printf("%.9lf\n", score);
        quitp(score, "score = %.9lf", score);
    }
}
