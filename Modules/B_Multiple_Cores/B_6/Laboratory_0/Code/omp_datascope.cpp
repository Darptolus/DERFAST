#include <omp.h>
#include <cstdio>

int main() {
    int private_var = 10;      // Shared variable among all threads
    int shared_var = 10;      // Shared variable among all threads
    int firstprivate_var = 20; // Firstprivate variable, initialized for each thread
    int lastprivate_var = 0;   // Lastprivate variable, final value determined in parallel for loop

    #pragma omp parallel private(private_var) shared(shared_var) firstprivate(firstprivate_var)
    {
        int thread_id = omp_get_thread_num();
        private_var = thread_id;  // Each thread has its own copy of shared_var due to `private`
        printf("Thread %d: private_var = %d\n", thread_id, private_var);

        shared_var = thread_id;  // Each thread has its own copy of shared_var due to `private`
        printf("Thread %d: shared_var = %d\n", thread_id, shared_var);
        
        // The firstprivate variable is initialized with the original value for each thread
        firstprivate_var += thread_id;
        printf("Thread %d: firstprivate_var = %d\n", thread_id, firstprivate_var);
    }

    // Parallel for loop using lastprivate
    #pragma omp parallel for lastprivate(lastprivate_var)
    for (int i = 0; i < 4; i++) {
        lastprivate_var = i; // The final iteration (i=3) will set the value of lastprivate_var
        printf("Iteration %d: lastprivate_var = %d\n", i, lastprivate_var);
    }

    // Display final values
    printf("Final values:\n");
    printf("shared_var (unchanged in parallel region): %d\n", shared_var);
    printf("firstprivate_var (initial value was 20): %d\n", firstprivate_var);
    printf("lastprivate_var (from last iteration): %d\n", lastprivate_var);

    return 0;
}
