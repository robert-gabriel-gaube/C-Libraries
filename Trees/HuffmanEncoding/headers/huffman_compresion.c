#include "huffman_compresion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_CHARACTERS 27

typedef struct{
    unsigned frequency;
    char encoding[10];
}HUFFMAN_CHARACTER;

typedef struct node {
    char character;
    unsigned frequency;
    struct node *left, *right;
}NODE;

typedef NODE* NODE_P;
define_priority_queue(NODE_P);

struct huffman_encoding {
    HUFFMAN_CHARACTER characters[NUMBER_CHARACTERS];
    NODE_P huffman_tree;
};

//############# 
//# Utilities #
//#############

unsigned character_position(const char character) {
    if(character == ' ') return NUMBER_CHARACTERS - 1;
    else if(character >= 'A' && character <= 'Z') return character - 'A';
    else logger(Error, "Character not recognized");   
    return 0;
}

char position_character(const unsigned index) {
    if(index == NUMBER_CHARACTERS - 1) return ' ';
    else if(index < NUMBER_CHARACTERS) return 'A' + index;
    else logger(Error, "Index not recognized");
    return 0;
}

int frequency_condition(NODE_P a, NODE_P b) {
    return b->frequency - a->frequency;
}

void print_huffman_tree(NODE_P root) {
    if(root != NULL) {
        printf("%c(%d) ", root->character, root->frequency);
        print_huffman_tree(root->left);
        print_huffman_tree(root->right);
    }
}

void dealloc_huffman_tree(NODE_P root) {
    if(root != NULL) {
        dealloc_huffman_tree(root->left);
        dealloc_huffman_tree(root->right);
        free(root);
    }
}
void store_encoding(NODE_P root, HUFFMAN_ENCODING huffman_encoding, char* encoding, unsigned step) {
    if(root != NULL) {
        if(root->character != '-') {
            unsigned index = character_position(root->character);
            strncpy(huffman_encoding->characters[index].encoding, encoding, step);
            huffman_encoding->characters[index].encoding[step + 1] = 0;
        }
        encoding[step] = '0';
        store_encoding(root->left, huffman_encoding, encoding, step + 1);
        encoding[step] = '1';
        store_encoding(root->right, huffman_encoding, encoding, step + 1);
    }
}

NODE_P create_new_node(char character, unsigned frequency, NODE_P left, NODE_P right) {
    NODE_P new_node = (NODE_P)malloc(sizeof(NODE));
    if(new_node == NULL) logger(Error, "Not enough space");
    new_node -> character = character;
    new_node -> frequency = frequency;
    new_node -> left = left;
    new_node -> right = right;
    return new_node;
}

//###################################### 
//# Implementation of header functions #
//######################################

HUFFMAN_ENCODING initialize_huffman_encoding() {
    HUFFMAN_ENCODING huffman_encoding = (HUFFMAN_ENCODING)malloc(sizeof(struct huffman_encoding));
    if(huffman_encoding == NULL) {
        logger(Error, "Not enough space available");
    }
    for(unsigned i = 0; i < NUMBER_CHARACTERS; ++i) {
        huffman_encoding->characters[i].frequency = 0;
        strcpy(huffman_encoding->characters[i].encoding, "");
    }
    huffman_encoding->huffman_tree = NULL;
    return huffman_encoding;
}

//======================================

int is_character_in_huffman_enconding(HUFFMAN_ENCODING huffman_encoding, const char character) {
    unsigned char_position = character_position(character);
    return huffman_encoding->characters[char_position].frequency != 0;
}

//======================================

void add_character_to_huffman_encoding(HUFFMAN_ENCODING huffman_encoding, const char character, const unsigned frequency) {
    unsigned char_position = character_position(character);
    if(huffman_encoding->characters[char_position].frequency != 0) {
        logger(Error, "Character already added");
    }
    huffman_encoding->characters[char_position].frequency = frequency;
}

//======================================

void create_encoding(HUFFMAN_ENCODING huffman_encoding) {
    priority_queue(NODE_P) pq = new_priority_queue(NODE_P, &frequency_condition);

    for(unsigned i = 0; i < NUMBER_CHARACTERS; ++i) {
        if(huffman_encoding->characters[i].frequency != 0) {
            NODE_P single_node = create_new_node(position_character(i), huffman_encoding->characters[i].frequency, NULL, NULL);
            enqueue_priority_queue(pq, single_node);
        }
    }
    while(size_priority_queue(pq) != 1) {
        NODE_P node1 = dequeue_priority_queue(pq);
        NODE_P node2 = dequeue_priority_queue(pq);
        NODE_P new_combined_node = create_new_node('-', node1->frequency + node2->frequency, node1, node2);
        enqueue_priority_queue(pq, new_combined_node);
    }
    NODE_P huffman_tree = dequeue_priority_queue(pq);
    char encoding[10];
    store_encoding(huffman_tree, huffman_encoding, encoding, 0);
    huffman_encoding->huffman_tree = huffman_tree;
    dealloc_priority_queue(pq);
}

//======================================

void get_encoding_for_char(HUFFMAN_ENCODING huffman_encoding, const char character, char *where_to_store) {
    unsigned index = character_position(character);
    if(huffman_encoding->characters[index].frequency == 0) {
        logger(Error, "Character not present in huffman encryption");
    } 
    strcpy(where_to_store, huffman_encoding->characters[index].encoding);
}

//======================================

void dealloc_huffman_encoding(HUFFMAN_ENCODING huffman_encoding) {
    dealloc_huffman_tree(huffman_encoding->huffman_tree);
    free(huffman_encoding);
}
