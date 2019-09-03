#ifndef MD5_H
#define MD5_H

#include "container.h"

t_string const *md5_get_hash(int32_t fd,
                             uint8_t const *str,
                             t_queue *string_chunk);

#endif