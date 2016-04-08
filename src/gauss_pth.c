#include <stdlib.h>
#include <pthread.h>
#include "tools/debug.h"
#include "tools/rand.h"
#include "tools/vector.h"
#include "tools/check.h"

typedef struct {
    double** A;
    double* b;
    int n;
    int i;
    int j;
    int p;
    pthread_mutex_t* mutex;
} th_arg; // argument for the thread target func.

void test(int n, int p);
void gauss(double** A, double* b, int n, int p);
void* th_job(void* arg);
double* backsub(double** A, double* b, int n);
int get_pivot(double** arr, int j, int n);

int main(int argc, char* argv[]) {
    int n;
    int p;

    // enable_debug();
    disable_debug();

    if(argc < 3) {
        printf("Usage : gauss_pth n p\n");
        return 0;
    }

    n = atoi(argv[1]);
    p = atoi(argv[2]);

    if(n <= 0 || p <= 0) {
        printf("n and p should be > 0\n");
        return 0;
    }

    printf("Gaussian eliminition (with pthread)\n\n");
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

    init_time();

    gauss(A, b, n, p);
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
void gauss(double** A, double* b, int n, int p) {
    pthread_t* th;
    // pthread_mutex_t mutex;
    th_arg** arg;

    int ksave; // pivot
    int i, j;

    th = malloc(p*sizeof(*th));
    arg = malloc(p*sizeof(*arg));

    for(i = 0; i < p; i++) {
        arg[i] = malloc(sizeof(*arg[i]));
    }

    // mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    for(j = 0; j < n-1; j++) {
        ksave = get_pivot(A, j, n);
        swap(&A[j], &A[ksave], sizeof(A[j]));
        swap(&b[j], &b[ksave], sizeof(b[j]));

        // create threads
        for(i = 0; i < p; i++){
            arg[i]->A = A, arg[i]->b = b;
            arg[i]->i = i, arg[i]->j = j;
            arg[i]->n = n, arg[i]->p = p;

            pthread_create(&th[i], NULL, th_job,
                    arg[i]);
        }

        // join threads
        for(i = 0; i < p; i++) {
            pthread_join(th[i], NULL);
        }

    }

    for(i = 0; i < p; i++) {
        free(arg[i]);
    }

    free(arg);
    free(th);
}

void* th_job(void* arg) {
    th_arg* targ;
    int k, l;
    double m;

    targ = (th_arg*)arg;

    // pthread_mutex_lock(targ->mutex);
    
    for(k = (targ->i)+(targ->j)+1;
            k < targ->n; k = k+(targ->p)) {
        m = (targ->A)[k][targ->j]\
            /(targ->A)[targ->j][targ->j];

        for(l = targ->j; l < targ->n; l++) {
            (targ->A)[k][l]\
                -= m*(targ->A)[targ->j][l];
        }

        (targ->b)[k] -= m*(targ->b)[targ->j];
    }
    
    // pthread_mutex_unlock(targ->mutex);

    pthread_exit(0);
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

