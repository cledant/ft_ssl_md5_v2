#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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