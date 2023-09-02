#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include "str.h"
#ifdef TEST
    #include "tests_for_my_strings.h"
#endif


int main(){

    #ifdef TEST
        FILE* file = fopen("tests_strings.txt", "r");
        if(file == NULL){
            printf("No such file\n");
        }
        else{
            test(file);
        }
    #endif

}
