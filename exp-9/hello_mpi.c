/*
 * Experiment 9: MPI Hello World - every process prints a greeting and sends
 *               a message to the root process (rank 0), which prints it
 *
 * Compile: mpicc hello_mpi.c -o hello_mpi
 * Run:     mpirun -np 4 ./hello_mpi
 */

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char msg[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello World from process %d of %d\n", rank, size);

    if (rank != 0) {
        sprintf(msg, "Hello World from process %d", rank);
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(msg, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("Root (process 0) received: %s\n", msg);
        }
    }

    MPI_Finalize();
    return 0;
}
