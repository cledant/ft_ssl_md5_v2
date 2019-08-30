#include "ft_ssl.h"

void
debug_print_args(t_env *e)
{
    if (e->hash_type == MD5) {
        t_queue_foreach(e->opt.md5.queue, debug_print_input, NULL);
    } else if (e->hash_type == SHA256) {
        t_queue_foreach(e->opt.md5.queue, debug_print_input, NULL);
    } else {
        puts("DEBUG : Should not happend");
    }
}

void
debug_print_input(void *queue_data, void *data)
{
    (void)data;
    static char const list[][10] = { "File", "String", "Stdin" };
    t_input *in = queue_data;

    printf("=====\nType = %s\nStr = %s\n=====\n", list[in->access], in->ptr);
}