#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include "str.h"


#define test(func(args)) \
    if (my_##func(args) != func(args))\
        printf("ERROR!\n");

int main(){

/*
    char str1[100] = "HEL";
    char str2[100] = "LO";

    printf("%s", my_strncat(str2, str1, 5));
*//*

    char src[100000];
    char dest[100000];
    for(int i = 0; i < 99999; i++){
        src[i] = 'a';
    }
    src[99999] = '\0';

    double time_spent = 0
    ;
    clock_t begin = clock();
    my_strcpy(dest, src);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf", time_spent);
*/
    test(strlen("HELLO WORLD"));



    /*char* str2 = (char*)malloc(4);
    str2[0] = 'f';
    str2[1] = 'q';
    size_t len = 4;
    printf("%zd", getline(&str2, &len, stdin));
    printf("%s", str2);
    free(str2);
*/


}
