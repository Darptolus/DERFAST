#include <omp.h>
#include <cstdio>

int main() {
    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Before the barrier\n", thread_id);

        #pragma omp barrier  // All threads wait here until all have reached this point

        printf("Thread %d: After the barrier\n", thread_id);
    }

    return 0;
}