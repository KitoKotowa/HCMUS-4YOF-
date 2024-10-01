#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream file("1.txt");
    int n;
    file >> n;

    vector<vector<int>> triangle(n);
    vector<vector<int>> dp(n);

    for (int i = 0; i < n; i++) {
        triangle[i].resize(i + 1);
        dp[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            file >> triangle[i][j];
        }
    }

    dp[0][0] = triangle[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                dp[i][j] = dp[i-1][j] + triangle[i][j];
            } else if (j == i) {
                dp[i][j] = dp[i-1][j-1] + triangle[i][j];
            } else {
                dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
            }
        }
    }

    int max_sum = *max_element(dp[n-1].begin(), dp[n-1].end());
    
    vector<int> path;
    int j = max_element(dp[n-1].begin(), dp[n-1].end()) - dp[n-1].begin();
    
    for (int i = n - 1; i >= 0; i--) {
        path.push_back(triangle[i][j]);
        if (i > 0) {
            if (j == 0) {
                j = 0;
            } else if (j == i) {
                j--;
            } else {
                j = (dp[i-1][j-1] > dp[i-1][j]) ? j-1 : j;
            }
        }
    }

    reverse(path.begin(), path.end());

    for (int num : path) {
        cout << num << " ";
    }
    cout << endl << max_sum << endl;

    return 0;
}
