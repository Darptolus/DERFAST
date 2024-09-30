#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, value, sum;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Step 1: Each process sets its value to its rank
    // Each process contributes its rank value for the reduction operation
    value = rank;

    // Step 2: Use MPI_Reduce to sum all values
    // - &value: The data to be reduced (in this case, the rank)
    // - &sum: The result of the reduction, stored on the root process
    // - 1: We are reducing 1 integer per process
    // - MPI_INT: The datatype of the reduction elements (integer in this case)
    // - MPI_SUM: The reduction operation, summing all values
    // - 0: The rank of the root process where the result is stored
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Step 3: Only the root process (rank 0) prints the result
    if (rank == 0) {
        // Print the total sum of all ranks
        printf("Total sum of all ranks: %d\n", sum);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
