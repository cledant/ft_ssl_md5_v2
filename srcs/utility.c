#include "ft_ssl.h"

t_input *
t_input_new(char const *str, t_access_type type)
{
    t_input *in = (t_input *)malloc(sizeof(t_input));

    if (!in) {
        return (NULL);
    }
    in->ptr = str;
    in->access = type;
    return (in);
}

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