#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINELEN (80)

char *mygets(char *buf, int len);
int execute(char *executable, char *arg1, char *arg2);

int main(int argc, char *argv[]) {
    char *command = argv[1];
    if (command[0] != '.' && command[0] != '/') { // to add the './'
        char newCommand[LINELEN];
        strcpy(newCommand, "./");
        strcat(newCommand, command);
        command = newCommand;
    }
    char str1[LINELEN + 1];
    char str2[LINELEN + 1];

    if (argc != 2)
        return -1;

    while (1) {
        if (mygets(str1, LINELEN) == NULL) {
            break;
        }
        if (mygets(str2, LINELEN) == NULL) {
            break;
        }
        printf("Exit Status: %d\n", execute(command, str1, str2));
        fflush(stdout);
    }
    return 0;
}

int execute(char *executable, char *arg1, char *arg2) {
    char *args[] = {executable, arg1, arg2, NULL};

    int rc = fork();
    int status;
    int exit_status = -2;

    if (rc < 0) {
        exit(-2);
    } else if (rc == 0) {
        execvp(args[0], args);
    } else {
        waitpid(rc, &status, 0);
        exit_status = WEXITSTATUS(status);
    }
    return exit_status;
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
