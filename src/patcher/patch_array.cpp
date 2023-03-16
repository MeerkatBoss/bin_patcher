#include <string.h>

#include "patch_array.h"
#define ARRAY_ELEMENT patch


inline void copy_element(ARRAY_ELEMENT* dest, const ARRAY_ELEMENT* src)
{
    memcpy(dest, src, sizeof(*dest));
}

inline void delete_element(ARRAY_ELEMENT* element)
{
    memset(element, 0, sizeof(*element));
}

#include "dynamic_array/dynamic_array_impl.h"

#undef ARRAY_ELEMENT