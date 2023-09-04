#pragma once

const size_t size_of_arrays_in_tests = 200;

struct TEST_STRING{
    char* request;
    char* arg_str1;
    char* arg_char;
    size_t* arg_size_t;
    FILE* arg_file;
};

void test(FILE* file);
TEST_STRING* input_test(FILE* file);
bool check_results(const TEST_STRING* one_test);
void destr_TEST_STRING(TEST_STRING* one_test);
