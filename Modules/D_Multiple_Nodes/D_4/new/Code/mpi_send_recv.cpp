#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the total number of processes and the rank of the current process
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Define a message buffer
    int message = -1;
    if (world_rank == 0) {
        // If the current process is rank 0, initialize the message
        message = 42;
        // Send the message to process with rank 1
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message: %d\n", message);
    } else if (world_rank == 1) {
        // If the current process is rank 1, receive the message from process with rank 0
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message: %d\n", message);
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}