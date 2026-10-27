/*
 * Experiment 11: MPI sum of the first N integers - each process sums its own
 *                chunk, then MPI_Reduce combines the partial sums at root
 *
 * Compile: mpicc sum_mpi.c -o sum_mpi
 * Run:     mpirun -np 4 ./sum_mpi            (default N = 10000)
 *          mpirun -np 4 ./sum_mpi 1000000    (N = 1000000)
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long N = 10000, local_sum = 0, total_sum = 0;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) N = atoll(argv[1]);

    start = MPI_Wtime();

    /* Each process sums its own chunk of 1..N */
    long long chunk = N / size;
    long long lo = rank * chunk + 1;
    long long hi = (rank == size - 1) ? N : lo + chunk - 1;

    for (long long i = lo; i <= hi; i++)
        local_sum += i;

    printf("Process %d summed %lld..%lld = %lld\n", rank, lo, hi, local_sum);

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    end = MPI_Wtime();

    if (rank == 0) {
        printf("\nSum of first %lld integers = %lld\n", N, total_sum);
        printf("Expected (N(N+1)/2)       = %lld\n", N * (N + 1) / 2);
        printf("Processes: %d, Time: %f sec\n", size, end - start);
    }

    MPI_Finalize();
    return 0;
}
