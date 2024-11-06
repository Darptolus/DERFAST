#include <omp.h>
#include <cstdio>

int main() {
    int counter = 0;

    #pragma omp parallel num_threads(10)
    {
        // Each thread increments the counter atomically
        #pragma omp atomic
        counter++;

        int thread_id = omp_get_thread_num();
        printf("Thread %d incremented counter to %d\n", thread_id, counter);
    }

    // Final value of counter after all threads have incremented it
    printf("Final counter value: %d\n", counter);

    return 0;
}