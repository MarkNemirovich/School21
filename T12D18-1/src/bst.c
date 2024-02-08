#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

t_btree* bstree_create_node(int item) {
    t_btree* newBranch = (t_btree*)malloc(sizeof(t_btree));
    newBranch->data = item;
    newBranch->right = NULL;
    newBranch->left = NULL;
    return newBranch;
}

int int_comparer(int a, int b) { return a - b; }
void print(int a) { printf("%d ", a); };

void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int)) {
    t_btree* ptr = root;
    char inserted = 0;
    while (!inserted && ptr != NULL)
        if (cmpf(ptr->data, item) > 0) {
            if (ptr->left == NULL) {
                ptr->left = bstree_create_node(item);
                inserted = 1;
            }
            ptr = ptr->left;
        } else {
            if (ptr->right == NULL) {
                ptr->right = bstree_create_node(item);
                inserted = 1;
            }
            ptr = ptr->right;
        }
}

void bstree_free(t_btree* elem) {
    if (elem != NULL) {
        bstree_free(elem->left);
        bstree_free(elem->right);
        free(elem);
    }
}
void bstree_apply_infix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        bstree_apply_infix(root->left, applyf);
        applyf(root->data);
        bstree_apply_infix(root->right, applyf);
    }
}
void bstree_apply_prefix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        applyf(root->data);
        bstree_apply_infix(root->left, applyf);
        bstree_apply_infix(root->right, applyf);
    }
}
void bstree_apply_postfix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL) {
        bstree_apply_infix(root->left, applyf);
        bstree_apply_infix(root->right, applyf);
        applyf(root->data);
    }
}