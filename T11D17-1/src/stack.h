#ifndef DOOR_STACK_H
#define DOOR_STACK_H

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

struct Stack* init();
void push(struct Stack* head, int value);
int pop(struct Stack* head);
void destroy(struct Stack* head);
struct Node* newNode(int data);

#endif