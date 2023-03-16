#ifndef __PATCH_ARRAY_H
#define __PATCH_ARRAY_H

#include <stddef.h>

constexpr size_t MAX_PATCH_SIZE = 32;

struct patch
{
    size_t         size;
    size_t         offset;
    unsigned char  bytes[MAX_PATCH_SIZE];
};

#define ARRAY_ELEMENT patch

#include "dynamic_array/dynamic_array.h"

#undef ARRAY_ELEMENT

#endif