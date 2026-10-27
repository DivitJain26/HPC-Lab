/*
 * Experiment 5: OpenMP firstprivate clause - each thread gets its own copy of val,
 *               initialised with the value from before the parallel region
 *
 * Compile: gcc -fopenmp private.c -o private
 * Run:     ./private
 */

#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;

    printf("Initial value of val = %d\n", val);

    #pragma omp parallel num_threads(4) firstprivate(val)
    {
        int thread_id = omp_get_thread_num();

        printf("Thread %d: Before increment, val = %d\n",
               thread_id, val);

        val++;

        printf("Thread %d: After increment, val = %d\n",
               thread_id, val);
    }

    printf("Final value of val = %d\n", val);

    return 0;
}
