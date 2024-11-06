#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Each process prints a message before the barrier
    printf("Process %d: Before the barrier\n", rank);

    // Synchronize all processes at this barrier
    MPI_Barrier(MPI_COMM_WORLD);

    // Each process prints a message after the barrier
    printf("Process %d: After the barrier\n", rank);

    MPI_Finalize();
    return 0;
}
