#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void readFile(string& filePath, int& n, vector<int>& a) {
    ifstream fin(filePath);

    fin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }
    
    fin.close();
}

struct Result {
    int sum;
    int start;
    int end;
};

Result sumMax(vector<int>& a, int l, int r) {
    if (l == r) {
        return {max(a[l], 0), l, l};
    }
    int c = (l + r) / 2;
    Result maxLS = sumMax(a, l, c);
    Result maxRS = sumMax(a, c+1, r);
    
    int temp = 0;
    int maxLpartS = 0;
    int lStart = c;

    for (int i = c; i >= l; --i) {
        temp += a[i];
        if (temp > maxLpartS) {
            maxLpartS = temp;
            lStart = i;
        }
    }
    
    int maxRpartS = 0;
    int rEnd = c + 1;
    temp = 0;
    for (int i = c+1; i <= r; ++i) {
        temp += a[i];
        if (temp > maxRpartS) {
            maxRpartS = temp;
            rEnd = i;
        }
    }
    int crossSum = maxLpartS + maxRpartS;
    
    if (crossSum >= maxLS.sum && crossSum >= maxRS.sum) {
        return {crossSum, lStart, rEnd};
    } else if (maxLS.sum >= maxRS.sum) {
        return maxLS;
    } else {
        return maxRS;
    }
}

int main() {
    string filePath = "3.txt";
    int n;
    vector<int> a;
    
    readFile(filePath, n, a);
    Result res = sumMax(a, 0, n-1);

    for (int i = res.start; i <= res.end; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << res.sum << endl;

    return 0;
}