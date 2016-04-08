#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "tools/debug.h"
#include "tools/rand.h"
#include "tools/vector.h"
#include "tools/check.h"

void test(int n, int p);
void gauss(double** A, double* b, int n);
double* backsub(double** A, double* b, int n);
int get_pivot(double** arr, int j, int n);

int main(int argc, char* argv[]) {
    int n;
    int p;

    // enable_debug();
    disable_debug();

    if(argc < 3) {
        printf("Usage : gauss_seq n p\n");
        return 0;
    }

    n = atoi(argv[1]);
    p = atoi(argv[2]);

    if(n <= 0 || p <= 0) {
        printf("n and p should be > 0\n");
        return 0;
    }

    printf("Gaussian elimination (with OpenMP)\n\n");
    test(n, p);

    return 0;
}

/* main routine */
void test(int n, int p) {
    double **A, *b, *x;
    double correct; // ||Ax-b||_2
    double elapsed; // dt

    init_rand();

    A = init_matrix(n);
    b = init_vector(n);

    gen_matrix(A, n);
    gen_vector(b, n);

    print_matrix(A, n);
    print_vector(b, n);

    /* -------------------- */

    omp_set_num_threads(p);

    init_time();

    gauss(A, b, n);
    x = backsub(A, b, n);

    elapsed = check_time();
    correct = check_correct(A, b, x, n);

    /* -------------------- */

    print_matrix(A, n);
    print_vector(b, n);
    print_vector(x, n);

    del_matrix(A);
    del_vector(b);
    del_vector(x);

    printf("Correctness : %f\n", correct);
    printf("Elapsed time : %f\n", elapsed);
}

/* gaussian elimination */
void gauss(double** A, double* b, int n) {
    int ksave; // pivot
    int j, k, l;
    double m;

    for(j = 0; j < n-1; j++) {
        ksave = get_pivot(A, j, n);
        swap(&A[j], &A[ksave], sizeof(A[j]));
        swap(&b[j], &b[ksave], sizeof(b[j]));

#pragma omp parallel for private(k, l, m)
        for(k = j+1; k < n; k++) {
            m = A[k][j]/A[j][j];
            
            for(l = j; l < n; l++) {
                A[k][l] -= m*A[j][l];
            }

            b[k] -= m*b[j];
        }
    }
}

/* back substitution */
double* backsub(double** A, double* b, int n) {
    double* x;
    double temp;
    int i, j;
    
    x = init_vector(n);

    x[n-1] = b[n-1]/A[n-1][n-1];

    for(i = n-2; i >= 0; i--) {
        temp = 0;

        for(j = i+1; j < n; j++) {
            temp += x[j]*A[i][j];
        }

        x[i] = (b[i]-temp)/A[i][i];
    }

    return x;
}

/* pick a pivot from the jth column;
 * k = maxloc(abs(arr[j:n][j]))
 *   = {k in [j, n) |  abs(arr[k][j])
 *      > abs(arr[i][j]) for all i} */
int get_pivot(double** arr, int j, int n) {
    int k, i;
    double y_best, y_cmp;

    k = j;
    y_best = abs(arr[k][j]);

    for(i = j+1; i < n; i++) {
        y_cmp = abs(arr[i][j]);

        if(y_cmp > y_best) {
            k = i;
            y_best = y_cmp;
        }
    }

    return k;
}
