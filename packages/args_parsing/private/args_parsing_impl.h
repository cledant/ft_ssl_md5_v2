#ifndef ARGS_PARSING_IMPL_H
#define ARGS_PARSING_IMPL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// display.c
void display_md5_help();
void display_sha256_help();

// utility.c
t_input *t_input_new(char const *str, t_access_type type);

#endif