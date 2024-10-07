#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELEN (80)

int lencmp(const char *str1, const char *str2);
int lexcmp(const char *str1, const char *str2);
char *mygets(char *buf, int len);

int main() {
    int (*cmpfunc)(const char *, const char *) = NULL;
    char cmp[LINELEN + 1];
    char str1[LINELEN + 1];
    char str2[LINELEN + 1];

    while (1) {
// each mygets is getting their input from stdin which was changed to be from the pipe, and the output to another pipe to be read by the parent
        if (mygets(cmp, LINELEN) == NULL) 
            break;

        if (!strcmp(cmp, "lexcmp"))
            cmpfunc = lexcmp;
        else if (!strcmp(cmp, "lencmp"))
            cmpfunc = lencmp;
        else
            return -1;

        if (mygets(str1, LINELEN) == NULL)
            break;
        if (mygets(str2, LINELEN) == NULL)
            break;
        printf("%s(%s, %s) == %d\n", cmp, str1, str2, cmpfunc(str1, str2));
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
