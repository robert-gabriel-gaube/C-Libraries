#include "binary_tree.h"
#include <float.h>
#include <stdlib.h>
#define INF FLT_MAX

//############# 
//# Utilities #
//#############

float get_value(BINARY_TREE binary_tree, unsigned index) {
    return binary_tree.elements[index];
}
unsigned get_size(BINARY_TREE binary_tree) {
    return binary_tree.size;
}
void set_value(BINARY_TREE *binary_tree, unsigned index, float value) {
    binary_tree -> elements[index] = value;
}

unsigned max(unsigned a, unsigned b) {
    return a > b ? a : b;
}

unsigned get_node_position_by_value(BINARY_TREE binary_tree, float value, unsigned index) {
    if(index < binary_tree.size && get_value(binary_tree, index) != INF) {
        if(get_value(binary_tree, index) == value) {
            return index;
        } else {
            return max(get_node_position_by_value(binary_tree, value, index * 2),
                       get_node_position_by_value(binary_tree, value, index * 2 + 1));
        }
    }
    return 0;
}

void resize_binary_tree(BINARY_TREE* binary_tree, unsigned new_size) {
    unsigned i;
    if(new_size < binary_tree -> size) {
        logger(Warning, "Resize with smaller size");
    }
    binary_tree -> elements = (float*)realloc(binary_tree -> elements, new_size * (sizeof(float)));
    for(i = get_size(*binary_tree); i < new_size; ++i) {
        set_value(binary_tree, i, INF);
    }   
    binary_tree -> size = new_size;
}

//###################################### 
//# Implementation of header functions #
//######################################

BINARY_TREE initialize_binary_tree() {
    BINARY_TREE binary_tree;
    binary_tree.elements = NULL;
    binary_tree.size = 0;
    return binary_tree;
}

//======================================

void add_value_to_binary_tree(BINARY_TREE* binary_tree, float value, float value_parent) {
    if(binary_tree -> size == 0) {
        resize_binary_tree(binary_tree, 2);
        set_value(binary_tree, 1, value);
    } else {
        unsigned parent_position = get_node_position_by_value(*binary_tree, value_parent, 1);
        if(parent_position == INF) {
            char message[100];
            sprintf(message, "There isn't a node with the value %f in the binary tree.", value_parent);
            logger(Warning, message);
            return;
        } else {
            unsigned size = get_size(*binary_tree);
            if(parent_position * 2 + 1 >= size) {
                resize_binary_tree(binary_tree, parent_position * 2 + 2);
            }

            if(get_value(*binary_tree, parent_position * 2) == INF) {
                set_value(binary_tree, parent_position * 2, value);
            } else if(get_value(*binary_tree, parent_position * 2 + 1) == INF) {
                set_value(binary_tree, parent_position * 2 + 1, value);
            } else {
                char message[100];
                sprintf(message, "The node with the value %f already has 2 children.", value_parent);
                logger(Warning, message);
            }
        }
    }
}

//======================================

void set_subtree_null(BINARY_TREE *binary_tree, unsigned index) {
    if(index < get_size(*binary_tree) && get_value(*binary_tree, index) != INF) {
        set_value(binary_tree, index, INF);
        set_subtree_null(binary_tree, index * 2);
        set_subtree_null(binary_tree, index * 2 + 1);
    }
}

void delete_value_binary_tree(BINARY_TREE *binary_tree, float value) {
    unsigned position = get_node_position_by_value(*binary_tree, value, 1);
    if(position == 0) {
        logger(Warning, "Value is not present in the tree");
    } else {
        set_subtree_null(binary_tree, position);
    }
}

//======================================

void show_preorder_recursive(BINARY_TREE binary_tree, unsigned index) {
    if(index < get_size(binary_tree) && get_value(binary_tree, index) != INF) {
        printf("%f ", get_value(binary_tree, index));
        show_preorder_recursive(binary_tree, index * 2);
        show_preorder_recursive(binary_tree, index * 2 + 1);
    }
}

void show_binary_tree_preorder(BINARY_TREE binary_tree) {
    show_preorder_recursive(binary_tree, 1);
    printf("\n");
}

//======================================

void show_postorder_recursive(BINARY_TREE binary_tree, unsigned index) {
    if(index < get_size(binary_tree) && get_value(binary_tree, index) != INF) {
        show_postorder_recursive(binary_tree, index * 2);
        show_postorder_recursive(binary_tree, index * 2 + 1);
        printf("%f ", get_value(binary_tree, index));
    }
}

void show_binary_tree_postorder(BINARY_TREE binary_tree) {
    show_postorder_recursive(binary_tree, 1);
    printf("\n");
}

//======================================

void show_inorder_recursive(BINARY_TREE binary_tree, unsigned index) {
    if(index < get_size(binary_tree) && get_value(binary_tree, index) != INF) {
        show_inorder_recursive(binary_tree, index * 2);
        printf("%f ", get_value(binary_tree, index));
        show_inorder_recursive(binary_tree, index * 2 + 1);
    }
}

void show_binary_tree_inorder(BINARY_TREE binary_tree) {
    show_inorder_recursive(binary_tree, 1);
    printf("\n");
}

//======================================

void dealloc_binary_tree(BINARY_TREE* binary_tree) {
    free(binary_tree -> elements);
    binary_tree -> elements = NULL;
}