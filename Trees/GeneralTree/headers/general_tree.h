#ifndef GENERAL_TREE_H
#define GENERAL_TREE_H

#include "../../../Generals/generals.h"

typedef struct node {
    struct node *first_child, *right_brother, *parent;
    unsigned value;
}NODE;

typedef NODE* NODE_P;

typedef struct {
    NODE_P root;
}GENERAL_TREE;

GENERAL_TREE initialize_general_tree();
void add_new_node(GENERAL_TREE*, unsigned value, unsigned value_parent);
int is_null(GENERAL_TREE);
void delete_node_after_value(GENERAL_TREE*, unsigned value);
unsigned tree_height(GENERAL_TREE);
unsigned tree_degree(GENERAL_TREE);
void show_tree_in_preorder(GENERAL_TREE);
void show_tree_in_postorder(GENERAL_TREE);
void show_tree_in_inorder(GENERAL_TREE);
void dealloc_tree(GENERAL_TREE*);

#endif