#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();

        int a = 0;
        int b = 100;

        for (int i = m; i < b; i+=n) {
            printf("Hello %d (current thread -- %d)\n", i, m);
        }
    }
    
    return 0; 
}