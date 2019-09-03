#ifndef SHA256_H
#define SHA256_H

#include "container.h"

t_string const *sha256_get_hash(int32_t fd,
                                uint8_t const *str,
                                t_queue *string_chunk);

#endif
