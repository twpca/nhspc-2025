#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <utility>

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int MIN_T = 1;
constexpr int MAX_T[] = {1000, 1, 1000, 1000};
constexpr int MIN_N = 1;
constexpr int MAX_N[] = {500, 500, 50, 500};


int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int t = inf.readInt(MIN_T, MAX_T[s], "t");
    inf.readChar('\n');

    for(int i = 0; i < t; i++){
        int n = inf.readInt(MIN_N, MAX_N[s], "n of case " + std::to_string(i));
        inf.readSpace();
        int p = inf.readInt(0, n, "p of case " + std::to_string(i));
        inf.readSpace();
        int q = inf.readInt(0, n, "q of case " + std::to_string(i));
        inf.readSpace();
        int r = inf.readInt(0, n, "r of case " + std::to_string(i));
        inf.readChar('\n');

        ensuref(p + q + r <= n, std::string("p + q + r > n on case " + std::to_string(i)).c_str());
        ensuref(p + q + r >= 1, std::string("p + q + r = 0 on case " + std::to_string(i)).c_str());

        if(s == 1){
            ensuref(p == 0, std::string("p != 0 on case " + std::to_string(i)).c_str());
        }
    }
    inf.readEof();

    return 0;
}
