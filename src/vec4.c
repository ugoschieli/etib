#include "vec4.h"
#include <assert.h>
#include <math.h>

GLfloat indexVec4(vec4* vec, size_t n)
{
    assert(n >= 1 && n <= 4);
    switch (n) {
    case 1:
        return vec->x;
    case 2:
        return vec->y;
    case 3:
        return vec->z;
    case 4:
        return vec->w;
    default:
        return 0;
    };
}

void setValVec4(vec4* vec, GLfloat val, size_t n)
{
    assert(n >= 1 && n <= 4);
    switch (n) {
    case 1:
        vec->x = val;
        break;
    case 2:
        vec->y = val;
        break;
    case 3:
        vec->z = val;
        break;
    case 4:
        vec->w = val;
        break;
    };
}

GLfloat normVec4(vec4* vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z + vec->w * vec->w);
}

void normalizeVec4(vec4* vec)
{
    vec->x = vec->x / normVec4(vec);
    vec->y = vec->y / normVec4(vec);
    vec->z = vec->z / normVec4(vec);
    vec->w = vec->w / normVec4(vec);
}
