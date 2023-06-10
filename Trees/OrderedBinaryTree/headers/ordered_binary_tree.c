#include "ordered_binary_tree.h"
#include <stdlib.h>
#include <stdio.h>


ORDERED_BINARY_TREE new_ordered_binary_tree() {
    ORDERED_BINARY_TREE tree;
    tree.root = NULL;
    return tree;
}

//======================================

void insert_ordered_binary_tree(ORDERED_BINARY_TREE *tree, int value) {
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    if(new_node == NULL) logger(Error, "Not enough space is available");

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if (tree->root == NULL) {
        tree->root = new_node;
    } else {
        NODE **current_node = &(tree->root);
        while(*current_node) {
            if(value < (*current_node)->value) {
                current_node = &((*current_node)->left);
            } else {
                current_node = &((*current_node)->right);
            }
        }
        *current_node = new_node;
    }
}

//======================================

void remove_ordered_binary_tree(ORDERED_BINARY_TREE *tree, int value) {
    if(tree->root == NULL) {
        logger(Warning, "Root node is null");
    } else {
        NODE **current_node = &(tree->root);
        while((*current_node) && (*current_node)->value != value) {
            if(value > (*current_node)->value) {
                current_node = &((*current_node)->right);
            } else {
                current_node = &((*current_node)->left);
            }
        }
        if(*current_node == NULL) {
            logger(Warning, "Value is not in the tree");
        } else {
            if((*current_node)->left == NULL && (*current_node)->right == NULL) {
                free(*current_node);
                *current_node = NULL;
            } else if((*current_node)->left == NULL) {
                NODE* aux_node = *current_node;
                *current_node = (*current_node) -> right;
                free(aux_node);
            } else if((*current_node)->right == NULL) {
                NODE* aux_node = *current_node;
                *current_node = (*current_node) -> left;
                free(aux_node);
            } else {
                NODE** replacement_node = &((*current_node)->left);
                while((*replacement_node)->right) {
                    replacement_node = &((*replacement_node) -> right);
                }   
                (*current_node)->value = (*replacement_node)->value;
                free(*replacement_node);
                *replacement_node = NULL;
            }
        }
    }
}

//======================================

void show_preorder_recursive(NODE const* node) {
    if(node) {
        printf("%d ", node->value);
        show_preorder_recursive(node->left);
        show_preorder_recursive(node->right);
    }
}

void print_ordered_preorder_binary_tree(ORDERED_BINARY_TREE binary_tree) {
    show_preorder_recursive(binary_tree.root);
    printf("\n");
}

//======================================

void show_postorder_recursive(NODE const* node) {
    if(node) {
        show_postorder_recursive(node->left);
        show_postorder_recursive(node->right);
        printf("%d ", node->value);
    }
}

void print_ordered_postorder_binary_tree(ORDERED_BINARY_TREE binary_tree) {
    show_postorder_recursive(binary_tree.root);
    printf("\n");
}

//======================================

void show_inorder_recursive(NODE const* node) {
    if(node) {
        show_inorder_recursive(node->left);
        printf("%d ", node->value);
        show_inorder_recursive(node->right);
    }
}

void print_ordered_inorder_binary_tree(ORDERED_BINARY_TREE binary_tree) {
    show_inorder_recursive(binary_tree.root);
    printf("\n");
}

//======================================

void dealloc_recursive(NODE* node) {
    if(node) {
        dealloc_recursive(node->left);
        dealloc_recursive(node->right);
        free(node);
    }
}

void dealloc_ordered_binary_tree(ORDERED_BINARY_TREE tree) {
    dealloc_recursive(tree.root);
}