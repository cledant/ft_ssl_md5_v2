#include "args_processing.h"
#include "args_processing_impl.h"

static void
process_exit_md5(t_input *in, t_queue *queue)
{
    free(in);
    t_queue_delete(queue);
    exit(-1);
}

t_bool
process_md5_stdin(t_opt_md5 const *opt)
{
    t_string const *hash = md5_get_hash(0, NULL, NULL);

    if (!hash) {
        puts("ft_ssl: failed to alloc memory");
        return (TRUE);
    }
    if (opt->echo) {
        puts("TODO ECHO STDIN");
    }
    puts(hash->str);
    t_string_delete((t_string *)hash, TRUE);
    return (FALSE);
}

t_bool
process_md5_file(char const *filesname, t_opt_md5 const *opt)
{
    int32_t fd = open(filesname, O_RDONLY);

    if (fd < 0) {
        printf("ft_ssl: failed to open: %s\n", filesname);
        return (FALSE);
    }
    t_string const *hash = md5_get_hash(fd, NULL, NULL);

    if (!hash) {
        puts("ft_ssl: failed to alloc memory");
        return (TRUE);
    }
    if (opt->quiet) {
        puts(hash->str);
    } else if (opt->reverse) {
        printf("%s %s\n", hash->str, filesname);
    } else {
        printf("MD5 (%s) = %s\n", filesname, hash->str);
    }
    t_string_delete((t_string *)hash, TRUE);
    return (FALSE);
}

static t_bool
process_md5_str(char const *str, t_opt_md5 const *opt)
{
    t_string const *hash = md5_get_hash(-1, (uint8_t *)str, NULL);

    if (!hash) {
        puts("ft_ssl: failed to alloc memory");
        return (TRUE);
    }
    if (opt->quiet) {
        puts(hash->str);
    } else if (opt->reverse) {
        printf("%s \"%s\"\n", hash->str, str);
    } else {
        printf("MD5 (\"%s\") = %s\n", str, hash->str);
    }
    t_string_delete((t_string *)hash, TRUE);
    return (FALSE);
}

void
process_md5(t_opt *opt)
{
    t_opt_md5 *ptr = &opt->md5;

    while (ptr->queue->size) {
        t_input *in = t_queue_pop_front(ptr->queue);

        switch (in->access) {
            case STDIN:
                if (process_md5_stdin(ptr)) {
                    process_exit_md5(in, opt->md5.queue);
                }
                break;
            case STRING:
                if (process_md5_str(in->ptr, ptr)) {
                    process_exit_md5(in, opt->md5.queue);
                }
                break;
            case FILES:
                if (process_md5_file(in->ptr, ptr)) {
                    process_exit_md5(in, opt->md5.queue);
                }
                break;
        }
        free(in);
    }
    t_queue_delete(ptr->queue);
}