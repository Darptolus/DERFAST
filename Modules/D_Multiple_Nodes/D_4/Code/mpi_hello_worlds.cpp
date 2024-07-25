#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the total number of processes and the rank of the current process
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Print out "Hello, World!" along with the rank of the current process
    printf("Hello from process %d of %d\n", world_rank, world_size);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}