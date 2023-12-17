#include <stdio.h>
#include "functionsLab1.h"

void helloWorld(){
    printf("%s\n","hello world");
}

void printTriangle(int s){
   for (int i = 0; i < s; i++) {
        for (int j = 0; j < (s-1-i); j++) {
            printf(" ");
        }

         for (int j = 0; j < (i+1); j++) {
            printf("*");
        }
         
        printf("\n");
   }
}

