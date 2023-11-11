#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void test_create();

int main() {
#ifdef CREATE
    test_create();
#endif
    return 0;
}

void test_create() {
    // Arrange
    int test_1 = 10;
    int test_2 = 6;
    // Act
    t_btree* branch1 = bstree_create_node(test_1);
    t_btree* branch2 = bstree_create_node(test_2);

    // Assert
    printf("%d %d %p\n", test_1, branch1->data, branch1);
    printf("%d %d %p", test_2, branch2->data, branch2);
    free(branch1);
    free(branch2);
}