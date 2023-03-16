#ifndef __BINARY_PATCHER_H
#define __BINARY_PATCHER_H

#include <stddef.h>

#include "patch_array.h"

/**
 * @brief
 * Applies binary patches to given array of bytes
 *
 * @param[inout] dest array of bytes to be patched
 * @param[in] dest_size size of `dest` array
 * @param[in] patches patch descriptions
 * @return 0 upon success, -1 otherwise
 */
int apply_patches(char* dest,
                  size_t dest_size,
                  const dynamic_array(patch)* patches);

#endif