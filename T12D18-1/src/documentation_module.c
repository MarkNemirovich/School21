#include "documentation_module.h"

#include <stdarg.h>

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int (*validate)(char*), int document_count, ...) {
    int* mask = malloc(document_count * sizeof(int));
    if (document_count < Max_Documents_count && mask != NULL) {
        va_list docs;
        va_start(docs, document_count);
        for (int i = 0; i < document_count; i++) {
            mask[i] = validate(va_arg(docs, char*));
        }
        va_end(docs);
    }
    return mask;
}

void print_docs(int* avaliable, int document_count, ...) {
    va_list docs;
    va_start(docs, document_count);
    for (int i = 0; i < document_count; i++) {
        printf("[%s: %savailable]", va_arg(docs, char*), avaliable[i] ? "" : "un");
        if (i != document_count - 1) printf("\n");
    }
    va_end(docs);
}