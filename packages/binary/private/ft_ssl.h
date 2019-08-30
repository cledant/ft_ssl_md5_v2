#ifndef FT_SSL
#define FT_SSL

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

// debug.c
void debug_print_args(t_env *e);
void debug_print_input(void *queue_data, void *data);

#endif