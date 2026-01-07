#include "testlib.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

constexpr double EPS = 1e-6;
string INF = "infinity";

int main(int argc, char * argv[])
{
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("compare files as list of float numbers");
    registerTestlibCmd(argc, argv);

    int n = 0;
    while (!ans.eof())
    {
        std::string j = ans.readString();
        if (j == "" && ans.eof()) break;
        std::string p = ouf.readString();
        if (p == "" && ouf.eof()) quitf(_wa, "unexpected eof");
        n++;

        if (j == INF) {
            if (p != INF) quitf(_wa, "%d%s lines differ -  INF vs %s", n,
                    englishEnding(n).c_str(), p.c_str());
            continue;
        }

        double dblAnswer = stringToDouble(ans, j.c_str());
        double dblOutput = stringToDouble(ouf, p.c_str());
        if (fabs(dblAnswer - dblOutput) > max(1.0, dblAnswer) * EPS) {
            double error = fabs(dblAnswer - dblOutput) / max(1.0, dblAnswer);
            quitf(_wa, "%d%s lines differ - error %e > eps %e", n,
                    englishEnding(n).c_str(), error, EPS);
        }
    }

    if (n == 1) quitf(_ok, "single line");
    quitf(_ok, "%d lines", n);
}
