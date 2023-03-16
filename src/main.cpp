#include <stdio.h>

#include "logger/logger.h"

#include "mapper/mapper.h"
#include "patcher/patcher.h"

#define PATCH_BYTES {\
        0xBA, 0x67, 0x90,       /* mov dx, 9067h           */\
        0xBB, 0x9D, 0x17,       /* mov bx, 179Dh           */\
        0xEB, 0x19              /* jmp 0127H    ; ip + 19h */\
}


int main()
{
    add_default_file_logger();
    add_logger({
        .name = "Console logger",
        .stream = stderr,
        .logging_level = LOG_ERROR,
        .settings_mask = LGS_USE_ESCAPE | LGS_KEEP_OPEN
    });

    dynamic_array(patch) patches = {};
    array_ctor(&patches);

    array_push(
        &patches,
        {.size = 8, .offset=6, .bytes=PATCH_BYTES}
    );

    file_mapping mapping = {};
    int res = get_editable_file_mapping("CRACK_ME.COM", &mapping);
    LOG_ASSERT_ERROR(
        res == 0,
        { array_dtor(&patches); return 1; },
        "Failed to open file 'CRACK_ME.COM'", NULL
    );

    res = apply_patches(mapping.data, mapping.data_size, &patches);
    LOG_ASSERT_ERROR(
        res == 0,
        { array_dtor(&patches); return 1; },
        "File too small to apply patch", NULL
    );

    LOG_ASSERT(unmap_file_mapping(&mapping) == 0, return 1);

    array_dtor(&patches);

    return 0;
}
