#ifndef FT_SSL
#define FT_SSL

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "container.h"

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

typedef struct s_env
{
    t_hash_type hash_type;
    t_opt opt;
} t_env;

// display.c
void display_binary_help();
void display_command_help();
void display_md5_help();
void display_sha256_help();

// opt_md5.c
void clean_exit_md5(t_opt_md5 *opt, char const *str);
void parse_opt_args_md5(int32_t argc, char const **argv, t_opt *opt);

// process_md5.c
void process_md5(t_opt *opt);

// process_sha256.c
void process_sha256(t_opt *opt);

// opt_sha256.c
void parse_opt_args_sha256(int32_t argc, char const **argv, t_opt *opt);

// utility.c
t_input *t_input_new(char const *str, t_access_type type);
void debug_print_args(t_env *e);
void debug_print_input(void *queue_data, void *data);

#endif