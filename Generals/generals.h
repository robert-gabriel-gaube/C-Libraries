#ifndef GENERALS_H
#define GENERALS_H

#include <stdio.h>

typedef enum {
    Warning, Error, Information
}LOGGER_OPTIONS;

void logger(LOGGER_OPTIONS option, const char* message);
FILE* open_file(const char* file_path);
void read_line_from_file(FILE *file, char *where);
void close_file(FILE *file);

#endif 