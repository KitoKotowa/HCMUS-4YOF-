#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, string> LCSLength(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> C(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            } else {
                C[i][j] = max(C[i][j - 1], C[i - 1][j]);
            }
        }
    }

    int i = m, j = n;
    string lcs;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]); 
            --i;
            --j;
        } else if (C[i - 1][j] > C[i][j - 1]) {
            --i; 
        } else {
            --j; 
        }
    }

    reverse(lcs.begin(), lcs.end()); 

    return {C[m][n], lcs}; 
}

int main() {
    // string X = "XYXZPQ";
    // string Y = "YXQYXP";
    string X,Y;
    
    getline(cin, X);
    getline(cin, Y);
    auto result = LCSLength(X, Y);

    cout << result.second << endl;

    return 0;
}
