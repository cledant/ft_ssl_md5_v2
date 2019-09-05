#include "container.h"
#include "container_impl.h"

t_string *
t_string_new(char const *str)
{
    t_string *ptr = (t_string *)malloc(sizeof(t_string));

    if (!ptr) {
        return (NULL);
    }
    memset(ptr, 0, sizeof(t_string));
    ptr->str = (str)
                 ? strdup(str)
                 : (char *)malloc(sizeof(char) * (T_STRING_DEFAULT_SIZE + 1));
    if (!ptr->str) {
        free(ptr);
        return (NULL);
    }
    if (str) {
        ptr->len = strlen(ptr->str);
        ptr->allocated_len = ptr->len;
    } else {
        memset(ptr->str, 0, sizeof(char) * (T_STRING_DEFAULT_SIZE + 1));
        ptr->len = 0;
        ptr->allocated_len = T_STRING_DEFAULT_SIZE;
    }
    return (ptr);
}

t_string *
t_string_sized_new(uint64_t default_len)
{
    t_string *ptr = (t_string *)malloc(sizeof(t_string));

    if (!ptr) {
        return (NULL);
    }
    if (!default_len) {
        default_len = T_STRING_DEFAULT_SIZE;
    }
    memset(ptr, 0, sizeof(t_string));
    ptr->str = (char *)malloc(sizeof(char) * (default_len + 1));
    if (!ptr->str) {
        free(ptr);
        return (NULL);
    }
    memset(ptr->str, 0, sizeof(char) * (default_len + 1));
    ptr->len = 0;
    ptr->allocated_len = default_len;
    return (ptr);
}

void
t_string_init(t_string *string, char *buff, uint64_t buff_size)
{
    string->str = buff;
    string->len = 0;
    string->allocated_len = buff_size;
    memset(string->str, 0, string->allocated_len + 1);
}

char *
t_string_delete(t_string *string, t_bool delete_str)
{
    char *ptr = string->str;

    free(string);
    if (delete_str) {
        free(ptr);
        return (NULL);
    }
    return (ptr);
}

void
t_string_clear(t_string *string)
{
    string->len = 0;
    memset(string->str, 0, sizeof(char) * string->allocated_len + 1);
}

t_string *
t_string_append(t_string *string, char const *str)
{
    uint64_t len_str = strlen(str);

    if (string->len + len_str < string->allocated_len) {
        uint64_t new_alloc_len =
          string->allocated_len + len_str + T_STRING_INCREMENT_SIZE;

        if (new_alloc_len < string->allocated_len) {
            return (string);
        }
        char *new_str =
          realloc(string->str, sizeof(char) * (new_alloc_len + 1));

        if (!new_str) {
            return (string);
        }
        string->str = new_str;
        string->allocated_len = new_alloc_len;
    }
    strcat(string->str, str);
    string->len += len_str;
    return (string);
}

t_string *
t_string_append_len(t_string *string, char const *str, uint64_t len)
{
    uint64_t len_str = strlen(str);
    if (len > len_str) {
        len = len_str;
    }

    if (string->len + len < string->allocated_len) {
        uint64_t new_alloc_len =
          string->allocated_len + len + T_STRING_INCREMENT_SIZE;

        if (new_alloc_len < string->allocated_len) {
            return (string);
        }
        char *new_str =
          realloc(string->str, sizeof(char) * (new_alloc_len + 1));

        if (!new_str) {
            return (string);
        }
        string->str = new_str;
        string->allocated_len = new_alloc_len;
    }
    strlcat(string->str, str, len + 1);
    string->len += len;
    return (string);
}

t_string *
t_string_append_no_resize(t_string *string,
                          char const *str,
                          uint64_t *appended_len)
{
    uint64_t to_cpy = strlen(str);

    if (!to_cpy) {
        return (string);
    }
    uint64_t free_space = string->allocated_len - string->len;
    if (free_space < to_cpy) {
        to_cpy = free_space;
    }
    strlcat(string->str, str, to_cpy + 1);
    string->len += to_cpy;
    if (appended_len) {
        *appended_len = to_cpy;
    }
    return (string);
}

inline uint64_t
t_string_get_free_space(t_string *string)
{
    return (string->allocated_len - string->len);
}