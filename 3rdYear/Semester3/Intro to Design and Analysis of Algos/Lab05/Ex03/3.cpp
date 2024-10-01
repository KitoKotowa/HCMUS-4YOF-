#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void readFile(string& filePath, vector<int>& a, int& n) {
    ifstream fin(filePath);
    if (fin.is_open()) {
        fin >> n;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            fin >> a[i];
        }
        fin >> n;
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

vector<int> findLMIS(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1);
  
    vector<int> seq(n);

    for (int i = 0; i < n; ++i) {
        seq[i] = i; 
      
        for (int prev = 0; prev < i; ++prev) {
            if (a[prev] < a[i] && 
                1 + dp[prev] > dp[i]) {
              
                dp[i] = 1 + dp[prev];
                seq[i] = prev;
            }
        }
    }

    int ans = -1;
    int ansInd = -1;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > ans) {
            ans = dp[i];
            ansInd = i;
        }
    }

    vector<int> res;
    res.push_back(a[ansInd]);
    while (seq[ansInd] != ansInd) {
        ansInd = seq[ansInd];
        res.push_back(a[ansInd]);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    string filePath = "3.txt"; 
    int n;
    vector<int> a;
    readFile(filePath, a, n);
    vector<int> result = findLMIS(a);
    
    for (int res: result) {
        cout << res << " ";
    }

    return 0;
}
