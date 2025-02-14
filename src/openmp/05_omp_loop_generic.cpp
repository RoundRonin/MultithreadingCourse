#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();

        int b = 100;

        #pragma omp for
        for (int i = 0; i < b; i+=1) {
            printf("Hello %d (current thread -- %d)\n", i, m);
        }
    }
    
    return 0; 
}