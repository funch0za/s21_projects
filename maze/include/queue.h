#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
  int row;
  int col;
} Point;

typedef struct queue_node_t {
  Point data;
  struct queue_node_t *next;
} queue_node_t;

typedef struct {
  queue_node_t *front;
  queue_node_t *rear;
  int size;
} queue_t;

queue_t *queue_create(void);

int queue_is_empty(queue_t *q);

void queue_push(queue_t *q, int row, int col);

Point queue_pop(queue_t *q);

Point queue_front(queue_t *q);

int queue_size(queue_t *q);

void queue_clear(queue_t *q);

void queue_destroy(queue_t *q);

#endif
