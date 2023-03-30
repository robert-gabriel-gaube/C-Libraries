#include "general_tree.h"
#include <stdlib.h>
#include <stdio.h>

// Prototype for some implementation which use these functions
// before the definition is actually implemented.
void dealloc_tree_recursive(NODE_P root);


//############# 
//# Utilities #
//#############

NODE_P create_new_node(unsigned value) {
    NODE_P node = (NODE_P)malloc(sizeof(NODE));
    if(node == NULL) logger(Error, "Not enough space");

    node -> first_child= NULL;
    node -> right_brother = NULL;
    node -> parent = NULL;
    node -> value = value;

    return node;
}

// Returns an address to the NODE* that has the searched value
// or NULL if it doesn't exist. In other words returns a NODE**.
NODE_P* get_node_by_value(NODE_P* root, unsigned value) {
    if((*root) != NULL) {
        if((*root) -> value == value) {
            return root;
        }
        NODE_P *child = &((*root) -> first_child), *returned_node;
        while((*child) != NULL) {
            returned_node = get_node_by_value(child, value);
            if(returned_node != NULL) {
                return returned_node;
            }
            child = &((*child) -> right_brother);
        }
    }
    return NULL;
}

// Returns an address to the NODE* which is the first null child 
// of the node parent. In other words returns a NODE**.
NODE_P* get_first_null_child(NODE_P* parent) {
    if(parent == NULL || *parent == NULL) return NULL;

    NODE_P* child = &((*parent) -> first_child);
    while((*child) != NULL) {
        child = &((*child) -> right_brother);
    }
    return child;
}

// Degree = Number of children
unsigned node_degree(NODE_P node) {
    unsigned degree = 0;
    NODE_P child = node -> first_child;
    while(child != NULL) {
        child = child -> right_brother;
        degree++;
    }
    return degree;
}

void set_parent(NODE_P node, NODE_P parent) {
    node -> parent = parent;
}
void set_first_child(NODE_P node, NODE_P first_child) {
    node -> first_child = first_child;
}
void set_right_brother(NODE_P node, NODE_P right_brother) {
    node -> right_brother = right_brother;
}

unsigned max(unsigned a, unsigned b) {
    return a > b ? a : b;
}

//###################################### 
//# Implementation of header functions #
//######################################

GENERAL_TREE initialize_general_tree() {
    GENERAL_TREE tree;
    tree.root = NULL;
    return tree;
}

//======================================

void add_new_node(GENERAL_TREE* tree, unsigned value, unsigned value_parent) {
    if(tree -> root == NULL) {
        tree -> root = create_new_node(value);
    } else {
        NODE_P *parent = get_node_by_value(&(tree -> root), value_parent);
        if(parent == NULL) {
            char message[100];
            sprintf(message, "No node in the tree with this value %u", value_parent);
            logger(Warning, message);
            return;
        }
        NODE_P *child = get_first_null_child(parent);
        *child = create_new_node(value);
        set_parent(*child, *parent);
    }
}

//======================================

int is_null(GENERAL_TREE tree) {
    return (tree.root == NULL);
}

//======================================

void delete_node_after_value(GENERAL_TREE* tree, unsigned value) {
    NODE_P *node = get_node_by_value(&(tree -> root), value);
    dealloc_tree_recursive(*node);
    *node = NULL;
}

//======================================

unsigned tree_height_recursive(NODE_P root, unsigned level) {
    if(root != NULL) {
        return max(tree_height_recursive(root -> first_child, level + 1),
                   tree_height_recursive(root -> right_brother, level));
    }
    return level - 1;
}
unsigned tree_height(GENERAL_TREE tree) {
    return tree_height_recursive(tree.root, 1); 
}

//======================================

// Tree Degree = The maximum degree of any node in the tree
unsigned tree_degree_recursive(NODE_P root) {
    if(root != NULL) {
        return max(node_degree(root),
                   max(tree_degree_recursive(root -> first_child),
                       tree_degree_recursive(root -> right_brother)));
    }
    return 0;
}

unsigned tree_degree(GENERAL_TREE tree) {
    return tree_degree_recursive(tree.root); 
}

//======================================

void show_preorder_recursive(NODE_P root) {
    if(root != NULL) {
        printf("%u ", root -> value);
        show_preorder_recursive(root -> first_child);
        show_preorder_recursive(root -> right_brother);
    }
}

void show_tree_in_preorder(GENERAL_TREE tree) {
    show_preorder_recursive(tree.root);
    printf("\n");
}

//======================================

void show_postorder_recursive(NODE_P root) {
    if(root != NULL) {
        show_postorder_recursive(root -> first_child);
        printf("%u ", root -> value);
        show_postorder_recursive(root -> right_brother);
    }
}

void show_tree_in_postorder(GENERAL_TREE tree) {
    show_postorder_recursive(tree.root);
    printf("\n");
}

//======================================

void show_inorder_recursive(NODE_P root) {
    if(root != NULL) {
        if(root -> first_child == NULL) {
            printf("%u ", root -> value);
        } else {
            show_inorder_recursive(root -> first_child);
            printf("%u ", root -> value);
            NODE_P child = root -> first_child;
            while(child -> right_brother != NULL) {
                show_inorder_recursive(child -> right_brother);
                child = child -> right_brother;
            }
        }
    }
}

void show_tree_in_inorder(GENERAL_TREE tree) {
    show_inorder_recursive(tree.root);
    printf("\n");
}

//======================================

void dealloc_tree_recursive(NODE_P root) {
    if(root != NULL) {
        dealloc_tree_recursive(root -> first_child);
        dealloc_tree_recursive(root -> right_brother);
        free(root);
    }
}

void dealloc_tree(GENERAL_TREE *tree) {
    dealloc_tree_recursive(tree -> root);
    tree -> root = NULL;
}