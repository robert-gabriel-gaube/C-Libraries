#include "headers/ordered_binary_tree.h"
#include <stdio.h>
int main() {
    ORDERED_BINARY_TREE tree = new_ordered_binary_tree();
    insert_ordered_binary_tree(&tree, 10);
    insert_ordered_binary_tree(&tree, 7);
    insert_ordered_binary_tree(&tree, 8);
    insert_ordered_binary_tree(&tree, 9);
    insert_ordered_binary_tree(&tree, 11);
    insert_ordered_binary_tree(&tree, 12);

    print_ordered_inorder_binary_tree(tree);

    remove_ordered_binary_tree(&tree, 10);
    print_ordered_inorder_binary_tree(tree);

    dealloc_ordered_binary_tree(tree);

    return 0;
}