#include <omp.h>
#include <stdio.h>
#include <math.h>

#define NUMT    4
#define SIZE    16384
#define NUMTRIES    2

float A[SIZE];
float B[SIZE];
float C[SIZE];

int main() {
    #ifndef _OPENMP
        fprintf(stderr, "OpenMP is not supported here -- sorry.\n");
    #endif
    
    for ( int i = 0; i < SIZE; i++) {
        A[i] = 1.;
        B[i] = 2.;
    }
    
    omp_set_num_threads(NUMT);
    fprintf(stderr, "Using %d threads\n", NUMT);
    
    double maxMegaMults = 0;
    
    for (int t = 0; t < NUMTRIES; t++) {
        double time0 = omp_get_wtime();
        
        #pragma omp parallel for
        for (int i = 0; i < SIZE; i++ ) {
            C[i] = A[i] * B[i];
        }
        
        double time1 = omp_get_wtime();
        double megaMults = (double)SIZE/(time1-time0)/1000000;
        if (megaMults > maxMegaMults) {
            maxMegaMults = megaMults;
        }
    }
    
    printf("Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults);
    
    return 0;
}