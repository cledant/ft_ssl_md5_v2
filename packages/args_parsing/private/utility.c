#include "args_parsing.h"
#include "args_parsing_impl.h"

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