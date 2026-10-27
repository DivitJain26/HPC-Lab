/*
 * Experiment 6: OpenMP private clause - each thread gets its own uninitialised copy of val
 *
 * Compile: gcc -fopenmp private_clause.c -o private_clause
 * Run:     ./private_clause
 */

#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;

    printf("Initial value of val = %d\n", val);

    #pragma omp parallel num_threads(4) private(val)
    {
        int thread_id = omp_get_thread_num();

        val = 100 + thread_id;

        printf("Thread %d: Before increment, val = %d\n",
               thread_id, val);

        val++;

        printf("Thread %d: After increment, val = %d\n",
               thread_id, val);
    }

    printf("Final value of val = %d\n", val);

    return 0;
}
