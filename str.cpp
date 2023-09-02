#include <stdio.h>
#include <string.h>
#include "my_asserts.h"
#include "str.h"


int my_puts(const char* str){
    my_assert(str != NULL, return EOF);
    int index = 0;
    while(str[index] != '\0'){
        putchar(str[index]);
        index++;
    }
    putchar('\n');
    return 1;
}

const char* my_strchr(const char* str, const char target_ch){
    my_assert(str != NULL, return NULL);

    size_t index = 0;
    while(str[index] != '\0' && str[index] != target_ch){
        index++;
    }
    if(str[index] == target_ch){
        return (str + index);
    }
    return NULL;
}

size_t my_strlen(const char* str){
    my_assert(str != NULL, return 0);

    size_t index = 0;
    while(str[index] != '\0'){
        index++;
    }
    return index;
}


char* my_strcpy(char* dest, const char* src){
    my_assert(src != dest, return NULL);
    my_assert(src != NULL, return NULL);
    my_assert(dest != NULL, return NULL);

    //int index = 0;

    memcpy(dest, src, my_strlen(src) + 1);

    /*while(src[index] != '\0'){ //TODO memcpy, test time
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';*/
    return dest;
}

char* my_strncpy(char* dest, const char* src, size_t count_symbols){
    my_assert(src != dest, return NULL);
    my_assert(src != NULL, return NULL);
    my_assert(dest != NULL, return NULL);

    size_t count_symbols_cp = 0;

    if(count_symbols < strlen(src)){
        count_symbols_cp = count_symbols;
    }
    else{
        count_symbols_cp = strlen(src);
    }

    memcpy(dest, src, count_symbols_cp);
    dest[count_symbols_cp] = '\0';
    /*size_t index = 0;
    while(src[index] != '\0' && index < count_symbols){
        dest[index] = src[index];
        index++;
    }
    for(; index < count_symbols; index++){
        dest[index] = '\0';
    }*/
    return dest;
}

char* my_strcat(char* dest, const char* src){
    my_assert(src != dest, return NULL);
    my_assert(src != NULL, return NULL);
    my_assert(dest != NULL, return NULL);

    size_t index_end_dest = 0;
    while(dest[index_end_dest] != '\0'){
        index_end_dest++;
    }

    memcpy(dest + index_end_dest, src, my_strlen(src));
    /*
    do{
        dest[index_end_dest + index_src] = src[index_src];
        index_src++;
    }while(src[index_src] != '\0');
    */
    return dest;
}

char* my_strncat(char* dest, const char* src, size_t count_symbols){
    my_assert(src != dest, return NULL);
    my_assert(src != NULL, return NULL);
    my_assert(dest != NULL, return NULL);

    size_t index_end_dest = 0;
    while(dest[index_end_dest] != '\0'){
        index_end_dest++;
    }


    size_t count_symbols_cp = 0;

    if(count_symbols < strlen(src)){
        count_symbols_cp = count_symbols;
    }
    else{
        count_symbols_cp = strlen(src);
    }

    memcpy(dest + index_end_dest, src, count_symbols_cp);

    /*size_t count_of_written_symbols = 0; // TODO conditional cmpilation
    size_t index_src = 0;

    while(src[index_src] != '\0' && count_of_written_symbols < count_symbols){
        dest[index_end_dest + index_src] = src[index_src];
        index_src++;
        count_of_written_symbols++;
    }
    */
    dest[index_end_dest + count_symbols_cp] = '\0';
    return dest;
}

char* my_fgets(char* str, size_t count_symbols, FILE* file){
    my_assert(file != NULL, return NULL);
    my_assert(str != NULL, return NULL);

    size_t index = 0;
    int input_char = getc(file);
    while(input_char != EOF && input_char != '\n' && index < count_symbols){
        str[index] = (char)input_char;
        index++;
        input_char = getc(file);
    }
    if(input_char == '\n' && index < count_symbols){
        str[index] = '\n';
        index++;
    }
    str[index] = '\0';
    return str;
}

char* my_strdup(const char* str){
    my_assert(str != NULL, return NULL);

    char* new_str = (char*)malloc((my_strlen(str) + 1) * sizeof(char)); // TODO use calloc
    my_assert(new_str != NULL,
        printf("No free memory\n"); // stderr
        return NULL;
    );

    size_t index = 0;

    do{
        new_str[index] = str[index];
        index++;
    }while(str[index] != '\0');

    return new_str;
}

char* buff_input_line(FILE* file){
    my_assert(file != NULL, return NULL);

    char* str = NULL;
    size_t len_of_str = 0;
    int input_char = getc(file);
    bool flag_continue_input = true;

    if(input_char == EOF){
        str = (char*)calloc(1, sizeof(char));
        str[0] = '\0';
        flag_continue_input = false;
    }
    if(input_char == '\n'){
        len_of_str = 1;
        str = (char*)calloc(2, sizeof(char));
        str[0] = '\n';
        str[1] = '\0';
        flag_continue_input = false;
    }

    while(flag_continue_input){
        str = (char*)realloc(str, len_of_str + BUFF_GETLINE + 1); // + 1 for \0 if last symbol in buffer is \n

        for(size_t i = 0; i < BUFF_GETLINE; i++){
            if(input_char == EOF){
                str[i + len_of_str] = '\0';
                flag_continue_input = false;
                break;
            }
            else if(input_char == '\n'){
                str[i + len_of_str] = '\n';
                flag_continue_input = false;
                str[i + len_of_str + 1] = '\0';
                break;
            }
            str[i + len_of_str] = (char)input_char;
            input_char = getc(file);
        }
        len_of_str += BUFF_GETLINE;
    }
    return str;
}

size_t my_getline(char **lineptr, size_t *size_of_lineptr, FILE* file){
    my_assert(lineptr != NULL, return 0);
    my_assert(size_of_lineptr != NULL, return 0);
    my_assert(file != NULL, return 0);

    char* str = buff_input_line(file);

    size_t size_of_new_lineptr = strlen(str) + 1;
    if(*size_of_lineptr < size_of_new_lineptr){
        *lineptr = (char*)realloc(*lineptr, size_of_new_lineptr);
        *size_of_lineptr = size_of_new_lineptr;
    }

    memcpy(*lineptr, str, size_of_new_lineptr);
    free(str);
    return strlen(*lineptr);
}








