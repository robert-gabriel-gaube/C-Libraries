#ifndef ORDERED_BINARY_TREE_H
#define ORDERED_BINARY_TREE_H
#include "../../../Generals/generals.h"

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
}NODE;

typedef struct tree {
    NODE *root;
}ORDERED_BINARY_TREE;

ORDERED_BINARY_TREE new_ordered_binary_tree();
void insert_ordered_binary_tree(ORDERED_BINARY_TREE *tree, int value);
void remove_ordered_binary_tree(ORDERED_BINARY_TREE *tree, int value); // WIP
void print_ordered_preorder_binary_tree(ORDERED_BINARY_TREE tree);
void print_ordered_inorder_binary_tree(ORDERED_BINARY_TREE tree);
void print_ordered_postorder_binary_tree(ORDERED_BINARY_TREE tree);
void dealloc_ordered_binary_tree(ORDERED_BINARY_TREE tree);

#endif /* ORDERED_BINARY_TREE_H */