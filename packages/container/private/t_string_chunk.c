#include "container.h"
#include "container_impl.h"

t_string_chunk *
t_string_chunk_new(uint64_t len)
{
    t_string_chunk *ptr = (t_string_chunk *)malloc(sizeof(t_string_chunk));

    if (!ptr) {
        return (NULL);
    }
    if (!(ptr->queue = t_queue_new())) {
        free(ptr);
        return (NULL);
    }
    if (!len) {
        len = 1;
    }
    ptr->chunk_size = len;
    t_string *new_str = t_string_sized_new(ptr->chunk_size);

    if (!new_str) {
        t_queue_delete(ptr->queue);
        free(ptr);
        return (NULL);
    }
    t_queue_push_back(ptr->queue, new_str);
    return (ptr);
}

void
t_string_chunk_delete(t_string_chunk *string_chunk)
{
    t_queue_delete(string_chunk->queue);
    free(string_chunk);
}

void
t_string_chunk_append(t_string_chunk *string_chunk, char const *str)
{
    uint64_t len_str = strlen(str);

    if (!len_str) {
        return;
    }
    t_string *last_chunk = string_chunk->queue->end->data;
    uint64_t free_space = last_chunk->allocated_len - last_chunk->len;

    if (free_space && free_space >= len_str) {
        t_string_append_len(last_chunk, str, free_space);
        return;
    } else if (free_space) {
        t_string_append_len(last_chunk, str, free_space);
        len_str -= free_space;
        str += free_space;
    }
    uint64_t nb_full_chunk = len_str / string_chunk->chunk_size;
    if (len_str % string_chunk->chunk_size) {
        ++nb_full_chunk;
    }
    for (uint64_t i = 0; i < nb_full_chunk; ++i) {
        t_string *chunk = t_string_sized_new(string_chunk->chunk_size);

        if (!chunk) {
            return;
        }
        t_string_append_len(chunk, str, string_chunk->chunk_size);
        t_queue_push_back(string_chunk->queue, chunk);
        str += string_chunk->chunk_size;
    }
}