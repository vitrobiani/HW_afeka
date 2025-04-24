#include <stdio.h>
#include <math.h>
#define HEAVY 100000
#define SIZE 30

// This function performs heavy computations,
// its run time depends on x and y values
// DO NOT change the function
double heavy(int x, int y) {
    int i, loop;
    double sum = 0;
    if ((x == 3 && y == 3) || (x == 3 && y == 5) || (x == 3 && y == 7) ||
        (x == 20 && y == 10))
        loop = 200;
    else
        loop = 1;
    for (i = 1; i < loop * HEAVY; i++)
        sum += cos(exp(cos((double)i / HEAVY)));
    return sum;
}

// Sequential code to be parallelized
int main(int argc, char *argv[]) {
    int x, y;
    int size = SIZE;
    double answer = 0;

    for (x = 0; x < size; x++)
        for (y = 0; y < size; y++)
            answer += heavy(x, y);

    printf("answer = %e\n", answer);
}
