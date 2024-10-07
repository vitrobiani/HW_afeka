#include <stdio.h>
#include <stdlib.h>

int lencmp(const char* str1, const char* str2){
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

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Enter 2 inputs");
        return 1;
    }

    return lencmp(argv[1], argv[2]);
}
