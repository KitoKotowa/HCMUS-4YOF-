#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

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

void findMaxSubseqO3(vector<int>& a, vector<int>& maxSubseq, int& maxSum, int& n) {
    maxSum = 0;
    maxSubseq.clear();
    
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int curSum = 0;
            for (int k = i; k <= j; ++k) {
                curSum += a[k];
            }
            if (curSum > maxSum) {
                maxSum = curSum;
                maxSubseq.assign(a.begin() + i, a.begin() + j + 1);
            }
        }
    }
}

void findMaxSubseqO2(vector<int>& a, vector<int>& maxSubseq, int& maxSum, int& n) {
    maxSum = 0;
    maxSubseq.clear();
    
    for (int i = 0; i < n; ++i) {
        int curSum = 0;
        for (int j = i; j < n; ++j) {
            curSum += a[j];
            if (curSum > maxSum) {
                maxSum = curSum;
                maxSubseq.assign(a.begin() + i, a.begin() + j + 1);
            }
        }
    }
}

void dynamicProgramming(vector<int>& a, vector<int>& maxSubseq, int& maxSum, int& n) {
    maxSum = 0;
    int curSum = 0;
    maxSubseq.clear();
    int start = 0;
    int temp = 0;
    int end = 0;

    for (int i = 0; i < n; ++i) {
        curSum += a[i];
        if (curSum > maxSum) {
            maxSum = curSum;
            start = temp;
            end = i;
        }
        else {
            if (curSum < 0) {
                curSum = 0;
                temp = i + 1;
            } 
        }
    }

    if (maxSum > 0) {
        for (int i = start; i <= end; ++i) {
            maxSubseq.push_back(a[i]);
        }
    }
}



void printSubsum(vector<int>& maxSubseq, int& maxSum) {
    if (maxSum <= 0) {
        maxSum = 0;
        maxSubseq.clear();
    }
    
    for (int num : maxSubseq) {
        cout << num << " ";
    }
    cout << endl << maxSum << endl;
}

int main() {
    string filePath = "1.txt";
    int n;
    vector<int> a;
    
    readFile(filePath, n, a);
    
    vector<int> maxSubseq;
    int maxSum;

    findMaxSubseqO3(a, maxSubseq, maxSum, n);
    cout << "Brute force with running time Θ(n^3)"<< endl;
    printSubsum(maxSubseq, maxSum);

    findMaxSubseqO2(a, maxSubseq, maxSum, n);
    cout << "Brute force with running time Θ(n^2)"<< endl;
    printSubsum(maxSubseq, maxSum);

    dynamicProgramming(a,maxSubseq, maxSum, n);
    cout << "Dynamic Programming"<< endl;
    printSubsum(maxSubseq, maxSum);

    return 0;
}