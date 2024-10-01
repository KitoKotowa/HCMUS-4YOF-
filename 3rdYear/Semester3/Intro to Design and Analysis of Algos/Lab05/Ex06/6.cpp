#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

void readFile(int& n, vector<int>& dimensions, string& filePath) {
    ifstream fin(filePath);
    fin >> n;
    dimensions.resize(n+1);
    for (int i = 0; i < n; ++i) {
        fin >> dimensions[i] >> dimensions[i + 1];
    }
    fin.close();
}


pair<int, string> matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    function<string(int, int)> printOptimalParens = [&](int i, int j) -> string {
        if (i == j) {
            return "A" + to_string(i + 1);
        } else {
            return "(" + printOptimalParens(i, s[i][j]) + " " + printOptimalParens(s[i][j] + 1, j) + ")";
        }
    };

    return {m[0][n - 1], printOptimalParens(0, n - 1)};
}

int main() {
    string filePath("6.txt");

    int n;
    vector<int> dimensions;
    readFile(n, dimensions, filePath);

    auto result = matrixChainOrder(dimensions);

    cout << result.second << endl;
    cout << result.first << endl;

    return 0;
}