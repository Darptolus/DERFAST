#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int root = 0;
    const int totalElements = 16;
    const int elementsPerProcess = totalElements / size;
    
    std::vector<int> sendBuffer;
    if (rank == root) {
        // Initialize the send buffer on the root process
        sendBuffer.resize(totalElements);
        for (int i = 0; i < totalElements; ++i) {
            sendBuffer[i] = i + 1;
        }
        std::cout << "Root process sending data: ";
        for (int i : sendBuffer) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    // Buffer to receive scattered data
    std::vector<int> receiveBuffer(elementsPerProcess);

    // Scatter the data from the root process to all processes
    MPI_Scatter(sendBuffer.data(), elementsPerProcess, MPI_INT, 
                receiveBuffer.data(), elementsPerProcess, MPI_INT, 
                root, MPI_COMM_WORLD);

    // Each process modifies its received data
    for (int& val : receiveBuffer) {
        val *= 2;  // Example modification: doubling each element
    }

    std::cout << "Process " << rank << " received and modified data: ";
    for (int i : receiveBuffer) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Buffer to gather modified data back into the root process
    std::vector<int> gatherBuffer;
    if (rank == root) {
        gatherBuffer.resize(totalElements);
    }

    // Gather the modified data back into the root process
    MPI_Gather(receiveBuffer.data(), elementsPerProcess, MPI_INT, 
               gatherBuffer.data(), elementsPerProcess, MPI_INT, 
               root, MPI_COMM_WORLD);

    if (rank == root) {
        std::cout << "Root process gathered modified data: ";
        for (int i : gatherBuffer) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
