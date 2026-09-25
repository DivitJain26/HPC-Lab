#include <stdio.h>
#include <omp.h>

#define TERMS 10

void series_of_2(void) {
    for (int i = 1; i <= TERMS; i++)
        printf("[Thread %d] Series of 2: %d\n", omp_get_thread_num(), 2 * i);
}

void series_of_4(void) {
    for (int i = 1; i <= TERMS; i++)
        printf("[Thread %d] Series of 4: %d\n", omp_get_thread_num(), 4 * i);
}

int main(void) {
    #pragma omp parallel num_threads(2)
    {
        // Only one thread creates the tasks...
        #pragma omp single
        {
            printf("Thread %d is creating the tasks\n\n", omp_get_thread_num());

            #pragma omp task
            series_of_2();

            #pragma omp task
            series_of_4();
        }
        // ...but any thread in the team may execute them.
        // The implicit barrier at the end of 'single' lets the idle
        // thread pick up the second task.
    }

    printf("\nBoth series printed.\n");
    return 0;
}
