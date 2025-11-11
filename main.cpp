#include <iostream>
#include "closest_pair.h"
#include "matrix_multiplication.h"
using namespace std;

int main() {
    cout << "==== Divide and Conquer Algorithm Demonstrator ====\n";
    cout << "1. Closest Pair of Points\n";
    cout << "2. Matrix Multiplication\n";
    int choice;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        runClosestPairDemo();
    } else if (choice == 2) {
        runMatrixMultiplicationDemo();
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
