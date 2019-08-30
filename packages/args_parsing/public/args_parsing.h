#ifndef ARGS_PARSING_H
#define ARGS_PARSING_H

#include "shared_types.h"

// opt_md5.c
void parse_opt_args_md5(int32_t argc, char const **argv, t_opt *opt);

// opt_sha256.c
void parse_opt_args_sha256(int32_t argc, char const **argv, t_opt *opt);

#endif