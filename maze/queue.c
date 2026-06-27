#include "queue.h"
#include <stdlib.h>

queue_t *queue_create(void) {
  queue_t *q = (queue_t *)malloc(sizeof(queue_t));
  if (q == NULL) {
    return NULL;
  }
  q->front = NULL;
  q->rear = NULL;
  q->size = 0;
  return q;
}

int queue_is_empty(queue_t *q) { return q == NULL || q->front == NULL; }

void queue_push(queue_t *q, int row, int col) {
  if (q == NULL)
    return;

  queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
  if (new_node == NULL)
    return;

  new_node->data.row = row;
  new_node->data.col = col;
  new_node->next = NULL;

  if (q->rear == NULL) {
    q->front = new_node;
    q->rear = new_node;
  } else {
    q->rear->next = new_node;
    q->rear = new_node;
  }
  q->size++;
}

Point queue_pop(queue_t *q) {
  Point empty_point = {-1, -1};

  if (q == NULL || q->front == NULL) {
    return empty_point;
  }

  queue_node_t *temp = q->front;
  Point data = temp->data;

  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }

  free(temp);
  q->size--;

  return data;
}

Point queue_front(queue_t *q) {
  Point empty_point = {-1, -1};

  if (q == NULL || q->front == NULL) {
    return empty_point;
  }

  return q->front->data;
}

int queue_size(queue_t *q) { return q == NULL ? 0 : q->size; }

void queue_clear(queue_t *q) {
  if (q == NULL)
    return;

  while (!queue_is_empty(q)) {
    queue_pop(q);
  }
}

void queue_destroy(queue_t *q) {
  if (q == NULL)
    return;

  queue_clear(q);
  free(q);
}