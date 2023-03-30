#include <stdio.h>
#include <stdlib.h>
#include "headers/general_tree.h"
#include "../../Generals/generals.h"
#define FILENAME "tree.txt"

int main() {
    // Initializations
    GENERAL_TREE tree = initialize_general_tree();
    FILE *input_file = open_file(FILENAME);

    char line[20], *start_second_number = NULL;
    unsigned parent, child;

    // We have to add the first row seperatelly
    // because add_new_node() adds only the root when it's 
    // used for the first time.

    read_line_from_file(input_file, line);
    parent = strtol(line, &start_second_number, 10);

    child = strtol(start_second_number + 1, NULL, 10);
    add_new_node(&tree, parent, 0); // Add root
    add_new_node(&tree, child, parent); // Add the first child of root
    
    // Continue as usual
    while(!feof(input_file)) { 
        read_line_from_file(input_file, line);
        parent = strtol(line, &start_second_number, 10);

        child = strtol(start_second_number + 1, NULL, 10);
        add_new_node(&tree, child, parent);
    }
    close_file(input_file);
    
    // Invalid node
    add_new_node(&tree, 90, 98);

    // Some operations used
    printf("Height is: %u\n", tree_height(tree));
    printf("Degree is: %u\n", tree_degree(tree));

    printf("Inorder: "); show_tree_in_inorder(tree);
    printf("Postorder: "); show_tree_in_postorder(tree);
    printf("Preorder: "); show_tree_in_preorder(tree);

    delete_node_after_value(&tree, 6); printf("\n");
    logger(Information, "Deleted node and subtree which had value = 6");

    printf("New tree preorder: "); show_tree_in_preorder(tree);
    printf("New height is: %u\n", tree_height(tree));
    printf("New degree is: %u\n", tree_degree(tree));

    // Post-use 
    dealloc_tree(&tree);

    return 0;
}