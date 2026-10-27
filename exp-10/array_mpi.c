/*
 * Experiment 10: MPI point-to-point communication - each process sends an
 *                array of 2 integers to the root process (rank 0)
 *
 * Compile: mpicc array_mpi.c -o array_mpi
 * Run:     mpirun -np 4 ./array_mpi
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data[2];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Each process prepares two numbers */
    data[0] = rank * 10;
    data[1] = rank * 10 + 1;

    if (rank != 0) {
        MPI_Send(data, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent: %d, %d\n", rank, data[0], data[1]);
    } else {
        printf("Root (process 0) has its own data: %d, %d\n", data[0], data[1]);
        for (int i = 1; i < size; i++) {
            int recv[2];
            MPI_Recv(recv, 2, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Root received from process %d: %d, %d\n", i, recv[0], recv[1]);
        }
    }

    MPI_Finalize();
    return 0;
}
