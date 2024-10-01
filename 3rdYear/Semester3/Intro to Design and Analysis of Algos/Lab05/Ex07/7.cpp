#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>

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

pair<double, vector<vector<int>>> optimalBST(const vector<double>& p) {
    int n = p.size();
    vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0));
    vector<vector<int>> root(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        cost[i][i] = p[i];
        root[i][i] = i;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            cost[i][j] = numeric_limits<double>::max();
            double sum = 0;
            for (int k = i; k <= j; ++k) {
                sum += p[k];
            }
            for (int r = i; r <= j; ++r) {
                double left = (r > i) ? cost[i][r-1] : 0;
                double right = (r < j) ? cost[r+1][j] : 0;
                double totalCost = left + right + sum;
                if (totalCost < cost[i][j]) {
                    cost[i][j] = totalCost;
                    root[i][j] = r;
                }
            }
        }
    }

    return {cost[0][n-1], root};
}

int main() {
    ifstream inputFile("7.txt");
    if (!inputFile) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    vector<int> keys(n);
    vector<double> probabilities(n);

    for (int i = 0; i < n; i++) {
        inputFile >> keys[i];
    }
    for (int i = 0; i < n; i++) {
        inputFile >> probabilities[i];
    }

    inputFile.close();

    auto [totalCost, root] = optimalBST(probabilities);

    for (int i = 0; i < n; i++) {
        cout << keys[i] << " " << fixed << setprecision(1) << probabilities[i] << endl;
    }
    cout << "Total cost: " << fixed << setprecision(1) << totalCost << endl;

    return 0;
}