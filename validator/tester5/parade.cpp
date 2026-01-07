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

constexpr int MIN_K = 1;
constexpr int MAX_K[] = {20, 1, 20, 20, 20};
constexpr int MIN_N = 1;
constexpr int MAX_N[] = {100'000, 100'000, 500, 100'000, 100'000};
constexpr int MIN_C = 1;
constexpr int MAX_C = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(MIN_N, MAX_N[s], "N");
    inf.readSpace();
    int k = inf.readInt(MIN_K, MAX_K[s], "K");
    inf.readChar('\n');
    ensuref(k <= n, "K <= N");

    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(MIN_C, MAX_C, "l_" + std::to_string(i));
        inf.readSpace();
        int r = inf.readInt(MIN_C, MAX_C, "r_" + std::to_string(i));
        inf.readChar('\n');
		ensuref(l <= r, "l_i <= r_i");
		if(s == 3) ensuref(l == r, "l_i == r_i");
        if(s == 3) ensuref(r <= 100000, "r_i <= 100000");
    }
    inf.readEof();

    return 0;
}

