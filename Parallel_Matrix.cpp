#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std;
using namespace std::chrono;

int N; 
int NUM_THREADS; 
vector<vector<int>> A, B, C;

void initializeMatrix(vector<vector<int>> &matrix) 
{
    for (auto &row : matrix)
        for (auto &val : row) val = rand() % 100;
}

void* multiplyPart(void* arg) {
    int start = *(int*)arg, end = start + N / NUM_THREADS;
    for (int i = start; i < end; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
    return nullptr;
}

void runExperiment(int size, int threads) 
{
    N = size;
    NUM_THREADS = threads;
    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));
    C.assign(N, vector<int>(N));

    initializeMatrix(A);
    initializeMatrix(B);

    pthread_t threadHandles[NUM_THREADS];
    int indices[NUM_THREADS];

    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i * (N / NUM_THREADS);
        pthread_create(&threadHandles[i], nullptr, multiplyPart, &indices[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threadHandles[i], nullptr);

    auto end = high_resolution_clock::now();
    double elapsed = duration<double>(end - start).count();

    cout << "Matrix Size: " << N << " | Threads: " << NUM_THREADS 
         << " | Execution Time: " << fixed << setprecision(5) << elapsed << " sec\n";
}
int main() 
{
    srand(time(0));

    vector<int> matrixSizes = {100, 200, 500};
    int maxThreads = thread::hardware_concurrency(); 
    vector<int> threadCounts = {2, 4, 8, maxThreads}; 

    for (int size : matrixSizes) {
        for (int threads : threadCounts) {
            runExperiment(size, threads);
        }
        cout << "-------------------------------------\n";
    }
}
