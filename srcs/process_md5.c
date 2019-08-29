#include "ft_ssl.h"

static void
print_hash_md5(t_opt_md5 const *opt,
               char const *source,
               t_string const *s)
{
    (void)opt;
    (void)s;
    printf("MD5 (%s) = %s\n", source, "TODO Things");
}

void
process_md5(t_opt *opt)
{
    t_opt_md5 *ptr = &opt->md5;

    while (ptr->queue->size) {
        t_input *in = t_queue_pop_front(ptr->queue);
        t_string *hash = NULL;

        switch (in->access) {
            case STDIN:
                print_hash_md5(ptr, "stdin", hash);
                break;
            case STRING:
                print_hash_md5(ptr, in->ptr, hash);
                break;
            case FILES:
                print_hash_md5(ptr, in->ptr, hash);
                break;
        }
        free(in);
    }
    t_queue_delete(ptr->queue);
}