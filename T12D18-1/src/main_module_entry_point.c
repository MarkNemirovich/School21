#include <stdio.h>
#include <stdlib.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
#ifdef Q1
    print_log(print_char, Module_load_success_message);
#elif Q2
    int* availability_mask = check_available_documentation_module(validate, Documents_count, Documents);

    print_docs(availability_mask, Documents_count, Documents);
    free(availability_mask);
#endif
    return 0;
}