#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdatomic.h>

// a struct to hold everything
typedef struct {
    int lval, uval;
    char *flagarr;
    atomic_int *current;
    pthread_mutex_t *mutex;
} thread_args;

void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *tval);
int isprime(int n, thread_args targs);

void *find_primes(void *args) {
    thread_args *targs = (thread_args *)args;
    int num;

    while (1) {
        num = atomic_fetch_add(targs->current, 1);

        if (num > targs->uval) {
            break;
        }

        // check if the number is prime
        if (isprime(num, *targs)) {
            pthread_mutex_lock(targs->mutex);
            targs->flagarr[num - targs->lval] = 1;
            pthread_mutex_unlock(targs->mutex);
        }
    }

    return NULL;
}

int main(int argc, char **argv) {
    int lval = 1; // bottom bound
    int uval = 100; // top bound
    int nval = 10; // number of primes to show
    int tval = 4; // number of threads to create
    char *flagarr = NULL;
    int num;
    int count = 0;
    pthread_t *threads;
    thread_args targs;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    parseargs(argv, argc, &lval, &uval, &nval, &tval);
    if (uval < lval) {
        fprintf(stderr, "Upper bound should not be smaller than lower bound\n");
        exit(1);
    }
    if (lval < 2) {
        lval = 2;
        uval = (uval > 1) ? uval : 1;
    }
    if (nval < 0) {
        fprintf(stderr, "number value should not be greater or equal to 0\n");
        exit(1);
    }
    if (tval <= 0) {
        fprintf(stderr, "The number of threads should be greater than 0\n");
        exit(1);
    }

    // allocate the flags array
    flagarr = (char *)calloc(uval - lval + 1, sizeof(char));
    if (flagarr == NULL) {
        fprintf(stderr, "Failed to allocate memory for flag array\n");
        exit(1);
    }

    // initialize thread arguments
    targs.lval = lval;
    targs.uval = uval;
    targs.flagarr = flagarr;
    atomic_int current = lval;
    targs.current = &current;
    targs.mutex = &mutex;

    // create tval threads
    threads = (pthread_t *)malloc(tval * sizeof(pthread_t));
    if (threads == NULL) {
        fprintf(stderr, "Failed to allocate memory for threads\n");
        free(flagarr);
        exit(1);
    }

    // activate all the threads to to finding primes function
    for (int i = 0; i < tval; i++) {
        if (pthread_create(&threads[i], NULL, find_primes, &targs) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            free(flagarr);
            free(threads);
            exit(2);
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < tval; i++) {
        pthread_join(threads[i], NULL);
    }

    // count primes found
    for (num = lval; num <= uval; num++) {
        if (flagarr[num - lval]) {
            count++;
        }
    }

    if (count < nval) {
        printf("The number n (%d) you chose exceeded the number of primes calculated.\n", nval);
        nval = count;
    }

    // father prints results
    printf("Found %d primes%c\n", count, count ? ':' : '.');
    if (nval != count) {
        printf("Printing %d out of them\n", nval);
    }
    for (num = lval; nval > 0; num++) {
        if (flagarr[num - lval]) {
            nval--;
            printf("%d%c", num, nval ? ',' : '\n');
        }
    }

    free(flagarr);
    free(threads);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void parseargs(char *argv[], int argc, int *lval, int *uval, int *nval, int *tval) {
    int ch;
    opterr = 0;
    while ((ch = getopt(argc, argv, "l:u:n:t:")) != -1)
        switch (ch) {
        case 'l': // Lower bound flag
            *lval = atoi(optarg);
            break;
        case 'u': // Upper bound flag
            *uval = atoi(optarg);
            break;
        case 'n':
            *nval = atoi(optarg);
            break;
        case 't':
            *tval = atoi(optarg);
            break;
        case '?':
            if ((optopt == 'l') || (optopt == 'u') || (optopt == 'n') || (optopt == 't'))
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            exit(1);
        default:
            exit(1);
        }
}

int isprime(int n, thread_args targs) {
    static int *primes = NULL; // NOTE: static !
    static int size = 0;       // NOTE: static !
    static int maxprime;       // NOTE: static !
    int root;
    int i;

    // Init primes array (executed on first call)
    if (primes == NULL) {
        // lock the critical parts (static shared resource)
        pthread_mutex_lock(targs.mutex);
        primes = (int *)malloc(2 * sizeof(int));
        if (primes == NULL)
            exit(1);
        size = 2;
        primes[0] = 2;
        primes[1] = 3;
        maxprime = 3;
        pthread_mutex_unlock(targs.mutex);
    }

    root = (int)(sqrt(n));

    while (root > maxprime) {
        for (i = maxprime + 2;; i += 2) {
            if (isprime(i, targs)) {
                // lock the critical parts (static shared resource)
                pthread_mutex_lock(targs.mutex);
                if (i > maxprime) {
                    size++;
                    primes = (int *)realloc(primes, size * sizeof(int));
                    if (primes == NULL) {
                        exit(1);
                    }
                    primes[size - 1] = i;
                    maxprime = i;
                }
                pthread_mutex_unlock(targs.mutex);
                break;
            }
        }
    }
    // Check 'special' cases
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;

    // Check prime
    for (i = 0; ((i < size) && (root >= primes[i])); i++)
        if ((n % primes[i]) == 0)
            return 0;
    return 1;
}
