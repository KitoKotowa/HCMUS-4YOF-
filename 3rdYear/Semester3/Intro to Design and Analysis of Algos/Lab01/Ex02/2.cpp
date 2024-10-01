#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

void readFile(string& filePath, int& k, vector<int>& denominations, int& n) {
    ifstream fin(filePath);
    if (fin.is_open()) {
        fin >> k;
        denominations.resize(k);
        for (int i = 0; i < k; ++i) {
            fin >> denominations[i];
        }
        fin >> n;
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void findMinCoins(vector<int> &denominations, int n, vector<int> &result, vector<int> &current, int index, int &minCoins) {
    if (n == 0) {
        int coinCount = 0;
        for (int c : current) {
            coinCount += c;
        }
        if (coinCount < minCoins) {
            minCoins = coinCount;
            result = current;
        }
        return;
    }
    
    if (index >= denominations.size() || n < 0) return;
    
    for (int i = 0; i <= n / denominations[index]; ++i) {
        current[index] = i;
        findMinCoins(denominations, n - i * denominations[index], result, current, index + 1, minCoins);
    }
}

int main() {
    int k, n;
    vector<int> denominations;
    string filePath = "2.txt";

    vector<int> result(k, 0);
    vector<int> current(k, 0);

    readFile(filePath, k, denominations, n);

    int minCoins = INT_MAX;
    
    findMinCoins(denominations, n, result, current, 0, minCoins);
    
    if (minCoins == INT_MAX) {
        cout << "No solution" << endl;
    } else {
        for (int i = 0; i < k; ++i) {
            cout << denominations[i] << ": " << result[i] << endl;
        }
    }
    
    return 0;
}