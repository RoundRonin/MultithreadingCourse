#include <stdio.h>
#include <omp.h>

int main(void) {
#pragma omp parallel
    {
        int n = omp_get_num_threads();
        int m = omp_get_thread_num();

        int a = 0;
        int b = 101;

        int width = b / n;
        int num_long = b / m;

        int left = a;
        int right = b;

        if (n < num_long) {
            left = a + m * (width + 1);
            right = left + (width + 1);
        } else if (n == num_long) {
            left = a + m * (width + 1);
            right = left + width;
        } else {
            left = a + m * (width + 1) + n - num_long;
            right = left + width;
        }
        
        for (int i = left; i < right; i+=1) {
            printf("Hello %d (current thread -- %d)\n", i, m);
        }
    }
    
    return 0; 
}