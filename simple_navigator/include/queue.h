#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "navigator_err.h"

typedef struct queue_node {
  int data;
  struct queue_node *next;
} queue_node;

typedef struct {
  queue_node *front;
  queue_node *back;
  size_t size;
} queue;

queue *queue_create(void);
err queue_push(queue *q, int value);
err queue_pop(queue *q, int *value);
err queue_front(queue *q, int *value);
err queue_back(queue *q, int *value);
int queue_is_empty(queue *q);
size_t queue_size(queue *q);
void queue_clear(queue *q);
void queue_free(queue *q);

#endif
