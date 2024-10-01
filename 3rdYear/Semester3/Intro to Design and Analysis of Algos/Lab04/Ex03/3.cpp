#include <iostream> 
#include <fstream>
#include <vector>

using namespace std;

void readFile(string& filePath, int& n, vector<int>& a, int& k) {
    ifstream fin(filePath);

    fin >> n;
    a.resize(n);
    
    for (int i = 0; i <n; ++i) {
        fin >> a[i];
    }

    fin >> k;
    fin.close();
}

int partition(vector<int>& a, int l, int r) {
    int x = a[r]; 
    int i = l;
    for (int j = l; j <= r - 1; ++j) {
        if (a[j] <= x) {
            swap(a[i], a[j]);
            ++i;
        }
    }
    swap(a[i], a[r]);
    return i;
}

int selection(vector<int>& a, int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int pos = partition(a, l, r);
        if (pos - l == k - 1)
            return a[pos];
        if (pos - l > k - 1) 
            return selection(a, l, pos - 1, k);

        return selection(a, pos + 1, r, k - pos + l - 1);
    }

    return INT_MAX;
}

int main() {
    string filePath = "3.txt";
    int n, k;
    vector<int> a;
    readFile(filePath, n, a, k);
    cout << selection(a, 0, n-1, k);

    return 0;
}