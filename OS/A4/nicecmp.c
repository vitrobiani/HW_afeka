#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINELEN (80)

int lencmp(const char *str1, const char *str2);
int lexcmp(const char *str1, const char *str2);
char *mygets(char *buf, int len);
int mygeti();

int main()
{
    int pfd[2];
    int rc;
    char *cmpstr[] = {"lexcmp", "lencmp"};
    int veclen = sizeof(cmpstr)/sizeof(char *);
    char str1[LINELEN + 1];
    char str2[LINELEN + 1];
    int index;

    if (pipe(pfd) == -1) {
        exit(-2);
    }

    rc = fork();


    switch (rc) {
        case -1: {
            exit(-2);
        }
        case 0: { // child loopcmp
            close(pfd[1]); // close son write
            dup2(pfd[0], STDIN_FILENO); // change child read to be through the pipe
            close(pfd[0]); // close child og read

            execl("./loopcmp.exe", "loopcmp.exe", (char *)NULL); // executing child once (he will wait as long as the pipe is connected)
            exit(-2);
        }
        default: { // father
            close(pfd[0]);  // close father read

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
                write(pfd[1], buf, strlen(buf)); // write to the pipe to be read by loopcmp
                usleep(1000); // wait a little while just so the os doesn't start this loop again (in father) before finishing printing in the son
            }

            close(pfd[1]);  // Close write end of pipe
            wait(NULL);  // Wait for child process to finish
        }
    }
    return 0;
}

char *mygets(char *buf, int len)
{
    char *retval;

    retval = fgets(buf, len, stdin);
    buf[len] = '\0';
    if (buf[strlen(buf) - 1] == 10) /* trim \r */
        buf[strlen(buf) - 1] = '\0';
    else if (retval) 
        while (getchar() != '\n'); /* get to eol */

    return retval;
}

int mygeti()
{
    int ch;
    int retval = 0;

    while (isspace(ch = getchar()));
    while (isdigit(ch))
    {
        retval = retval * 10 + ch - '0';
        ch = getchar();
    }
    while (ch != '\n')
        ch = getchar();
    return retval;
}
