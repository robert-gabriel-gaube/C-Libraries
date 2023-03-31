#include <stdio.h>
#include "headers/huffman_compresion.h"

int main() {
    HUFFMAN_ENCODING huffman_encoding = initialize_huffman_encoding();
    add_character_to_huffman_encoding(huffman_encoding, 'A', 10);
    add_character_to_huffman_encoding(huffman_encoding, 'D', 2);
    add_character_to_huffman_encoding(huffman_encoding, 'E', 5);
    add_character_to_huffman_encoding(huffman_encoding, 'Z', 1);

    create_encoding(huffman_encoding);

    char encoding[10];
    get_encoding_for_char(huffman_encoding, 'A', encoding);
    printf("Encoding for A is %s\n", encoding);

    get_encoding_for_char(huffman_encoding, 'D', encoding);
    printf("Encoding for D is %s\n", encoding);

    get_encoding_for_char(huffman_encoding, 'E', encoding);
    printf("Encoding for E is %s\n", encoding);

    get_encoding_for_char(huffman_encoding, 'Z', encoding);
    printf("Encoding for Z is %s\n", encoding);

    dealloc_huffman_encoding(huffman_encoding);

    return 0;
}