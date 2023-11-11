#ifndef BST_MODULE_H
#define BST_MODULE_H

typedef struct Branch {
    int data;
    struct Branch* right;
    struct Branch* left;
} t_btree;

t_btree* bstree_create_node(int item);
int int_comparer(int, int);
void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int));
void bstree_free(t_btree* elem);
void bstree_apply_infix(t_btree* root, void (*applyf)(int));
void bstree_apply_prefix(t_btree* root, void (*applyf)(int));
void bstree_apply_postfix(t_btree* root, void (*applyf)(int));
void print(int);
#endif