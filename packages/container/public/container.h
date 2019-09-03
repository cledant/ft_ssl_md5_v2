#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>

#define TRUE 1
#define FALSE 0

typedef uint8_t t_bool;

typedef struct s_list
{
    struct s_list *prev;
    struct s_list *next;
    void *data;
} t_list;

typedef struct s_queue
{
    t_list *begin;
    t_list *end;
    uint64_t size;
} t_queue;

typedef struct s_string
{
    char *str;
    uint64_t len;
    uint64_t allocated_len;
} t_string;

typedef struct s_byte_array
{
    uint8_t *data;
    uint64_t len;
    uint64_t allocated_len;
} t_byte_array;

// t_string.c
t_string *t_string_new(char const *str);
t_string *t_string_sized_new(uint64_t default_len);
void t_string_init(t_string *string, char *buff, uint64_t buff_size);
char *t_string_delete(t_string *string, t_bool delete_str);
void t_string_clear(t_string *string);
t_string *t_string_append(t_string *string, char const *str);
t_string *t_string_append_len(t_string *string, char const *str, uint64_t len);
t_string *t_string_append_no_resize(t_string *string,
                                    char const *str,
                                    uint64_t *appended_len);
uint64_t t_string_get_free_space(t_string *string);

// t_byte_array.c
t_byte_array *t_byte_array_new(uint64_t default_len);
t_byte_array *t_byte_array_copy(t_byte_array *src);
void t_byte_array_init(t_byte_array *byte_array,
                       uint8_t *array,
                       uint64_t array_size);
uint8_t *t_byte_array_delete(t_byte_array *byte_array, t_bool delete_str);
void t_byte_array_clear(t_byte_array *byte_array);
t_byte_array *t_byte_array_append(t_byte_array *byte_array,
                                  uint8_t const *array,
                                  uint64_t len);
t_byte_array *t_byte_array_append_no_resize(t_byte_array *byte_array,
                                            uint8_t const *array,
                                            uint64_t len,
                                            uint64_t *appended_len);
uint64_t t_byte_array_get_free_space(t_byte_array *byte_array);

// t_list.c
t_list *t_list_new();

// t_queue.c
t_queue *t_queue_new();
void t_queue_delete(t_queue *queue);
void t_queue_deep_delete(t_queue *queue, void (*func)(void *));
uint64_t t_queue_get_size(t_queue *queue);
void t_queue_push_back(t_queue *queue, void *data);
void t_queue_push_front(t_queue *queue, void *data);
void *t_queue_pop_front(t_queue *queue);
void *t_queue_pop_back(t_queue *queue);
void t_queue_foreach(t_queue *queue, void (*func)(void *, void *), void *data);

// endianness.c
uint32_t swap_endianness_32(uint32_t num);
uint64_t swap_endianness_64(uint64_t num);

// rotate_data.c
uint32_t left_rotate_32(uint32_t val, uint32_t shift);
uint32_t right_rotate_32(uint32_t val, uint32_t shift);

#endif