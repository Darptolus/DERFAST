#include <stdio.h>
#include "mpi.h"
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); // alt.: NULL,NULL
    
  printf("Hello world!\n");

  MPI_Finalize();

  return 0;
}
