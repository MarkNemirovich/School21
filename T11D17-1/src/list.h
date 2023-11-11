#ifndef DOOR_LIST_H
#define DOOR_LIST_H

struct door {
    int id;
    int status;
};

struct node {
    struct node* next;
    struct door door;
};

struct node* init(struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);

#endif