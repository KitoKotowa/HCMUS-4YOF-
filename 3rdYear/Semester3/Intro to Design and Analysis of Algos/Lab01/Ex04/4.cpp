#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = INT_MAX;

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

int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    int n;
    string filePath = "4.txt";
    // ifstream fin(filePath);

    // fin >> n;
    int city1, city2, distance;
    vector<vector<int>> dist;

    readFile(n,dist,filePath);
    vector<int> cities;
    for (int i = 0; i < n; ++i)
        cities.push_back(i);

    vector<int> best_tour;
    int min_length = INF;

    do {
        int current_length = 0;
        bool valid_tour = true;
        for (int i = 0; i < n - 1; ++i) {
            if (dist[cities[i]][cities[i + 1]] == INF) {
                valid_tour = false;
                break;
            }
            current_length += dist[cities[i]][cities[i + 1]];
        }
        if (valid_tour && dist[cities[n - 1]][cities[0]] != INF) {
            current_length += dist[cities[n - 1]][cities[0]];
            if (current_length < min_length) {
                min_length = current_length;
                best_tour = cities;
            }
        }
    } while (next_permutation(cities.begin() + 1, cities.end())); 

    if (min_length == INF) {
        cout << "No solution" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            cout << best_tour[i] + 1 << " "; 
        }
        cout << endl << min_length << endl;
    }

    return 0;
}

