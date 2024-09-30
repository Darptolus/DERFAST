#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel num_threads(10)
    {
        printf("Hi from %d\n", omp_get_thread_num());
    }
    return 0;
}