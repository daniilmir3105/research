#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>


int main() {
    int i, j, n, a[719][719], b[719], c[719];

    clock_t start = clock();

    n = 100; //Max 719

    printf("Matrix A\n");

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            a[i][j] = 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B\n");

#pragma omp parallel private(i) shared(b)
    {
#pragma omp for
        for (i = 0; i < n; ++i) {
            b[i] = 5;
            printf("%d\n", b[i]);
        }
    }

    printf("\nA * B\n");

#pragma omp parallel private(i) shared(c)
    {
#pragma omp for
        for (i = 0; i < n; ++i) {
            c[i] = 0;
        }
    }

#pragma omp parallel private(i,j) shared(n,a,b,c)
    {
#pragma omp for schedule(dynamic)
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                c[i] += b[j] * a[j][i];
            }
        }
    }


#pragma omp parallel private(i) shared(c)
    {
#pragma omp for
        for (i = 0; i < n; ++i) {
            printf("%d\n", c[i]);
        }
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    start = clock();
    printf("Matrix A\n");

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            a[i][j] = 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B\n");

#pragma omp parallel private(i) shared(b)
    {
#pragma omp for
        for (i = 0; i < n; ++i) {
            b[i] = 5;
            printf("%d\n", b[i]);
        }
    }
    printf("\nA * B\n");
    omp_set_num_threads(4);
#pragma omp parallel for
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i] += b[j] * a[j][i];
        }
    }
    stop = clock();
    elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}
