#ifndef __FILE_MAPPER_H
#define __FILE_MAPPER_H

#include <stddef.h>

struct file_mapping
{
    char*  data;
    size_t data_size;
};

/**
 * Maps file with given name to memory as shared page
 *
 * @param[in] filename name of file to be mapped
 * @param[out] mapping struct, containing pointer to mapped data area
 * and its size
 *
 * @return 0 upon success, -1 otherwise (check `errno` for errors)
 */
int get_editable_file_mapping(const char* filename, file_mapping* mapping);

/**
 * Frees mapped file page
 *
 * @return 0 upon success, -1 otherwise (check `errno` for errors)
 */
int unmap_file_mapping(file_mapping* mapping);

#endif
