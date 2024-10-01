#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> result(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> result(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    if (size == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = size / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    vector<vector<int>> M1 = strassen(addMatrices(A11, A22, newSize), addMatrices(B11, B22, newSize), newSize);
    vector<vector<int>> M2 = strassen(addMatrices(A21, A22, newSize), B11, newSize);
    vector<vector<int>> M3 = strassen(A11, subtractMatrices(B12, B22, newSize), newSize);
    vector<vector<int>> M4 = strassen(A22, subtractMatrices(B21, B11, newSize), newSize);
    vector<vector<int>> M5 = strassen(addMatrices(A11, A12, newSize), B22, newSize);
    vector<vector<int>> M6 = strassen(subtractMatrices(A21, A11, newSize), addMatrices(B11, B12, newSize), newSize);
    vector<vector<int>> M7 = strassen(subtractMatrices(A12, A22, newSize), addMatrices(B21, B22, newSize), newSize);

    vector<vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(M1, M4, newSize), M5, newSize), M7, newSize);
    vector<vector<int>> C12 = addMatrices(M3, M5, newSize);
    vector<vector<int>> C21 = addMatrices(M2, M4, newSize);
    vector<vector<int>> C22 = addMatrices(subtractMatrices(addMatrices(M1, M3, newSize), M2, newSize), M6, newSize);

    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> B[i][j];

    vector<vector<int>> C = strassen(A, B, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
