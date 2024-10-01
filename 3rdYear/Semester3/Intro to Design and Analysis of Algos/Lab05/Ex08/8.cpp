#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

using namespace std;

void readFile(int& n, vector<int>& w, string& filePath, int& t) {
    ifstream fin(filePath);
    fin >> n;
    w.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> w[i];
    }
    fin >> t;
    fin.close();
}

void printSubset(const vector<int>& w, const vector<bool>& subset) {
    for (int i = 0; i < w.size(); ++i) {
        if (subset[i]) {
            cout << w[i] << " ";
        }
    }
    cout << endl;
}

void SoS_DP(const vector<int>& w, int t) {
    int n = w.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(t + 1, false));
    
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= t; ++j) {
            if (j < w[i-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j-w[i-1]];
            }
        }
    }
    
    vector<bool> subset(n, false);
    for (int i = n, j = t; i > 0 && j >= 0; --i) {
        if (i == 1 && j > 0 && dp[i][j]) {
            subset[i-1] = true;
            printSubset(w, subset);
        } else if (dp[i-1][j]) {
            continue;
        } else {
            subset[i-1] = true;
            j -= w[i-1];
            if (j == 0) {
                printSubset(w, subset);
            }
        }
    }
}

int main() {
    string filePath = "8.txt";
    int n, t;
    vector<int> w;

    readFile(n, w, filePath, t);
    
    int total = accumulate(w.begin(), w.end(), 0);
    
    if (*min_element(w.begin(), w.end()) <= t && t <= total) {
        SoS_DP(w, t);
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}