#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();
        printf("Hello %i/%i\n", m, n);
    }
    
    return 0; 
}