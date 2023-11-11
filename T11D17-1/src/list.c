#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    root->door = *door;
    root->next = NULL;
    return root;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* append = (struct node*)malloc(sizeof(struct node));
    append->door = *door;
    append->next = elem->next;
    elem->next = append;
    while (append->next != NULL) append = append->next;
    return append;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* p = root;
    int i = 0;
    for (; i < door_id && p != NULL; i++) p = p->next;
    if (i != door_id) p = NULL;
    return p;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* p = root;
    if (root == elem) {
        root = root->next;
    } else {
        while (p != NULL && p->next != elem) {
            p = p->next;
        }
        if (p != NULL) {
            p->next = elem->next;
            free(elem);
        }
    }
    return root;
}

void destroy(struct node* root) {
    struct node* p = root;
    struct node* t;
    while (p != NULL) {
        t = p;
        p = p->next;
        free(t);
    }
    root = NULL;
}