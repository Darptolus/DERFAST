#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print hello world from each process
    std::cout << "Hello world from process " << rank << " of " << size << std::endl;

    // Finalize MPI
    MPI_Finalize();

    return 0;
}