#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculate.h"
#include "draw.h"
#include "my_stack.h"

int main() {
    char **graph = callocMatrix(HEIGHT, WIDTH + 1);  // macro in the draw
    int correct = graph != NULL;
    struct st *operations = NULL;                                  // operators list
    char input_string[MAX_STRING], output_string[3 * MAX_STRING];  // macro in the my_stack
    scanf("%s", input_string);

    correct = parseToPolish(operations, input_string, output_string);
    if (correct) {
        HEAD head;
        init(&head);
        initGraph(graph, HEIGHT, WIDTH);
        correct = addFuncForGraph(graph, HEIGHT, WIDTH, output_string, &head);
    }
    if (correct) {
        drawGraph(graph, HEIGHT);
        printf("\nPostfix notation:%s", output_string);
    } else {
        drawEmptyGraph(HEIGHT);
        printf("Something wrong in your equation :(");
    }
    freeMatrix(graph, HEIGHT);
    return 0;
}
