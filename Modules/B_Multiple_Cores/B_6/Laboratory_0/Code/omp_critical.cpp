#include <omp.h>
#include <cstdio>

int main() {
    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        // Only one thread at a time can execute this block
        #pragma omp critical
        {
            printf("Hello from thread %d inside the critical section\n", thread_id);
        }

        // This line is executed by all threads without restriction
        printf("Hello from thread %d outside the critical section\n", thread_id);
    }

    return 0;
}
