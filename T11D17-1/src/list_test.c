#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void test_adding(struct node* root, struct node* current, struct door* doors);
void test_removing(struct node* root, struct node* current);
void initialize_doors(struct door* doors);
void print(struct node* list);

int main() {
    struct node* root = NULL;
    struct node* current = NULL;
    struct door doors[DOORS_COUNT];
    initialize_doors(doors);

    root = init(doors);
    current = root;
    current = add_door(current, &doors[1]);
    current = add_door(current, &doors[2]);
    current = add_door(current, &doors[3]);
    current = add_door(current, &doors[4]);
#ifdef DEBUG
    test_adding(root, current, doors);
    test_removing(root, current);
#endif
    destroy(root);
    return 0;
}

void test_adding(struct node* root, struct node* current, struct door* doors) {
    // Arrange
    struct node* rootA = (root->next);
    struct node* fourthA = find_door(4, root);
    char success = 1;
    // Act
    current = add_door(root, &doors[5]);
    add_door(find_door(3, root), &doors[6]);
    add_door(current, &doors[7]);

    // Assert
    success &= find_door(1, root)->next == rootA;
    success &= find_door(4, root)->next != fourthA && find_door(5, root)->next == fourthA;
    success &= find_door(7, root)->next == NULL;
    printf("%s", success ? "SUCCESS\n" : "FAIL\n");
}

void test_removing(struct node* root, struct node* current) {
    // Arrange
    struct node* rootA = (root->next);
    struct node* fourthA = find_door(5, root);
    char success = 1;

    // Act
    root = remove_door(root, root);
    root = remove_door(find_door(3, root), root);
    root = remove_door(current, root);

    // Assert
    success &= find_door(0, root) == rootA;
    success &= find_door(3, root) == fourthA && find_door(4, root)->next != fourthA;
    success &= find_door(4, root)->next == NULL;
    printf("%s", success ? "SUCCESS\n" : "FAIL");
}

void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void print(struct node* root) {
    while (root != NULL) {
        printf("%d, %d, %p, %p\n", root->door.id, root->door.status, root, root->next);
        root = root->next;
    }
}