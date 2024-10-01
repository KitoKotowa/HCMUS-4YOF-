#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

using namespace std;

void readFile(int& n, vector<int>& w, string& filePath, int& t) {
    ifstream fin(filePath);
    fin >> n;
    w.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> w[i];
    }
    fin >> t;
    fin.close();
}

void SoS(vector<int>& s, int size, int sum, int start, const vector<int>& w, int t) {
    if (sum == t) {
        for (int i = 0; i < size; i++) {
            cout << s[i] << " ";
        }
        cout << endl;
    } else {
        for (int i = start; i < w.size(); i++) {
            if (sum + w[i] <= t) {
                s[size] = w[i];
                SoS(s, size + 1, sum + w[i], i + 1, w, t);
            }
        }
    }
}

void upgradedSoS(vector<int>& s, int size, int sum, int start, const vector<int>& w, int t, int total) {
    if (sum == t) {
        for (int i = 0; i < size; i++) {
            cout << s[i] << " ";
        }
        cout << endl;
        return;
    } else {
        int lost = 0;
        for (int i = start; i < w.size(); i++) {
            if ((sum + total - lost >= t) && (sum + w[i] <= t)) {
                s[size] = w[i];
                upgradedSoS(s, size + 1, sum + w[i], i + 1, w, t, total - lost - w[i]);
            }
            lost += w[i];
        }
    }
}


int main() {
    string filePath = "4.txt";
    int n, t;
    vector<int> w;

    readFile(n, w, filePath, t);
    
    int total = accumulate(w.begin(), w.end(), 0);
    
    if (*min_element(w.begin(), w.end()) <= t && t <= total) {
        vector<int> s(n, 0);
        cout << "Non-upgraded version" << endl;
        SoS(s, 0, 0, 0, w, t);
    } else {
        cout << "No Solution" << endl;
    }

    if (*min_element(w.begin(), w.end()) <= t && t <= total) {
        vector<int> s(n, 0);
        cout << "Upgraded version" << endl;
        upgradedSoS(s, 0, 0, 0, w, t, total);
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}