#include <iostream>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;

const int N = 500;

int num_thread = 8; //1, 2, 4, 8


int task4()
{
    int i, j, k;
    double start_time, end_time;


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

    // Matrix multiplication with OpenMP

    omp_set_num_threads(num_thread);

    start_time = omp_get_wtime();
#pragma omp parallel for private(i,j,k)
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            for (k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end_time = omp_get_wtime();

    // Output the execution time
    cout << "Matrix multiplication with " << num_thread << " threads completed in " << end_time - start_time << " seconds." << endl;

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