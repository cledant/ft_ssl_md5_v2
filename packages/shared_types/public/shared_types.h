#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include "container.h"

typedef enum e_hash_type
{
    NONE = 0,
    MD5,
    SHA256,
} t_hash_type;

typedef enum e_access_type
{
    FILES = 0,
    STRING,
    STDIN,
} t_access_type;

typedef struct s_input
{
    t_access_type access;
    char const *ptr;
} t_input;

typedef struct s_opt_md5
{
    int32_t position;
    uint8_t echo;
    uint8_t quiet;
    uint8_t reverse;
    uint8_t display_help;
    t_queue *queue;
} t_opt_md5;

typedef struct s_opt_sha256
{
    int32_t position;
    uint8_t echo;
    uint8_t quiet;
    uint8_t reverse;
    uint8_t display_help;
    t_queue *queue;
} t_opt_sha256;

typedef union s_opt
{
    t_opt_md5 md5;
    t_opt_sha256 sha256;
} t_opt;

#endif