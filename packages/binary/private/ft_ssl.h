#ifndef FT_SSL_H
#define FT_SSL_H

#include <stdio.h>
#include <string.h>

#include "args_parsing.h"
#include "args_processing.h"

#define NBR_CMD 2

typedef struct s_env
{
    t_hash_type hash_type;
    t_opt opt;
} t_env;

#endif