// tools for managing matrices (= 2d array)
// and vectors (= 1d array)

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "rand.h"

#ifndef VECTOR_H
#define VECTOR_H

/* generic swap function
 * - The size of two params should be equal! */
void swap(void* a, void* b, size_t s) {
    char *ca, *cb;
    char t;

    ca = (char*)a;
    cb = (char*)b;

    while(s--) {
        t = ca[s];
        ca[s] = cb[s];
        cb[s] = t;
    }
}

/* allocate a nXn-size matrix */
double** init_matrix(int n) {
    double** A;
    int i;

    A = calloc(n, sizeof(*A));
    A[0] = calloc(n*n, sizeof(*A[0]));

    for(i = 1; i < n; i++) {
        A[i] = A[i-1] + n;
    }

    return A;
}

/* allocate a n-size vector */
double* init_vector(int n) {
    double* a;

    a = calloc(n, sizeof(*a));

    return a;
}

/* fill the elements of the matrix
 * with randomly selected number in [0, 1) */
void gen_matrix(double** A, int n) {
    int i, j;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[i][j] = select_rand();
        }
    }
}

/* fill the elements of the vector
 * with randomly selected number in [0, 1) */
void gen_vector(double* a, int n) {
    int i;

    for(i = 0; i < n; i++) {
        a[i] = select_rand();
    }
}

/* delete the matrix */
void del_matrix(double** A) {
    if(A != NULL) {
        if(A[0] != NULL) {
            free(A[0]);
        }
        free(A);
    }
}

/* delete the vector */
void del_vector(double* a) {
    if(a != NULL) {
        free(a);
    }
}

/* print the matrix, only when ENABLE_DEBUG
 * is on */
void print_matrix(double** A, int n) {
    int i, j;

    if(!ENABLE_DEBUG) {
        return;
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n-1; j++) {
            printf("%.3f, ", A[i][j]);
        }

        printf("%.3f\n", A[i][n-1]);
    }

    printf("\n");
}

/* print the vector, only when ENABLE_DEBUG
 * is on */
void print_vector(double* a, int n) {
    int i;

    if(!ENABLE_DEBUG) {
        return;
    }

    for(i = 0; i < n-1; i++) {
        printf("%.3f, ", a[i]);
    }

    printf("%.3f\n\n", a[n-1]);
}

#endif
