#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINELEN (80)

char *mygets(char *buf, int len);
int mygeti();

int main() {
    int pfd1[2], pfd2[2];
    int rc;

    if (pipe(pfd1) == -1 || pipe(pfd2) == -1) {
        exit(-2);
    }

    rc = fork();
    switch (rc) {
        case -1: {
            exit(-2);
        }
        case 0: { // child loopcmp
            close(pfd1[1]); // close write end of first pipe
            close(pfd2[0]); // close read end of second pipe

            dup2(pfd1[0], STDIN_FILENO); // redirect stdin to read end of first pipe
            dup2(pfd2[1], STDOUT_FILENO); // redirect stdout to write end of second pipe

            execl("./loopcmp.exe", "loopcmp.exe", (char *)NULL); // executing child once (he will wait as long as the pipe is connected)
            exit(-2);
        }
        default: { // father
            close(pfd1[0]); // close read end of first pipe
            close(pfd2[1]); // close write end of second pipe

            char *cmpstr[] = {"lexcmp", "lencmp"};
            int veclen = sizeof(cmpstr)/sizeof(char *);
            char str1[LINELEN + 1];
            char str2[LINELEN + 1];
            int index;

            while (1) {
                printf("Please enter first string:\n");
                if (mygets(str1, LINELEN) == NULL)
                    break;
                printf("Please enter second string:\n");
                if (mygets(str2, LINELEN) == NULL)
                    break;
                do {
                    printf("Please choose:\n");
                    for (int i = 0; i < veclen; i++)
                        printf("%d - %s\n", i, cmpstr[i]);
                    index = mygeti();
                } while ((index < 0) || (index >= veclen));

                char buf[3*(LINELEN+1)]; // the cmp method, str1 and str2
                sprintf(buf, "%s\n%s\n%s\n", cmpstr[index], str1, str2);
                write(pfd1[1], buf, strlen(buf)); // write to the pipe to be read by loopcmp

                char result[LINELEN + 1];
                read(pfd2[0], result, LINELEN);
                printf("Result: %s\n", result);
            }
            close(pfd1[1]);
            close(pfd2[0]); 

            wait(NULL);
        }
    }
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

int mygeti() {
    int ch;
    int retval = 0;

    while (isspace(ch = getchar()))
        ;
    while (isdigit(ch)) {
        retval = retval * 10 + ch - '0';
        ch = getchar();
    }
    while (ch != '\n')
        ch = getchar();
    return retval;
}
