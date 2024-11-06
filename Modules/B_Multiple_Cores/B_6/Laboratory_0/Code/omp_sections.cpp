#include <omp.h>
#include <cstdio>

int main() {
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            printf("Hello from section 1\n");
        }

        #pragma omp section
        {
            printf("Hello from section 2\n");
        }
    }  // End of parallel sections

    return 0;
}