#ifndef BINARY_TREE_H
#define BINART_TREE_H

#include "../../../Generals/generals.h"

typedef struct {
    float *elements;
    unsigned size;
}BINARY_TREE;

BINARY_TREE initialize_binary_tree();
void add_value_to_binary_tree(BINARY_TREE*, float value, float value_parent);
void delete_value_binary_tree(BINARY_TREE*, float value);
void show_binary_tree_preorder(BINARY_TREE);
void show_binary_tree_postorder(BINARY_TREE);
void show_binary_tree_inorder(BINARY_TREE);
void dealloc_binary_tree(BINARY_TREE*);

#endif