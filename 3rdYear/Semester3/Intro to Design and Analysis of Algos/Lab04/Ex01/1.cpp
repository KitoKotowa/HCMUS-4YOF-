#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


void readFile(string& filePath, int& n, vector<vector<int>>& adj) {
    ifstream fin(filePath);

    fin >> n;
    adj.resize(n+1);
    
    string line;
    getline(fin, line); 

    for (int i = 1; i <= n; ++i) {
        getline(fin, line);
        istringstream iss(line);
        int neighbor;
        iss >> neighbor;

        adj[i] = vector<int>(neighbor);
        for (int j = 0; j < neighbor; ++j){
            iss >> adj[i][j];
        }
    }

    fin.close();
}

void printAdjList(int n, const vector<vector<int>>& adj) {
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i+1 << ": ";
        for (int neighbor : adj[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

vector<int> TopologicalSort(int& n, const vector<vector<int>>& adj) {
    vector<int> indegree(n+1, 0);
    queue<int> Q;
    vector<int> vec;

    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    for (int v = 1; v <= n; ++v) {
        if (indegree[v] == 0) {
            Q.push(v); 
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vec.push_back(u);
        for (int v : adj[u]) {
            --indegree[v];
            if (indegree[v] == 0) {
                Q.push(v);
            }
        }
    }
    
    if (vec.size() != n)
        cout << "Graph has a cycle" << endl;

    return vec;
}

int main() {
    string filePath = "1.txt";
    int n; 
    vector<vector<int>> adj;

    readFile(filePath, n, adj);
    // printAdjList(n, adj);

    vector<int> result = TopologicalSort(n, adj);

    for (int vertex : result) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}