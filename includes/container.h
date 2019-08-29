#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define T_STRING_DEFAULT_SIZE 32
#define T_STRING_INCREMENT_SIZE 128

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

typedef struct s_string_chunk
{
    t_queue *queue;
    uint64_t chunk_size;
} t_string_chunk;

// t_string.c
t_string *t_string_new(char const *str);
t_string *t_string_sized_new(uint64_t default_len);
char *t_string_delete(t_string *string, t_bool delete_str);
uint64_t t_string_get_len(t_string *string);
uint64_t t_string_get_allocated_len(t_string *string);
t_string *t_string_append(t_string *string, char const *str);
t_string *t_string_append_len(t_string *string, char const *str, uint64_t len);

// t_string_chunk.c
t_string_chunk *t_string_chunk_new(uint64_t len);
void t_string_chunk_delete();
void t_string_chunk_append(t_string_chunk *string_chunk, char const *str);

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

#endif