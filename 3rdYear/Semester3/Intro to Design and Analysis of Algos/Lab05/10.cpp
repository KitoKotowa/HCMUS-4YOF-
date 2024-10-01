#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int INF = -1e9;

void readFile(int& n, vector<vector<int>>& dist, const string& filePath) {
    ifstream fin(filePath);

    fin >> n;
    dist.assign(n, vector<int>(n, INF));

    int city1, city2, distance;
    while (fin >> city1 >> city2 >> distance) {
        if (city1 == -1 && city2 == -1 && distance == -1)
            break;
        dist[city1 - 1][city2 - 1] = distance;
        dist[city2 - 1][city1 - 1] = distance;
    }

    fin.close();
}

int main() {
    int n;
    string filePath = "10.txt";

    vector<vector<int>> dist;

    readFile(n, dist, filePath);

    int dp[(1 << n)][n];
    for (int i = 0; i < (1 << n); ++i)
        for (int j = 0; j < n; ++j)
            dp[i][j] = INF;

    dp[1][0] = 0;

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (!((mask >> i) & 1))
                continue;
            int prev_mask = mask ^ (1 << i);
            for (int j = 0; j < n; ++j) {
                if (i == j || !((prev_mask >> j) & 1))
                    continue;
                dp[mask][i] = min(dp[mask][i], dp[prev_mask][j] + dist[j][i]);
            }
        }
    }

    int min_length = INF;
    int best_tour = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[(1 << n) - 1][i] + dist[i][0] < min_length) {
            min_length = dp[(1 << n) - 1][i] + dist[i][0];
            best_tour = i;
        }
    }

    if (min_length == INF) {
        cout << "No solution" << endl;
    } else {
        vector<int> tour;
        int mask = (1 << n) - 1;
        tour.push_back(best_tour);
        while (mask > 1) {
            for (int i = 0; i < n; ++i) {
                if (i == best_tour)
                    continue;
                if (((mask >> i) & 1) && dp[mask][best_tour] == dp[mask ^ (1 << i)][i] + dist[i][best_tour]) {
                    tour.push_back(i);
                    mask ^= (1 << i);
                    best_tour = i;
                    break;
                }
            }
        }
        tour.push_back(0);
        reverse(tour.begin(), tour.end());
        for (int i = 0; i < n; ++i) {
            cout << tour[i] + 1 << " ";
        }
        cout << endl << min_length << endl;
    }

    return 0;
}