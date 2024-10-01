#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void readFile(int& n, vector<int>& a, string& filePath, int& sum) {
    ifstream fin(filePath);

    fin >> n;
    a.resize(n);
    
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }

    fin >> sum;

    fin.close();
}

bool subsetSum(vector<int>& a, vector<int>& subset, int n, int sum) {
    if (sum == 0) {
        for (int i = subset.size() - 1 ; i >= 0; --i) {
            cout << subset[i] << " ";
        }
        cout << endl;
        return true;
    }
    if (n == 0) {
        return false;
    }

    subset.push_back(a[n - 1]);
    bool found = subsetSum(a, subset, n - 1, sum - a[n - 1]);
    subset.pop_back();
    found = subsetSum(a, subset, n - 1, sum) || found;
    return found;
}

int main() {
    string filePath = "5.txt";
    int n;
    int sum;

    vector<int> a;
    readFile(n,a,filePath,sum);
    
    vector<int> subset;

    if (!subsetSum(a, subset, n, sum)) {
        cout << "No Solution" << endl;
    }

    return 0;
}