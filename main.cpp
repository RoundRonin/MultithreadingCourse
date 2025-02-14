#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <math.h>

bool isPrime(int number) {
    int root = sqrt(number);
    for (int i = 2; i <= root; i++) {
        if (number % i == 0) return false;
    }
    return true;
}

int main(void) {
    // дано n -- вывести число простых чисел <= n
    int n, counter{0};
    std::cin >> n;
    double time_before = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) counter++;
    }
    double time_after = omp_get_wtime();
    double time_diff = time_after - time_before;
    std::cout << counter << std::endl;
    std::cout << time_diff << std::endl;
}