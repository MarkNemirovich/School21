#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack* init() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(struct Stack* stack, int data) {
    struct Node* node = newNode(data);
    node->next = stack->top;
    stack->top = node;
}

int pop(struct Stack* stack) {
    struct Node* temp = NULL;
    int value = 0;
    if (stack->top) {
        temp = stack->top;
        value = temp->data;
        stack->top = temp->next;
    }
    return value;
}

void destroy(struct Stack* stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}