/*
 * Experiment 4: OpenMP parallel region with a fixed team of 4 threads (num_threads(4))
 *
 * Compile: gcc -fopenmp parallel.c -o parallel
 * Run:     ./parallel
 */

#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        printf("Hello, my name is Divit Jain. Thread ID: %d\n",
               omp_get_thread_num());
    }

    return 0;
}
