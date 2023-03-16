#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "logger/logger.h"

#include "mapper.h"

int get_editable_file_mapping(const char* filename, file_mapping* mapping)
{
    LOG_ASSERT(filename, return -1);
    LOG_ASSERT(mapping, return -1);

    int fd = open(filename, O_RDWR);
    if (fd < 0) return -1;  // Failed to open, errno indicates error

    struct stat file_info = {};
    int res = 0;
    
    res = fstat(fd, &file_info);
    LOG_ASSERT(
        res == 0,
        return -1
    );

    char* data = (char*) mmap(
            /* addr hint */     NULL,
            /* mapping size */  (size_t) file_info.st_size,
            /* prot flags */    PROT_READ | PROT_WRITE,
            /* mapping type*/   MAP_SHARED,
            /* descriptor */    fd,
            /* start offset */  0);
    res = close(fd);
    LOG_ASSERT(
        res == 0,
        return -1
    );

    if (!data) return -1;   // Failed to open, errno indicates error

    mapping->data = data;
    mapping->data_size = (size_t) file_info.st_size;

    return 0;
}

int unmap_file_mapping(file_mapping* mapping)
{
    return munmap(mapping->data, mapping->data_size);
}
