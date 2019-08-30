#include "ft_ssl.h"

static void
display_binary_help()
{
    puts("Usage: ft_ssl command [command options] [command args]\n\tAvailable "
         "commands:\n\t\tmd5\n\t\tsha256");
}

static void
display_command_help()
{
    puts("Available commands:\n\nMessage digest commands:\nmd5\nsha256");
}

static void
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

int
main(int argc, char const **argv)
{
    t_env e = { 0, { { 0 } } };
    static void (*parse_func[NBR_CMD])(int32_t, char const **, t_opt *) = {
        parse_opt_args_md5, parse_opt_args_sha256
    };
    static void (*process_func[NBR_CMD])(t_opt *) = { process_md5,
                                                      process_sha256 };

    if (argc < 2) {
        display_binary_help();
        return (1);
    }
    parse_command(&e.hash_type, argv[1]);
    if (e.hash_type == NONE) {
        printf("ft_ssl: Invalid command: %s\n\n", argv[1]);
        display_command_help();
        return (1);
    }
    (*parse_func[e.hash_type - 1])(argc, argv, &e.opt);
    (*process_func[e.hash_type - 1])(&e.opt);
    return (0);
}