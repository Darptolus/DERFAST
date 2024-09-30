#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_value = rank;  // Each process starts with its rank as the send value
    int recv_value = -1;    // Variable to hold the received value

    int next = (rank + 1) % size;        // Next process in the ring
    int prev = (rank - 1 + size) % size; // Previous process in the ring

    // Perform the ring communication
    if (rank == 0) {
        // Process 0 starts the ring
        MPI_Send(&send_value, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_value, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        // Other processes participate in the ring
        MPI_Recv(&recv_value, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&send_value, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    // Print the received value for each process
    std::cout << "Process " << rank << " received value " << recv_value << " from process " << prev << std::endl;

    MPI_Finalize();
    return 0;
}
