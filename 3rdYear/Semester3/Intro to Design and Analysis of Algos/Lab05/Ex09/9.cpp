#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Item {
    int weight;
    int value;
};

void readFile(string& filePath, int& capacity, int& n, vector<Item>& items) {
    ifstream fin(filePath);
    fin >> capacity >> n;

    items.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> items[i].weight >> items[i].value;
    }
    
    fin.close();
}

int main() {
    string filePath = "9.txt";
    int capacity, n;
    vector<Item> items;
    readFile(filePath, capacity, n, items);

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= capacity; ++j) {
            if (items[i - 1].weight > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }

    int best_value = dp[n][capacity];
    if (best_value == 0) {
        cout << "No solution" << endl;
    } else {
        int j = capacity;
        vector<int> res;
        for (int i = n; i > 0; --i) {
            if (dp[i][j] != dp[i - 1][j]) {
                res.push_back(i);
                j -= items[i - 1].weight;
            }
        }

        for (int i = res.size() - 1; i >= 0; i--) 
            cout << res[i] << " "; 

        cout << endl;
        cout << best_value << endl;
    }

    return 0;
}