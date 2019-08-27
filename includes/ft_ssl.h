#ifndef FT_SSL
#define FT_SSL

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "container.h"

#define TRUE 1
#define FALSE 0

typedef enum e_access_type
{
    FILES,
    STRING,
} t_access_type;

typedef struct s_input
{
    t_access_type access;
    char *ptr;
} t_input;

typedef struct s_opt_md5
{
    uint8_t echo;
    uint8_t quiet;
    uint8_t reverse;
    t_queue *queue;
} t_opt_md5;

typedef struct s_opt_sha256
{
    uint8_t echo;
    uint8_t quiet;
    uint8_t reverse;
    t_queue *queue;
} t_opt_sha256;

typedef union s_opt
{
    t_opt_md5 md5;
    t_opt_sha256 sha256;
} t_opt;

#endif