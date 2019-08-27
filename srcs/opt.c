#include "ft_ssl.h"

void
display_binary_help()
{
    puts("Usage: ft_ssl command [command options] [command args]\n\tAvailable "
         "commands:\n\t\tmd5\n\t\tsha256");
}

void
display_command_help()
{
    puts("Available commands:\n\nMessage digest commands:\nmd5\nsha256");
}

void
parse_command(t_hash_type *type, char const *str)
{
    static char const list[][10] = { "md5", "sha256" };

    for (uint64_t i = 0; i < 2; ++i) {
        if (!strcmp(list[i], str)) {
            *type = i + 1;
            return;
        }
    }
}

void
parse_opt_args_md5(uint64_t argc, char const **argv, t_opt *opt)
{
    (void)argc;
    (void)argv;
    (void)opt;
    puts("md5");
}

void
parse_opt_args_sha256(uint64_t argc, char const **argv, t_opt *opt)
{
    (void)argc;
    (void)argv;
    (void)opt;
    puts("sha256");
}