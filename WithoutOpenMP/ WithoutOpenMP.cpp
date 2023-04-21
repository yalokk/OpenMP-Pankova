#include <iostream>
#include <chrono>

using namespace std;

const int N = 1000;

int main() {

    int i, j, k;

    double** A = new double* [N];
    double** B = new double* [N];
    double** C = new double* [N];
    for (i = 0; i < N; ++i)
    {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

   // Fill matrices with random values
    srand(time(NULL));
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            A[i][j] = (double)rand() / RAND_MAX;
            B[i][j] = (double)rand() / RAND_MAX;
            C[i][j] = 0.0;
        }
    }

    // Matrix multiplication
    auto start_time = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end_time = chrono::high_resolution_clock::now();

    // Output the execution time
    auto execution_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Matrix multiplication without OpenMP completed in : " << execution_time.count() << " microseconds" << endl;

    for (i = 0; i < N; ++i)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
