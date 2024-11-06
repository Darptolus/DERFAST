#include <omp.h>
#include <cstdio>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Only one thread (Thread %d) creates tasks\n", omp_get_thread_num());

            // Task 1
            #pragma omp task
            {
                printf("Task 1 executed by thread %d\n", omp_get_thread_num());
            }

            // Task 2
            #pragma omp task
            {
                printf("Task 2 executed by thread %d\n", omp_get_thread_num());
            }
        }
    }

    return 0;
}
