#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN (80)

int lencmp(const char *str1, const char *str2);
int lexcmp(const char *str1, const char *str2);
int digcmp(const char *str1, const char *str2);
char *mygets(char *buf, int len);

int main(int argc, char *argv[]) {
    int (*cmpfunc)(const char *, const char *) = NULL;
    char str1[LINELEN + 1];
    char str2[LINELEN + 1];

    if (argc != 2)
        return -1;

    if (!strcmp(argv[1], "lexcmp"))
        cmpfunc = lexcmp;
    else if (!strcmp(argv[1], "lencmp"))
        cmpfunc = lencmp;
    else if (!strcmp(argv[1], "digcmp"))
        cmpfunc = digcmp;
    else
        return -1;

    while (1) {
        if (mygets(str1, LINELEN) == NULL)
            break;
        if (mygets(str2, LINELEN) == NULL)
            break;
        printf("%d\n", cmpfunc(str1, str2));
        fflush(stdout);
    }
    return 0;
}

int lencmp(const char *str1, const char *str2) {
    int val;
    val = strlen(str1) - strlen(str2);
    if (val < 0)
        return 1;
    if (val > 0)
        return 2;
    return 0;
}

int lexcmp(const char *str1, const char *str2) {
    int val;

    val = strcmp(str1, str2);
    if (val < 0)
        return 1;
    if (val > 0)
        return 2;
    return 0;
}

int digcmp(const char* str1, const char* str2){
    int d1 = atoi(str1);
    int d2 = atoi(str2);

    if (d1 < d2) {
        return 1;
    }else if (d1 > d2) {
        return 2;
    }else {
        return 0;
    }
}

char *mygets(char *buf, int len) {
    char *retval;

    retval = fgets(buf, len, stdin);
    buf[len] = '\0';
    if (buf[strlen(buf) - 1] == 10) /* trim \r */
        buf[strlen(buf) - 1] = '\0';
    else if (retval)
        while (getchar() != '\n')
            ; /* get to eol */

    return retval;
}
