#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 500; // Adjustable matrix size

void initializeMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(0));
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N));

    initializeMatrix(A);
    initializeMatrix(B);

    auto start = high_resolution_clock::now();
    multiplyMatrices(A, B, C);
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    cout << "Execution Time (Sequential): " << elapsed.count() << " seconds" << endl;

    return 0;
}
