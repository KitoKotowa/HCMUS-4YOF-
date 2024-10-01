#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

void readFile(string& filePath, vector<vector<int>>& costMatrix, int& n, vector<int>& assignment) {
    ifstream fin(filePath);

    fin >> n;
    
    costMatrix.resize(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> costMatrix[i][j];
        }
    }
    assignment.resize(n);
    for (int i = 0; i < n; ++i) {
        assignment[i] = i;
    }
        
    fin.close();
}

int calculateCost(const vector<vector<int>>& costMatrix, const vector<int>& assignment) {
    int totalCost = 0;
    for (int i = 0; i < assignment.size(); ++i) {
        totalCost += costMatrix[i][assignment[i]];
    }
    return totalCost;
}

void createPermutations(vector<int>& assignment, int start, int n, const vector<vector<int>>& costMatrix, int& minCost, vector<int>& best) {
    if (start == n) {
        int currentCost = calculateCost(costMatrix, assignment);
        if (currentCost < minCost) {
            minCost = currentCost;
            best = assignment;
        }
        return;
    }

    for (int i = start; i < n; ++i) {
        swap(assignment[start], assignment[i]);
        createPermutations(assignment, start + 1, n, costMatrix, minCost, best);
        swap(assignment[start], assignment[i]);
    }
}

int main() {
    string filePath = "7.txt";
    int n = 0;
    int minCost = INT_MAX;
    vector<int> best;
    vector<int> assignment;
    vector<vector<int>> costMatrix;

    readFile(filePath, costMatrix, n, assignment);

    createPermutations(assignment, 0, n, costMatrix, minCost, best);

    for (int i = 0; i < best.size(); ++i) {
        cout << best[i] + 1 << " ";
    }
    cout << endl;
    cout << minCost << endl;

    return 0;
}
