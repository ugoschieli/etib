#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include "log.h"

char* loadFile(char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size == -1) {
        return NULL;
    }

    rewind(f);
    char* buf = calloc(sizeof(char), (size_t)(size + 1));
    if (buf == NULL) {
        return NULL;
    }

    size_t n = fread(buf, sizeof(char), (size_t)size, f);
    if (n == 0) {
        print_error("failed to read file: %s", path);
    }
    fclose(f);

    return buf;
}
