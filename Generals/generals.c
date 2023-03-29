#include "generals.h"
#include <stdlib.h>
#include <string.h>

FILE* open_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if(file == NULL) logger(Error, "The file couldn't be opened");
    return file;
}

void read_line_from_file(FILE *file, char *where) {
    if(fgets(where, 100, file) == NULL) logger(Error, "Reading went wrong");
    where[strcspn(where, "\r\n")] = 0; 
}

void close_file(FILE *file) {
    if(fclose(file)) logger(Error, "The file didn't close correctly");
}

void logger(LOGGER_OPTIONS option, const char* message) {
    switch (option)
    {
        case Warning:
            printf("[WARNING] %s\n", message);
            break;
        case Error:
            printf("[ERROR] %s\n", message);
            exit(EXIT_FAILURE);
            break;
        case Information:
            printf("[INFO] %s\n", message);
            break;
    }
}