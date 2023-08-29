#pragma once

enum BUFF_SIZE{
    BUFF_GETLINE = 24
};

int my_puts(const char str[]);
const char* my_strchr(const char str[], const char tarhet_ch);
size_t my_strlen(const char str[]);
char* my_strcpy(char dest[], const char src[]);
char* my_strncpy(char dest[], const char src[], size_t count_symbols);
char* my_strcat(char dest[], const char src[]);
char* my_strncat(char dest[], const char src[], size_t count_symbols);
char* my_fgets(char* str, size_t count_symbols, FILE* file);
char* my_strdup(const char* str);
size_t my_getline(char** lineptr, size_t* len, FILE* file);


