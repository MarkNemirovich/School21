#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void sort(struct door** doors);
void swap(struct door* a, struct door* b);
void close(struct door* doors);
void print(struct door* doors);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    struct door* pointers[DOORS_COUNT];
    for (int i = 0; i < DOORS_COUNT; i++) pointers[i] = &doors[i];

    sort(pointers);
    close(doors);
    print(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort(struct door** doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        for (int j = 0; j < DOORS_COUNT - i - 1; j++) {
            if (doors[j]->id > doors[j + 1]->id) swap(doors[j], doors[j + 1]);
        }
    }
}

void swap(struct door* a, struct door* b) {
    struct door temp = *a;
    *a = *b;
    *b = temp;
}

void close(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT; i++) doors[i].status = 0;
    ;
}

void print(struct door* doors) {
    for (int i = 0; i < DOORS_COUNT - 1; i++) printf("%d, %d\n", doors[i].id, doors[i].status);
    printf("%d, %d\n", doors[DOORS_COUNT - 1].id, doors[DOORS_COUNT - 1].status);
}