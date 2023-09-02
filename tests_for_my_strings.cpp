#include <stdio.h>
#include <string.h>
#include "str.h"
#include "my_asserts.h"
#include "tests_for_my_strings.h"

void test(FILE* file){
    TEST_STRING* ex_test;
    for(int i = 1; (ex_test = input_test(file)) != NULL; i++){
        if(check_results(ex_test)){
            printf("Test №%d is OK\n", i);
        }
        else{
            printf("ERROR IN TEST №%d\n", i);
        }
        free(ex_test->request);
        free(ex_test->arg_str1);
        free(ex_test->arg_char);
        free(ex_test->arg_size_t);
        free(ex_test);
    }
}

TEST_STRING* input_test(FILE* file){
    my_assert(file != NULL, return NULL);

    TEST_STRING* one_test = (TEST_STRING*)calloc(sizeof(TEST_STRING), 1);
    *one_test = {(char*)calloc(size_of_arrays_in_tests, 1), (char*)calloc(size_of_arrays_in_tests, 1), (char*)calloc(1, 1), (size_t*)calloc(1, sizeof(size_t)), file};

    fgets(one_test->request, size_of_arrays_in_tests, file);
    if(strcmp(one_test->request, "my_puts\n") == 0 || strcmp(one_test->request, "my_strlen\n") == 0 || strcmp(one_test->request, "my_strcpy\n") == 0 || strcmp(one_test->request, "my_strcat\n") == 0 || strcmp(one_test->request, "my_strdup\n") == 0){
        fgets(one_test->arg_str1, size_of_arrays_in_tests - 1, file);
    }
    else if(strcmp(one_test->request, "my_strncpy\n") == 0 || strcmp(one_test->request, "my_strncat\n") == 0){
        fgets(one_test->arg_str1, size_of_arrays_in_tests - 1, file);
        fscanf(file, "%zu", one_test->arg_size_t);
        getc(file);
    }
    else if(strcmp(one_test->request, "my_strchr\n") == 0){
        fgets(one_test->arg_str1, size_of_arrays_in_tests - 1, file);
        *(one_test->arg_char) = (char)getc(file);
        getc(file);
        /*fscanf(file, "%c", one_test->arg_char);
        getc(file);*/
    }
    else if(strcmp(one_test->request, "my_fgets\n") == 0){
        fscanf(file, "%zu", one_test->arg_size_t);
        getc(file);
    }
    else if(strcmp(one_test->request, "my_getline\n") == 0){}   // getline get information themselves
    else{
        printf("%s", one_test->request);

        free(one_test->request);
        free(one_test->arg_str1);
        free(one_test->arg_char);
        free(one_test->arg_size_t);
        free(one_test);
        return NULL;
    }
    printf("%s", one_test->request);
    return one_test;
}

bool check_results(const TEST_STRING* one_test){
    my_assert(one_test != NULL, return false);

    if(strcmp(one_test->request, "my_puts\n") == 0){
        if((my_puts(one_test->arg_str1) >= 0 && puts(one_test->arg_str1) >= 0) or (my_puts(one_test->arg_str1) < 0 && puts(one_test->arg_str1) < 0)){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strlen\n") == 0){
        if(my_strlen(one_test->arg_str1) == strlen(one_test->arg_str1)){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strcpy\n") == 0){
        char for_my_dest[size_of_arrays_in_tests] = "";
        char for_dest[size_of_arrays_in_tests] = "";
        if(strcmp(my_strcpy(for_my_dest, one_test->arg_str1), strcpy(for_dest, one_test->arg_str1)) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strncpy\n") == 0){
        char for_my_dest[size_of_arrays_in_tests] = "";
        char for_dest[size_of_arrays_in_tests] = "";
        if(strcmp(my_strncpy(for_my_dest, one_test->arg_str1, *(one_test->arg_size_t)), strncpy(for_dest, one_test->arg_str1, *(one_test->arg_size_t))) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strchr\n") == 0){
        if(strcmp(my_strchr(one_test->arg_str1, *(one_test->arg_char)) ,strchr(one_test->arg_str1, *(one_test->arg_char))) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strcat\n") == 0){
        char for_my_dest[size_of_arrays_in_tests] = "";
        char for_dest[size_of_arrays_in_tests] = "";
        if(strcmp(my_strcat(for_my_dest, one_test->arg_str1), strcat(for_dest, one_test->arg_str1)) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strncat\n") == 0){
        char for_my_dest[size_of_arrays_in_tests] = "";
        char for_dest[size_of_arrays_in_tests] = "";
        if(strcmp(my_strncat(for_my_dest, one_test->arg_str1, *(one_test->arg_size_t)), strncat(for_dest, one_test->arg_str1, *(one_test->arg_size_t))) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_fgets\n") == 0){
        char str1_to_write[size_of_arrays_in_tests] = "";
        char str2_to_write[size_of_arrays_in_tests] = "";
        my_fgets(str1_to_write, *(one_test->arg_size_t), one_test->arg_file);
        fseek(one_test->arg_file, -(int)strlen(str1_to_write), SEEK_CUR);
        fgets(str2_to_write, (int)*(one_test->arg_size_t), one_test->arg_file);

        if(strcmp(str1_to_write, str2_to_write) == 0){
            return true;
        }
    }
    else if(strcmp(one_test->request, "my_strdup\n") == 0){
        char* str1 = my_strdup(one_test->arg_str1);
        char* str2 = strdup(one_test->arg_str1);
        if(strcmp(str1, str2) == 0){
            free(str1);
            free(str2);
            return true;
        }
        free(str1);
        free(str2);
    }
    else if(strcmp(one_test->request, "my_getline\n") == 0){
        char* str1_to_write = (char*)calloc(size_of_arrays_in_tests, 1);
        char* str2_to_write = (char*)calloc(size_of_arrays_in_tests, 1);
        size_t len_of_mass = size_of_arrays_in_tests;

        size_t len1 = my_getline(&str1_to_write, &len_of_mass, one_test->arg_file);
        fseek(one_test->arg_file, -((int)strlen(str1_to_write)), SEEK_CUR);
        size_t len2 = (size_t)getline(&str2_to_write, &len_of_mass, one_test->arg_file);

        if(len1 == len2 && strcmp(str1_to_write, str2_to_write) == 0){
            free(str1_to_write);
            free(str2_to_write);
            return true;
        }
        free(str1_to_write);
        free(str2_to_write);
    }


    return false;
}
