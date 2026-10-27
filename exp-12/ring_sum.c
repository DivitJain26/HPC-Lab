/*
 * Experiment 12: MPI ring communication - sum of the first N integers, the
 *                running total is passed around a ring 0 -> 1 -> ... -> size-1 -> 0
 *
 * Compile: mpicc ring_sum.c -o ring_sum
 * Run:     mpirun -np 4 ./ring_sum            (default N = 10000)
 *          mpirun -np 4 ./ring_sum 1000000    (N = 1000000)
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long N = 10000, local_sum = 0, running_sum = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) N = atoll(argv[1]);

    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    /* Each process sums its own chunk of 1..N */
    long long chunk = N / size;
    long long lo = rank * chunk + 1;
    long long hi = (rank == size - 1) ? N : lo + chunk - 1;
    for (long long i = lo; i <= hi; i++)
        local_sum += i;

    printf("Process %d: local sum of %lld..%lld = %lld\n", rank, lo, hi, local_sum);

    /* Pass the running total around the ring: 0 -> 1 -> 2 -> ... -> size-1 -> 0 */
    if (rank == 0) {
        running_sum = local_sum;
        MPI_Send(&running_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&running_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, &status);
        printf("\nRoot received final sum from process %d\n", prev);
        printf("Sum of first %lld integers (ring) = %lld\n", N, running_sum);
        printf("Expected (N(N+1)/2)               = %lld\n", N * (N + 1) / 2);
    } else {
        MPI_Recv(&running_sum, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received %lld from process %d, adding %lld, sending %lld to process %d\n",
               rank, running_sum, prev, local_sum, running_sum + local_sum, next);
        running_sum += local_sum;
        MPI_Send(&running_sum, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
