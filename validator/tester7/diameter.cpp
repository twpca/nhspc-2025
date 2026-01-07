#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <utility>

#include "testlib.h"
using namespace std;

int subtask(int argc, char **argv) {
    for (int i = 0; i + 1 < argc; i++) {
        if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
        }
    }
    abort();
}

constexpr int MIN_N = 1;
constexpr int MAX_N1[] = {2000, 400, 2000, 2000, 2000};
constexpr int MAX_N2[] = {2000, 1, 2000, 2000, 2000};
constexpr int MIN_M = 0;
constexpr int MAX_M1[] = {4'000'000, 400, 4'000'000, 4000, 4'000'000};
constexpr int MAX_M2[] = {4'000'000, 0, 4'000'000, 4000, 4'000'000};

int matrix1[2000+1][2000+1] = {};
int matrix2[2000+1][2000+1] = {};

int dfs(int node, int parent, vector<int> adj[], vector<bool> &visited, int n, bool &is_cyclic) {
    visited[node] = true;
    int size = 1;

    for(int neighbor : adj[node]) {
        if(!visited[neighbor]) {
            size += dfs(neighbor, node, adj, visited, n, is_cyclic);
        } else if(neighbor != parent) {
            is_cyclic = true;
        }
    }

    return size;
}



int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n1 = inf.readInt(MIN_N, MAX_N1[s], "n1");
    int m1 = 0;
    inf.readChar('\n');

    vector<int> adj1[n1+1];

    for(int i = 1; i <= n1; i++) {
        for(int j = 1; j < n1; j++) {
            char e = inf.readChar();
            ensuref(e == '0' || e == '1', "Expected '0' or '1'");
            matrix1[i][j] = e - '0';
            if(e == '1'){
                adj1[i].push_back(j);
                m1++;
            }
        }
        char e = inf.readChar();
        ensuref(e == '0' || e == '1', "Expected '0' or '1'");
        inf.readChar('\n');
        matrix1[i][n1] = e - '0';
        if(e == '1'){
            adj1[i].push_back(n1);
            m1++;
        }
    } 

    m1 /= 2;
    ensuref(m1 <= MAX_M1[s], "number of edges in first graph exceeds the limit");

    for(int i=1; i <= n1; i++) {
        ensuref(matrix1[i][i] == 0, "self-loops are not allowed in first matrix");
    }

    for(int i = 1; i <= n1; i++) {
        for(int j = 1; j <= n1; j++) {
            ensuref(matrix1[i][j] == matrix1[j][i], "first matrix must be symmetric");
        }
    }

    // subtask 2 must be no cycles
    if(s == 2) {
        ensuref(m1 == n1 - 1, "in subtask 2 first graph must be a tree");
        vector<bool> visited(n1+1, false);
        bool is_cyclic = false;
        int component_size = dfs(1, -1, adj1, visited, n1, is_cyclic);
        ensuref(!is_cyclic, "in subtask 2 first graph must be no cycles");
        ensuref(component_size == n1, "in subtask 2 first graph must be connected");
    }

    int n2 = inf.readInt(MIN_N, MAX_N2[s], "n2");
    int m2 = 0;
    inf.readChar('\n');

    vector<int> adj2[n2+1];

    for(int i = 1; i <= n2; i++) {
        for(int j = 1; j < n2; j++) {
            char e = inf.readChar();
            ensuref(e == '0' || e == '1', "Expected '0' or '1'");
            matrix2[i][j] = e - '0';
            if(e == '1'){
                adj2[i].push_back(j);
                m2++;
            }
        }
        char e = inf.readChar();
        ensuref(e == '0' || e == '1', "Expected '0' or '1'");
        inf.readChar('\n');
        matrix2[i][n2] = e - '0';
        if(e == '1'){
            adj2[i].push_back(n2);
            m2++;
        }
    } 

    m2 /= 2;
    ensuref(m2 <= MAX_M2[s], "number of edges in second graph exceeds the limit");

    for(int i=1; i <= n2; i++) {
        ensuref(matrix2[i][i] == 0, "self-loops are not allowed in second matrix");
    }

    for(int i = 1; i <= n2; i++) {
        for(int j = 1; j <= n2; j++) {
            ensuref(matrix2[i][j] == matrix2[j][i], "second matrix must be symmetric");
        }
    }

    // subtask 2 must be no cycles
    if(s == 2) {
        ensuref(m2 == n2 - 1, "in subtask 2 second graph must be a tree");
        vector<bool> visited(n2+1, false);
        bool is_cyclic = false;
        int component_size = dfs(1, -1, adj2, visited, n2, is_cyclic);
        ensuref(!is_cyclic, "in subtask 2 second graph must be no cycles");
        ensuref(component_size == n2, "in subtask 2 second graph must be connected");
    }

    inf.readEof();
    return 0;
}
