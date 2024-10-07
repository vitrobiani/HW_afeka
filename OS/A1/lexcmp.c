
#include <stdio.h>
#include <string.h>

int strCmp(const char* str1, const char* str2){
    int val = strcmp(str1, str2);

    if (val < 0) {
        return 1;
    }else if (val > 0) {
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

    return strCmp(argv[1], argv[2]);
}
