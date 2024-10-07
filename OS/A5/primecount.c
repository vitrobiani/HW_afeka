#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

void parseargs(char *argv[], int argc, int *lval, int *uval, int* nval, int* pval);
int isprime(int n);

int main(int argc, char **argv) {
    int lval = 1; // bottom bound
    int uval = 100; // top bound
    int nval = 10; // number of primes to show
    int pval = 4; // number of children to create
    char *flagarr = NULL;
    int num;
    int count = 0;

    // Parse arguments
    parseargs(argv, argc, &lval, &uval, &nval, &pval);
    if (uval < lval) {
        fprintf(stderr, "Upper bound should not be smaller then lower bound\n");
        exit(1);
    }
    if (lval < 2) {
        lval = 2;
        uval = (uval > 1) ? uval : 1;
    }
    if(nval < 0){
        fprintf(stderr, "number value should not be greater or equal to 0\n");
        exit(1);
    }
    if(pval <= 0){
        fprintf(stderr, "the number of child processes should not be greater or equal to 0\n");
        exit(1);
    }

    // Allocate flags
    flagarr = mmap(NULL, sizeof(int) * (uval - lval + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // mmap creates memory space that all the children can access
    if (flagarr == NULL)
        exit(1);
    // init with 0's
    for (int i = 0; i < (uval-lval); i++) {
        flagarr[i] = 0;
    }

    // forking the program pval times
    for (int p = 1; p <= pval; p++) {
        switch (fork()) {
            case -1: {
                exit(-2);
            }
            case 0: {
                int k = 0;
                int i = lval+(k*pval)+p-1;
                for (; i <= uval; k++) {
                    if (isprime(i)) {
                        flagarr[i-lval] = 1;
                    } else {
                        flagarr[i-lval] = 0;
                    }
                    i = lval+(k*pval)+p-1; // each child updates the corresponding place in the array
                }
                exit(0); // making sure to exit each of them
                break;
            }
        }
    }
    while (wait(NULL) != -1); // waiting for the children
    for (int i = 0; i < (uval-lval); i++) if (flagarr[i]) count++; // father "conting" all the primes found

    if (count < nval) {
        printf("the number n (%d) you chose exceeded the number of primes calculated.\n", nval);
        nval = count;
    }

    // Print results
    printf("Found %d primes%c\n", count, count ? ':' : '.');
    if (nval != count) {
        printf("printing %d out of them\n", nval);
    }
    for (num = lval; nval > 0 ; num++)
        if (flagarr[num - lval]) {
            nval--;
            printf("%d%c", num, nval ? ',' : '\n');
        }

    munmap(flagarr, sizeof(char) * (uval - lval + 1)); // free the mapping
    return 0;
}

// NOTE : use 'man 3 getopt' to learn about getopt(), opterr, optarg and optopt
void parseargs(char *argv[], int argc, int *lval, int *uval, int* nval, int* pval) {
    int ch;

    opterr = 0;
    while ((ch = getopt(argc, argv, "l:u:n:p:")) != -1)
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
        case 'p':
            *pval = atoi(optarg);
            break;
        case '?':
            if ((optopt == 'l') || (optopt == 'u'))
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

int isprime(int n) {
    static int *primes = NULL; // NOTE: static !
    static int size = 0;       // NOTE: static !
    static int maxprime;       // NOTE: static !
    int root;
    int i;

    // Init primes array (executed on first call)
    if (primes == NULL) {
        primes = (int *)malloc(2 * sizeof(int));
        if (primes == NULL)
            exit(1);
        size = 2;
        primes[0] = 2;
        primes[1] = 3;
        maxprime = 3;
    }

    root = (int)(sqrt(n));

    // Update primes array, if needed
    while (root > maxprime)
        for (i = maxprime + 2;; i += 2)
            if (isprime(i)) {
                size++;
                primes = (int *)realloc(primes, size * sizeof(int));
                if (primes == NULL)
                    exit(1);
                primes[size - 1] = i;
                maxprime = i;
                break;
            }

    // Check 'special' cases
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;

    // Check prime
    for (i = 0; ((i < size) && (root >= primes[i])); i++) {
        if ((n % primes[i]) == 0)
            return 0;
    }
    return 1;
}
