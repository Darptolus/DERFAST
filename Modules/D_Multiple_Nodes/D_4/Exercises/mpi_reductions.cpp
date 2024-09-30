#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, value, sum;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Step 1: Each process sets its value to its rank
    value = rank;  // Each process contributes its rank value

    // Step 2: Use MPI_Reduce to sum all values. Modify this to collect the result in rank 0.
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Step 3: Only the root process (rank 0) should print the result
    if (rank == 0) {
        // Print the total sum of all ranks
        printf("Total sum of all ranks: %d\n", sum);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}