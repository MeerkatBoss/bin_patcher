#include <string.h>

#include "logger/logger.h"

#include "patcher.h"

int apply_patches(char *dest,
                  size_t dest_size,
                  const dynamic_array(patch) * patches)
{
    LOG_ASSERT(dest, return -1);
    LOG_ASSERT(patches, return -1);

    for (size_t i = 0; i < patches->size; i++)
    {
        patch* ptc = array_get_element(patches, i);
        LOG_ASSERT(ptc->offset < dest_size, return -1);
        LOG_ASSERT(ptc->offset + ptc->size < dest_size, return -1);

        memcpy(dest + ptc->offset, ptc->bytes, ptc->size);
    }

    return 0;
}
