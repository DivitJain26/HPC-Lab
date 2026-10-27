/*
 * Experiment 3: OpenMP Hello World - every thread prints its thread ID
 *
 * Compile: gcc -fopenmp hello.c -o hello
 * Run:     OMP_NUM_THREADS=4 ./hello
 */

#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello World from thread %d\n", thread_id);
    }

    return 0;
}
