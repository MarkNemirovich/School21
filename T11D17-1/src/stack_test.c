#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void test_push(struct Stack* head);
void test_pop(struct Stack* head);
void print(struct Stack* stack);

int main() {
    struct Stack* stack = NULL;
    stack = init();
    push(stack, 1);
    push(stack, 2);
    push(stack, 5);
#ifdef TESTING
    test_push(stack);
    test_pop(stack);
#endif
    destroy(stack);
    return 0;
}

void test_push(struct Stack* head) {
    // Arrange
    int a = 1, c = 3;
    char success = 1;
    // Act
    push(head, a);
    push(head, c);

    // Assert
    success &= head->top->data == c;
    success &= head->top->next->data == a;
    success &= head->top->next->next->data == 5;
    success &= head->top->next->next->next->next->next == NULL;
    printf("%s", success ? "SUCCESS\n" : "FAIL\n");
}

void test_pop(struct Stack* head) {
    // Arrange
    int a = 1, b = 2, c = 5, node1, node2;
    char success = 1;
    // Act
    node1 = pop(head);
    node2 = pop(head);

    // Assert
    success &= node1 == 3;
    success &= node2 == 1;
    success &= head->top->data == c;
    success &= head->top->next->data == b;
    success &= head->top->next->next->data == a;
    success &= head->top->next->next->next == NULL;
    printf("%s", success ? "SUCCESS\n" : "FAIL");
}