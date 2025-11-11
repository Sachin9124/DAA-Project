#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(Matrix A, Matrix B, int n) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(Matrix A, Matrix B, int n) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix multiply(Matrix A, Matrix B, int n) {
    Matrix C(n, vector<int>(n, 0));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int k = n / 2;

    Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    Matrix M1 = multiply(add(A11, A22, k), add(B11, B22, k), k);
    Matrix M2 = multiply(add(A21, A22, k), B11, k);
    Matrix M3 = multiply(A11, subtract(B12, B22, k), k);
    Matrix M4 = multiply(A22, subtract(B21, B11, k), k);
    Matrix M5 = multiply(add(A11, A12, k), B22, k);
    Matrix M6 = multiply(subtract(A21, A11, k), add(B11, B12, k), k);
    Matrix M7 = multiply(subtract(A12, A22, k), add(B21, B22, k), k);

    Matrix C11 = add(subtract(add(M1, M4, k), M5, k), M7, k);
    Matrix C12 = add(M3, M5, k);
    Matrix C21 = add(M2, M4, k);
    Matrix C22 = add(subtract(add(M1, M3, k), M2, k), M6, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }

    return C;
}

void runMatrixMultiplicationDemo() {
    int n;
    cout << "\nEnter size of square matrix (power of 2): ";
    cin >> n;

    Matrix A(n, vector<int>(n)), B(n, vector<int>(n));
    cout << "Enter Matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter Matrix B:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    Matrix C = multiply(A, B, n);

    cout << "\nResultant Matrix (Divide & Conquer):\n";
    for (auto row : C) {
        for (auto val : row)
            cout << val << " ";
        cout << "\n";
    }
}
