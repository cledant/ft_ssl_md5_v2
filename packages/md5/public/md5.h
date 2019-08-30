#ifndef MD5_H
#define MD5_H

#include "container.h"

t_string const *md5_get_hash(int32_t fd,
                             char const *str,
                             t_string_chunk *string_chunk);

#endif