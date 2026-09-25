#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int N     = (argc > 1) ? atoi(argv[1]) : 20;   // total iterations
    int CHUNK = (argc > 2) ? atoi(argv[2]) : 4;    // iterations per chunk

    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));
    int *c = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    printf("N = %d, CHUNK = %d, threads = %d\n\n", N, CHUNK, omp_get_max_threads());

    double start = omp_get_wtime();

    // Iterations are split into fixed chunks of size CHUNK and assigned
    // to threads in round-robin order BEFORE the loop starts.
    #pragma omp parallel for schedule(static, CHUNK)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
        if (N <= 64)   // only print per-iteration info for small N
            printf("Thread %d -> iteration %d\n", omp_get_thread_num(), i);
    }

    double end = omp_get_wtime();

    if (N <= 64) {
        printf("\nResult c[i] = a[i] + b[i]:\n");
        for (int i = 0; i < N; i++)
            printf("c[%d] = %d\n", i, c[i]);
    }

    printf("\nTime taken: %f seconds\n", end - start);

    free(a); free(b); free(c);
    return 0;
}
