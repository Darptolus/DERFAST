#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char** argv) {
    unsigned cpu, node;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    syscall(SYS_getcpu, &cpu, &node, NULL);
    printf("MPI HostName: %s Rank %d / %d Thread = %d Core: %u\n",
           processor_name, world_rank, world_size, omp_get_thread_num(), cpu);
    
    #pragma omp parallel private(cpu, node)                 
    {
        syscall(SYS_getcpu, &cpu, &node, NULL);
        printf("OMP HostName: %s Rank %d / %d Thread = %d Core: %u\n", 
            processor_name, world_rank, world_size, omp_get_thread_num(), cpu);
        // usleep(1000000);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
// Compile
// PROG=hello_world_mpi_openmp_cores; g++ -fopenmp ${PROG}.cpp -o ${PROG}.o 

// Slurm
// salloc --nodes=3 --time=06:00:00
// squeue -u $USER
// srun -N 3 --jobid 3075792 tests/hello_world_mpi_openmp.o 
// srun -N 1 -n 1 --sockets-per-node 1 --cores-per-socket 1 --cpus-per-task 1 --threads-per-core 1 --ntasks-per-core 1 --jobid 3075792 tests/hello_world_mpi_openmp.o
// srun -N 1 -n 1 --sockets-per-node 1 --cores-per-socket 2 --cpus-per-task 2 --threads-per-core 1 --ntasks-per-core 1 --jobid 3075792 tests/hello_world_mpi_openmp.o

// PBS
// module load gcc openmpi
// export OMP_NUM_THREADS=3    
// One node 
// qsub -I -l select=1:ncpus=128:mpiprocs=1,walltime=01:00:00 -j oe -A hpc-spectacle -q debug -m n -N decard_test
// qsub -I -l select=2:ncpus=128:mpiprocs=1,walltime=00:15:00 -j oe -A hpc-spectacle -q debug -m n -N decard_test
// qsub -I -l select=2:ncpus=128:mpiprocs=2,walltime=00:10:00 -j oe -A hpc-spectacle -q debug -m n -N decard_test
// mpicxx -fopenmp Hello_World_MPI_OPENMP.cpp -o Hello_World_MPI_OPENMP.o
// mpirun -np 2 hello_world_MPI_OPENMP_cores.o

// qsub -l select=2:ncpus=128:mpiprocs=2,walltime=00:10:00 -j oe -A hpc-spectacle -q debug -m n -N wrf_test -k doe test_pbs

// WRF test on improv
// source ~/WRF_2/wrf_install/var_exports.sh
// qsub test_pbs 
// mpirun -np 1 ./hello_world_MPI_OPENMP_cores.o

// Improv
// PROG=hello_world_mpi_openmp_cores; OMP_NUM_THREADS=3; mpiexec --bind-to core:2 --map-by numa:8 ./${PROG}.o 
// Single Node - 8 MPI Ranks - 16 Threads by MPI rank
// PROG=hello_world_mpi_openmp_cores; OMP_NUM_THREADS=16; mpiexec -np 8 --bind-to core:16 --map-by numa:8 ./${PROG}.o 


// Laptop - MPICH
// PROG=test_mpi_openmp; mpicxx -fopenmp -o ${PROG} ${PROG}.cpp 