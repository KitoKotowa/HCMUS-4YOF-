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
    fin >> n;

    items.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> items[i].weight >> items[i].value;
    }
    
    fin.close();
}

int main() {
    string filePath = "6.txt";
    int capacity, n;
    int best_value = 0;
    int best_combination = 0;
    vector<Item> items;
    readFile(filePath, capacity, n, items);

    for (int i = 0; i < (1 << n); ++i) {
        int sum_weight = 0;
        int sum_value = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum_weight += items[j].weight;
                sum_value += items[j].value;
            }
        }

        if (sum_weight <= capacity && sum_value >= best_value) {
            best_value = sum_value;
            best_combination = i;
        }
    }

    if (best_value == 0) {
        cout << "No solution" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            if (best_combination & (1 << i)) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
        cout << best_value << endl;

    }

    return 0;
}
