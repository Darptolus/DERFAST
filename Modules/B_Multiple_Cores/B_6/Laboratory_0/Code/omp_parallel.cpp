#include <omp.h>
#include <cstdio>

int main() {
    // Start a parallel region
    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();  // Get the ID of each thread
        printf("Hello from thread %d\n", thread_id);
    }  // End of parallel region

    return 0;
}