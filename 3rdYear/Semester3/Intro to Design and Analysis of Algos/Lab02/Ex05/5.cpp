#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void readFile(int& n, vector<vector<int>>& graph, string& filePath, int& start) {
    ifstream fin(filePath);

    fin >> n;
    graph.resize(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> graph[i][j];
        }
    }

    fin >> start;

    fin.close();
}

void printCycle(const vector<int>& path) {
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;
}

bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& path, int pos, int n, int start) {
    if (graph[path[pos - 1]][v] == 0) {
        return false;
    }

    if (pos == n && v != start) {
        return false;
    }

    for (int i = 0; i < pos; ++i) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

bool hamCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos, int n, int start) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1) {
            return true;
        } else {
            return false;
        }
    }

    for (int v = 0; v < n; v++) {
        if (isSafe(v, graph, path, pos, n, start)) {
            path[pos] = v;

            if (hamCycleUtil(graph, path, pos + 1, n, start)) {
                return true;
            }

            path[pos] = -1;
        }
    }

    return false;
}

void hamCycle(vector<vector<int>>& graph, int start, int n) {
    vector<int> path(n, -1);
    path[0] = start;

    if (hamCycleUtil(graph, path, 1, n, start)) {
        printCycle(path);
    } else {
        cout << "No solution" << endl;
    }
}

int main() {
    string filePath = "5.txt";
    int n, start;
    vector<vector<int>> graph;

    readFile(n, graph, filePath, start);
    hamCycle(graph, start, n);

    return 0;
}