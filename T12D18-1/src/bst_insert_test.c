#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void test_insert();

int main() {
#ifdef INSERT
    test_insert();
#endif
    return 0;
}

void test_insert() {
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
    printf("%d %d %p\n", test_1, root->data, root);
    printf("%d %d %p\n", test_right, root->right->data, root->right);
    printf("%d %d %p\n", test_left, root->left->data, root->left);
    printf("%d %d %p\n", test_left_right, root->left->right->data, root->left->right);
    bstree_free(root);
}