#ifndef FT_SSL
#define FT_SSL

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "container.h"

#define TRUE 1
#define FALSE 0
#define NBR_CMD 2

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

typedef struct s_env
{
    t_hash_type hash_type;
    t_opt opt;
} t_env;

// opt.c
void display_binary_help();
void display_command_help();
void parse_command(t_hash_type *type, char const *str);
void parse_opt_args_md5(uint64_t argc, char const **argv, t_opt *opt);
void parse_opt_args_sha256(uint64_t argc, char const **argv, t_opt *opt);

#endif