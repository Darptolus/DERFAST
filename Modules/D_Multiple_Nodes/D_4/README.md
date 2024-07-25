# D.4. Message Passing Interface (MPI)

## Prerequisites
- [D.2. DEMAC: A distributed memory architecture](../D_2/README.md)


## Table of content
0. What is MPI?
1. MPI Basics
2. Collective Communications
3. Blocking vs Non-blocking
4. Stencil Computations

## 0. What is MPI?
MPI, which stands for Message Passing Interface, is a standardized and portable message-passing system designed for parallel computing. It allows multiple processes to communicate with each other, typically in a distributed computing environment such as a cluster or a network of computers.

Some of the elements defined by MPI that allow for distributed execution of programs are:

- **Process Creation**: MPI programs typically start with a single process, which then spawns multiple processes to perform parallel computations. Each process has its own address space and can run on a different processor or node within a distributed system.

- **Message Passing**: MPI enables communication between processes through message passing. Processes can send and receive messages to and from each other using various communication operations provided by the MPI library.

- **Data Distribution**: MPI allows for the distribution of data across multiple processes. Each process can work on its own portion of the data, and communication operations are used to exchange data between processes when necessary.

- **Synchronization**: MPI provides mechanisms for synchronizing the execution of processes. This ensures that processes coordinate their activities and avoid conflicts when accessing shared resources or data.

- **Collective Operations**: MPI supports collective operations, which involve communication and coordination among multiple processes. Examples include collective communication operations like broadcast, scatter, gather, and reduce, which enable efficient data exchange and computation across all processes.

MPI is widely used in scientific and engineering applications that require high-performance computing and parallel processing, such as weather modeling, computational fluid dynamics, molecular dynamics simulations, and more. It provides a flexible and efficient way to develop parallel programs that can run on a variety of computing architectures, from multi-core processors to large-scale clusters.

## 1. MPI Basics

### Hello Worlds!

Below is a simple "Hello, World!" example written in C using MPI. This program will run on multiple processes, each printing out its own "Hello, World!" message along with its rank (identifier) within the MPI communicator.

```
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
```

To compile and run this MPI program using OpenMPI, follow these steps:

0. The file hello_worlds.c contains the code required. 

1. Compile the code using the MPI compiler wrapper provided by OpenMPI. For C code,  use mpicc:

```
mpicc -o hello_worlds hello_worlds.c
```

2. Run the MPI program using mpirun, specifying the number of processes to be used:

```
mpirun -np 4 ./hello_worlds
```

This command runs the program hello_mpi with 4 processes. You can change 4 to any number you want.

3. The output should be similar to the following:

```
Hello from process 0 of 4
Hello from process 2 of 4
Hello from process 1 of 4
Hello from process 3 of 4
```

Each line represents the "Hello, World!" message printed by a different process, along with its rank within the MPI communicator. The order of the output may vary because MPI processes may execute concurrently.



## Send and Receive - Point-to-Point

Below is an example of MPI Send and Receive operations in C, along with instructions on how to compile and run the program using OpenMPI.

```
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
```

To compile and run this MPI program using OpenMPI, follow these steps:

0. The file send_recv_mpi.c contains the code required. 

1. Compile the code using the MPI compiler wrapper provided by OpenMPI. For C code, you can use mpicc:

```
mpicc -o send_recv_mpi send_recv_mpi.c
```

2. Run the MPI program using mpirun, specifying the number of processes to be used. Since this program requires exactly 2 processes (rank 0 and rank 1), you should run it with 2 processes:

```
mpirun -np 2 ./send_recv_mpi
```

3. The output should be similar to the following:

```
Process 0 sent message: 42
Process 1 received message: 42
```

The message is sent from process 0 to process 1 using MPI_Send and MPI_Recv operations, and each process prints out the message it sent or received.

## 2. Collective Communications
## 3. Blocking vs Non-blocking
## 4. Stencil Computations
