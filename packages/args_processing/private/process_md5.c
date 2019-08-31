#include "args_processing.h"
#include "args_processing_impl.h"

static void
print_hash_md5(t_opt_md5 const *opt,
               char const *source,
               t_string const *s)
{
    (void)opt;
    if (s) {
        printf("MD5 (%s) = %s\n", source, s->str);
    } else {
        printf("MD5 (%s) = %s\n", source, "TODO Things");
    }
}

void
process_md5(t_opt *opt)
{
    t_opt_md5 *ptr = &opt->md5;

    while (ptr->queue->size) {
        t_input *in = t_queue_pop_front(ptr->queue);
        t_string const *hash = NULL;

        switch (in->access) {
            case STDIN:
                hash = md5_get_hash(0, NULL, NULL);
                print_hash_md5(ptr, "stdin", hash);
                break;
            case STRING:
                hash = md5_get_hash(-1, in->ptr, NULL);
                print_hash_md5(ptr, in->ptr, hash);
                break;
            case FILES:
                hash = md5_get_hash(0, NULL, NULL);
                print_hash_md5(ptr, in->ptr, hash);
                break;
        }
        free(in);
        t_string_delete((t_string *)hash, TRUE);
    }
    t_queue_delete(ptr->queue);
}