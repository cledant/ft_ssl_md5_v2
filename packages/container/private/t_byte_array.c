#include "container.h"
#include "container_impl.h"

t_byte_array *
t_byte_array_new(uint64_t default_len)
{
    t_byte_array *ptr = (t_byte_array *)malloc(sizeof(t_byte_array));

    if (!ptr) {
        return (NULL);
    }
    if (!default_len) {
        default_len = T_BYTE_ARRAY_DEFAULT_SIZE;
    }
    memset(ptr, 0, sizeof(t_byte_array));
    ptr->data = (uint8_t *)malloc(sizeof(uint8_t) * default_len);
    if (!ptr->data) {
        free(ptr);
        return (NULL);
    }
    memset(ptr->data, 0, sizeof(uint8_t) * default_len);
    ptr->len = 0;
    ptr->allocated_len = default_len;
    return (ptr);
}

void
t_byte_array_init(t_byte_array *byte_array, uint8_t *array, uint64_t array_size)
{
    byte_array->data = array;
    byte_array->len = 0;
    byte_array->allocated_len = array_size;
    memset(byte_array->data, 0, byte_array->allocated_len);
}

uint8_t *
t_byte_array_delete(t_byte_array *byte_array, t_bool delete_str)
{
    uint8_t *ptr = byte_array->data;

    free(byte_array);
    if (delete_str) {
        free(ptr);
        return (NULL);
    }
    return (ptr);
}

void
t_byte_array_clear(t_byte_array *byte_array)
{
    byte_array->len = 0;
    memset(byte_array->data, 0, sizeof(uint8_t) * byte_array->allocated_len);
}

t_byte_array *
t_byte_array_append(t_byte_array *byte_array,
                    uint8_t const *array,
                    uint64_t len)
{
    if (byte_array->len + len < byte_array->allocated_len) {
        uint64_t new_alloc_len =
          byte_array->allocated_len + len + T_BYTE_ARRAY_INCREMENT_SIZE;

        if (new_alloc_len < byte_array->allocated_len) {
            return (byte_array);
        }
        uint8_t *new_str =
          realloc(byte_array->data, sizeof(uint8_t) * new_alloc_len);

        if (!new_str) {
            return (byte_array);
        }
        byte_array->data = new_str;
        byte_array->allocated_len = new_alloc_len;
    }
    memcpy(byte_array->data + byte_array->len, array, len);
    byte_array->len += len;
    return (byte_array);
}

t_byte_array *
t_byte_array_append_no_resize(t_byte_array *byte_array,
                              uint8_t const *array,
                              uint64_t len,
                              uint64_t *appended_len)
{
    if (!len) {
        return (byte_array);
    }
    uint64_t free_space = byte_array->allocated_len - byte_array->len;
    if (free_space < len) {
        len = free_space;
    }
    memcpy(byte_array->data + byte_array->len, array, len);
    byte_array->len += len;
    if (appended_len) {
        *appended_len = len;
    }
    return (byte_array);
}

inline uint64_t
t_byte_array_get_free_space(t_byte_array *byte_array)
{
    return (byte_array->allocated_len - byte_array->len);
}