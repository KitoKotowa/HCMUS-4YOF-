#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int moves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

bool isValid(int x, int y, int n, vector<vector<int>>& board) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

void readFile(string& filePath, int& n, int& row, int& col) {
    ifstream fin(filePath);
    if (fin.is_open()) {
        fin >> n;
        fin >> row >> col;
        fin.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

bool solveKnightTourUtil(int x, int y, int move_i, vector<vector<int>>& board, int n) {
    if (move_i == n * n) {
        return true;
    }
    for (int k = 0; k < 8; ++k) {
        int next_x = x + moves[k][0];
        int next_y = y + moves[k][1];
        if (isValid(next_x, next_y, n, board)) {
            board[next_x][next_y] = move_i;
            if (solveKnightTourUtil(next_x, next_y, move_i + 1, board, n)) return true;
            else board[next_x][next_y] = -1;
        }
    }
    return false;
}

void printBoard(vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << board[i][j] + 1 << "\t";
        cout << endl;
    }
}

bool solveKnightTour(int n, int row, int col) {
    vector<vector<int>> board(n, vector<int>(n, -1));
    board[row][col] = 0;
    if (!solveKnightTourUtil(row, col, 1, board, n)) {
        cout << "No solution" << endl;
        return false;
    } else {
        printBoard(board, n);
    }
    return true;
}

int main() {
    int n, row, col;
    string filePath = "2.txt";

    readFile(filePath, n, row, col);
    solveKnightTour(n, row, col);
    return 0;
}