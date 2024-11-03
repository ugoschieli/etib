#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stdlib.h>

typedef struct DynArray {
    void* data;
    size_t len;
    size_t capacity;
} DynArray_t;

DynArray_t newDA(void* data, size_t nbytes);

void pushDA(DynArray_t* da, void* data, size_t nbytes);

void destroyDA(DynArray_t* da);

#endif // DYN_ARRAY_H
