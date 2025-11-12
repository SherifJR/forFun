#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  

#define N 100000000   

int main() {
    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));
    double *z = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = 2*i;
    }

    double serial_start = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }

    double serial_end = omp_get_wtime();
    double ts = serial_end - serial_start;
    printf("z[200] = %f\n", z[200]);
    printf("This is serial, Time taken: %f seconds\n", ts);


/* OpenMP (Open Multi-Processing) is a library header in C/C++.

OpenMP is an API for parallel programming that lets you easily write multithreaded programs on shared-memory systems.*/


    omp_set_num_threads(1);  
    double start_one = omp_get_wtime();
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        z[i] = x[i] + y[i];
    }

    double t_one = omp_get_wtime() - start_one;

    int P;
    omp_set_num_threads(4); 
    double parallel_start = omp_get_wtime();

   
    #pragma omp parallel
    {
        #pragma omp single
        P = omp_get_num_threads();

        #pragma omp for
        for (int i = 0; i < N; i++) {
            z[i] = x[i] + y[i];
        }
    }

    double parallel_end = omp_get_wtime();

    double tp = parallel_end - parallel_start;

    printf("z[200] = %f\n", z[200]);
    printf("using parallel, Time taken: %f seconds\n", tp);

    double speedup = ts/tp;
    printf("Speedup is: %f\n", speedup);
    double efficiency = speedup / P;
    printf("Efficiency = %f\n", efficiency);
    double relative_speedup = t_one / tp;
    printf("Relative Speedup       = %f\n", relative_speedup);

    free(x);
    free(y);
    free(z);
    return 0;
}

