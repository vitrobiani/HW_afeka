#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *code = NULL;
    size_t s = 0;
    size_t n = getline(&code, &s, stdin);
    code[n - 1] = '\0';

    printf("%s\n", code);
    printf("%lu\n", s);
    printf("%lu\n", n);
    printf("%lu\n", strlen(code));

    return 0;
}
