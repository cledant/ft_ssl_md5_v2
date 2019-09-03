#include "container.h"
#include "container_impl.h"

t_queue *
t_queue_new()
{
    t_queue *ptr = (t_queue *)malloc(sizeof(t_queue));

    if (!ptr) {
        return (NULL);
    }
    memset(ptr, 0, sizeof(t_queue));
    return (ptr);
}

void
t_queue_delete(t_queue *queue)
{
    while (queue->begin) {
        t_list *tmp = queue->begin->next;

        free(queue->begin);
        queue->begin = tmp;
    }
    free(queue);
}

void
t_queue_deep_delete(t_queue *queue, void (*func)(void *))
{
    while (queue->begin) {
        t_list *tmp = queue->begin->next;

        (*func)(queue->begin->data);
        free(queue->begin);
        queue->begin = tmp;
    }
    free(queue);
}

uint64_t
t_queue_get_size(t_queue *queue)
{
    return (queue->size);
}

void
t_queue_push_back(t_queue *queue, void *data)
{
    if (!data) {
        return;
    }
    t_list *new_data = t_list_new();

    if (!new_data) {
        return;
    }
    new_data->data = data;
    new_data->prev = queue->end;
    if (queue->end) {
        queue->end->next = new_data;
    }
    queue->end = new_data;
    if (!queue->begin) {
        queue->begin = new_data;
    }
    ++queue->size;
}

void
t_queue_push_front(t_queue *queue, void *data)
{
    if (!data) {
        return;
    }
    t_list *new_data = t_list_new();

    if (!new_data) {
        return;
    }
    new_data->data = data;
    new_data->next = queue->begin;
    if (queue->begin) {
        queue->begin->prev = new_data;
    }
    queue->begin = new_data;
    if (!queue->end) {
        queue->end = new_data;
    }
    ++queue->size;
}

void *
t_queue_pop_front(t_queue *queue)
{
    if (!queue->begin) {
        return (NULL);
    }
    void *data = queue->begin->data;
    t_list *to_delete = queue->begin;

    if (queue->begin == queue->end) {
        queue->begin = NULL;
        queue->end = NULL;
    } else {
        queue->begin = queue->begin->next;
        queue->begin->prev = NULL;
    }
    free(to_delete);
    --queue->size;
    return (data);
}

void *
t_queue_pop_back(t_queue *queue)
{
    if (!queue->end) {
        return (NULL);
    }
    void *data = queue->end->data;
    t_list *to_delete = queue->end;

    if (queue->begin == queue->end) {
        queue->begin = NULL;
        queue->end = NULL;
    } else {
        queue->end = queue->end->prev;
        queue->end->next = NULL;
    }
    free(to_delete);
    --queue->size;
    return (data);
}

void
t_queue_foreach(t_queue *queue, void (*func)(void *, void *), void *data)
{
    while (queue->begin) {
        (*func)(queue->begin->data, data);
        queue->begin = queue->begin->next;
    }
}