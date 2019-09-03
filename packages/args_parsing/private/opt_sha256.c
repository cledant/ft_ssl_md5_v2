#include "args_parsing.h"
#include "args_parsing_impl.h"

static void
clean_exit_sha256(t_opt_sha256 *opt, char const *str)
{
    if (str) {
        puts(str);
    }
    if (opt->queue) {
        t_queue_deep_delete(opt->queue, free);
    }
    exit(1);
}

static uint8_t
parse_file(t_opt_sha256 *opt, char const *str)
{
    t_input *input = t_input_new(str, FILES);

    if (!input) {
        clean_exit_sha256(opt, "ft_ssl: failed to alloc memory");
    }
    t_queue_push_back(opt->queue, (void *)input);
    ++opt->position;
    return (0);
}

static uint8_t
parse_str(t_opt_sha256 *opt, char const *str, char c)
{
    if (!str) {
        printf("ft_ssl: Missing argument after option -%c\n", c);
        clean_exit_sha256(opt, NULL);
    }
    t_input *input = t_input_new(str, STRING);

    if (!input) {
        clean_exit_sha256(opt, "ft_ssl: failed to alloc memory");
    }
    t_queue_push_back(opt->queue, (void *)input);
    return (1);
}

static uint8_t
parse_opt(t_opt_sha256 *opt, char const *argv, char const *next_argv)
{
    while (*argv) {
        switch (*argv) {
            case 'h':
                opt->display_help = TRUE;
                break;
            case 'p':
                opt->echo = TRUE;
                break;
            case 'q':
                opt->quiet = TRUE;
                break;
            case 'r':
                opt->reverse = TRUE;
                break;
            case 's':
                return (parse_str(opt, next_argv, *argv));
            default:
                printf("ft_ssl: Invalid option: %c; type -h to display help\n",
                       *argv);
                clean_exit_sha256(opt, NULL);
                break;
        }
        ++argv;
    }
    return (0);
}

static uint8_t
parse_args(t_opt_sha256 *opt, char const *argv, char const *next_argv)
{
    uint64_t arg_len = strlen(argv);

    if (!opt->position && arg_len > 1 && argv[0] == '-') {
        return (parse_opt(opt, argv + 1, next_argv));
    } else {
        return (parse_file(opt, argv));
    }
}

void
parse_opt_args_sha256(int32_t argc, char const **argv, t_opt *opt)
{
    if (!(opt->sha256.queue = t_queue_new())) {
        clean_exit_sha256(&opt->sha256, "ft_ssl: failed to alloc memory");
    }
    for (int32_t i = 2; i < argc; ++i) {
        char const *next_ptr = NULL;

        if ((i + 1) < argc) {
            next_ptr = argv[i + 1];
        }
        i += parse_args(&opt->sha256, argv[i], next_ptr);
    }
    if (opt->sha256.display_help) {
        display_sha256_help();
        clean_exit_sha256(&opt->sha256, NULL);
    }
    if (!opt->sha256.queue->size || opt->sha256.echo) {
        t_input *input = t_input_new(NULL, STDIN);

        if (!input) {
            clean_exit_sha256(&opt->sha256, "ft_ssl: failed to alloc memory");
        }
        t_queue_push_front(opt->sha256.queue, (void *)input);
    }
}