#include <iostream>
#include <omp.h>
#include <stdio.h>


int task1() {
#pragma omp parallel
    {

        printf("Hello world! I'm thread number: %d . Total threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}