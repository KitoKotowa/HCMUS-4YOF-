#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isSafe(vector<int> &board, int row, int col, int n) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

bool solveNQueens(vector<int> &board, int row, int n) {
    if (row == n) {
        return true;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            board[row] = col;
            if (solveNQueens(board, row + 1, n)) {
                return true;
            }
        }
    }
    return false;
}

void printBoard(vector<int> &board, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> board(n, -1);

    if (solveNQueens(board, 0, n)) {
        printBoard(board, n);
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}