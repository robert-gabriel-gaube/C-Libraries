#include <stdio.h>
#include "headers/binary_tree.h" 

int main() {
    BINARY_TREE tree = initialize_binary_tree();
    add_value_to_binary_tree(&tree, 1, 1);
    add_value_to_binary_tree(&tree, 2, 1);
    add_value_to_binary_tree(&tree, 3, 1);
    add_value_to_binary_tree(&tree, 4, 1);

    add_value_to_binary_tree(&tree, 5, 3);
    add_value_to_binary_tree(&tree, 6, 3);

    add_value_to_binary_tree(&tree, 7, 5);
    add_value_to_binary_tree(&tree, 8, 5);

    show_binary_tree_preorder(tree);
    show_binary_tree_inorder(tree);
    show_binary_tree_postorder(tree);

    delete_value_binary_tree(&tree, 5);

    show_binary_tree_preorder(tree);

    dealloc_binary_tree(&tree);
    return 0;
}