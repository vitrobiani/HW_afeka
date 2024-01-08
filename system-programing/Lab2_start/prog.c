#include <stdio.h>
#include <string.h>
#include "arrays.h"
#include "exe.h"
#include "functionsLab2.h"


int main(int argc, char *argv[])
{
    if (argc == 0) return 1;
    printf("%s\n", argv[1]);
    if (strcmp(argv[1], "1")) {
        q1_A();
    }else if (strcmp(argv[1], "2")) {
        q1_B();
        printf("hh");
    }else if(strcmp(argv[1], "3")){
        q2();
    }else {
        printf("not good");
    }
    return 0;

}
