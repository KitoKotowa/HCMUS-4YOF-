#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void readMaze(string& filename, int& w, int& h, int& startX, int& startY, int& goalX, int& goalY, vector<vector<char>>& maze) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    fin >> w >> h;
    maze.resize(h, vector<char>(w));
    fin >> startY >> startX;

    fin >> goalY >> goalX;

    string dummy;
    getline(fin, dummy);

    string line;
    for (int i = 0; i < h; ++i) {
        if (getline(fin, line)) {
            // cout << "Line " << i << ": " << line << endl;
            for (int j = 0; j < w && j < line.length(); ++j) {
                maze[i][j] = line[j];
            }
        }
    }

    fin.close();
}

bool isValid(vector<vector<char>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
}

bool findPath(vector<vector<char>>& maze, int startX, int startY, int goalX, int goalY) {
    if (!isValid(maze, startX, startY)) return false;
    if (maze[startX][startY] == 'G') return true;
    if (maze[startX][startY] == 'X' || maze[startX][startY] == '#') return false;

    char original = maze[startX][startY];
    if (original != 'S') maze[startX][startY] = 'X';

    if (findPath(maze, startX - 1, startY, goalX, goalY)) return true;
    if (findPath(maze, startX, startY + 1, goalX, goalY)) return true;
    if (findPath(maze, startX + 1, startY, goalX, goalY)) return true;
    if (findPath(maze, startX, startY - 1, goalX, goalY)) return true;

    if (original != 'S') maze[startX][startY] = ' ';

    return false;
}

void printMaze(vector<vector<char>>& maze) {
    for (auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    // vector<vector<char>> maze = {
    //     {'#', 'S', '#', '#', ' ', '#'},
    //     {'#', ' ', ' ', ' ', ' ', '#'},
    //     {' ', '#', ' ', '#', ' ', '#'},
    //     {' ', ' ', ' ', ' ', '#', '#'},
    //     {' ', ' ', '#', '#' ,' ', 'G'},
    //     {' ', ' ', ' ', ' ', ' ', '#'},
    //     {'#', '#', '#', ' ', '#', '#'}
    // };
    vector<vector<char>> maze;
    string filePath = "3.txt";
    int w,h;

    int startX, startY, goalX, goalY;

    readMaze(filePath,w,h,startX, startY, goalX, goalY, maze);

    if (findPath(maze, startX, startY, goalX, goalY)) {
        printMaze(maze);
    } else {
        cout << "\nNo solution." << endl;
    }

    return 0;
}