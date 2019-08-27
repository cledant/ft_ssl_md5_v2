#include "ft_ssl.h"

int
main(int argc, char const **argv)
{
    t_env e = { 0, { { 0 } } };
    static void (*func[NBR_CMD])(uint64_t, char const **, t_opt *) = {
        parse_opt_args_md5, parse_opt_args_sha256
    };

    if (argc < 2) {
        display_binary_help();
        return (0);
    }
    parse_command(&e.hash_type, argv[1]);
    if (e.hash_type == NONE) {
        printf("ft_ssl: Invalid command: %s\n\n", argv[1]);
        display_command_help();
        return (0);
    }
    (*func[e.hash_type - 1])(argc, argv, &e.opt);
    return (0);
}