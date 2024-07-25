#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process calculates a local sum
    int localSum = 0;
    for (int i = rank * 10; i < (rank + 1) * 10; ++i) {
        localSum += i;
    }

    std::cout << "Process " << rank << " local sum: " << localSum << std::endl;

    // Variable to hold the global sum
    int globalSum = 0;

    // Reduce all local sums to the global sum on the root process
    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // The root process prints the global sum
    if (rank == 0) {
        std::cout << "Global sum: " << globalSum << std::endl;
    }

    MPI_Finalize();
    return 0;
}
