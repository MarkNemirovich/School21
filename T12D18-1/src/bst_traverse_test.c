#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void test_traverse();

int main() {
#ifdef TRAVERSE
    test_traverse();
#endif
    return 0;
}

void test_traverse() {
    // Arrange
    int test_1 = 10;
    int test_right = 16;
    int test_left = 2;
    int test_left_right = 6;
    // Act
    t_btree* root = bstree_create_node(test_1);
    bstree_insert(root, test_right, int_comparer);
    bstree_insert(root, test_left, int_comparer);
    bstree_insert(root, test_left_right, int_comparer);

    // Assert
    bstree_apply_infix(root, print);
    printf("\n");
    bstree_apply_prefix(root, print);
    printf("\n");
    bstree_apply_postfix(root, print);
    bstree_free(root);
}