#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const int N = 500;
vector<vector<int>> A(N, vector<int>(N)), B(N, vector<int>(N)), C(N, vector<int>(N));

void initializeMatrix(vector<vector<int>> &matrix) {
    for (auto &row : matrix) 
        for (auto &val : row) val = rand() % 100;
}

void multiplyMatrices() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            for (int k = 0; k < N; k++) 
                C[i][j] += A[i][k] * B[k][j];
}

int main() {
    srand(time(0));
    initializeMatrix(A), initializeMatrix(B);

    auto start = high_resolution_clock::now();
    multiplyMatrices();
    auto end = high_resolution_clock::now();

    cout << fixed << setprecision(5) << "Parallel Execution Time (OpenMP): " 
         << duration<double>(end - start).count() << " seconds\n";
}