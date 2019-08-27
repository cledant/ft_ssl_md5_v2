#include "container.h"

t_list *
t_list_new()
{
    t_list *ptr = (t_list *)malloc(sizeof(t_list));

    if (!ptr) {
        return (NULL);
    }
    memset(ptr, 0, sizeof(t_list));
    return (ptr);
}