#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, data;
    MPI_Request request;
    MPI_Status status;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure we have at least 2 processes
    if (size < 2) {
        printf("This exercise requires at least 2 processes.\n");
        MPI_Finalize();
        return -1;
    }

    if (rank == 0) {
        // Process 0 sends an integer to process 1 using non-blocking send
        data = 100;
        printf("Process 0: Sending data %d to process 1...\n", data);
        MPI_Isend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    } 
    else if (rank == 1) {
        // Process 1 receives an integer from process 0 using non-blocking receive
        printf("Process 1: Waiting to receive data from process 0...\n");
        MPI_Irecv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    }

    // Step 1: Ensure communication is complete
    // Wait for the non-blocking send/receive to finish
    if (rank == 0 || rank == 1) {
        MPI_Wait(&request, &status);
    }

    // Step 2: Synchronize all processes before proceeding
    // Ensure all processes reach this point before continuing
    MPI_Barrier(MPI_COMM_WORLD);

    // Step 3: Print the rank of each process after the barrier
    if (rank == 1) {
        // Process 1 prints the received data
        printf("Process 1: Received data %d from process 0\n", data);
    }

    // Each process prints its rank
    printf("Process %d: Finished\n", rank);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
