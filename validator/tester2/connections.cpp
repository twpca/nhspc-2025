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
constexpr int MAX_K[] = {18, 1, 10, 2, 2, 15, 15, 18};
constexpr int MIN_N = 2;
constexpr int MAX_N[] = {100'000, 100'000, 20, 3'000, 100'000, 3'000, 100'000, 100'000};
constexpr int MAX_C = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readSpace();
    int k = inf.readInt(MIN_K, MAX_K[s], "k");
    inf.readChar('\n');
    ensuref(2 * k <= n, "2k > n");

    std::set<std::pair<int, int>> vis;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, MAX_C, "x_" + std::to_string(i));
        inf.readSpace();
        int y = inf.readInt(0, MAX_C, "y_" + std::to_string(i));
        inf.readChar('\n');
        ensuref(vis.emplace(x, y).second, "duplicate points");
    }
    inf.readEof();

    return 0;
}
