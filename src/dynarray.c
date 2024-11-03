#include "dynarray.h"
#include <string.h>

DynArray_t newDA(void* data, size_t nbytes)
{
    void* daData;
    size_t daLen;
    size_t daCap;

    if (nbytes == 0) {
        daCap = daLen = 100;
        daData = malloc(100);
    } else {
        daLen = nbytes;
        daCap = nbytes * 2;
        daData = malloc(daCap);
    }

    if (data != NULL) {
        memcpy(daData, data, nbytes);
    }

    return (DynArray_t) { .data = daData, .len = daLen, .capacity = daCap };
}

void pushDA(DynArray_t* da, void* data, size_t nbytes)
{
    if ((da->len + nbytes) < da->capacity) {
        memcpy((char*)da->data + da->len, data, nbytes);
        da->len += nbytes;
        return;
    }

    size_t newCap = (da->capacity + nbytes) * 2;
    da->data = realloc(da->data, newCap);
    memcpy((char*)da->data + da->len, data, nbytes);
    da->len += nbytes;
    da->capacity = newCap;
}

void destroyDA(DynArray_t* da)
{
    free(da->data);
}
