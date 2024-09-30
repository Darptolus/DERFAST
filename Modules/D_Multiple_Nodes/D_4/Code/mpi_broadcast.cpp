#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int arraySize = 5;
    std::vector<int> data(arraySize);

    if (rank == 0) {
        // Root process initializes the data
        for (int i = 0; i < arraySize; ++i) {
            data[i] = i + 1;
        }
        std::cout << "Process 0 broadcasting data: ";
        for (int i : data) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    // Broadcast the data from process 0 to all other processes
    MPI_Bcast(data.data(), arraySize, MPI_INT, 0, MPI_COMM_WORLD);

    // All processes receive the broadcasted data
    std::cout << "Process " << rank << " received data: ";
    for (int i : data) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
