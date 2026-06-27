#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

queue *queue_create(void) {
  queue *q = (queue *)calloc(1, sizeof(queue));
  if (q == NULL) {
    return NULL;
  }
  q->front = NULL;
  q->back = NULL;
  q->size = 0;
  return q;
}

err queue_push(queue *q, int value) {
  if (q == NULL) {
    return INVALID_PARAMS;
  }

  queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
  if (new_node == NULL) {
    return OUT_OF_MEMORY;
  }

  new_node->data = value;
  new_node->next = NULL;

  if (queue_is_empty(q)) {
    q->front = new_node;
    q->back = new_node;
  } else {
    q->back->next = new_node;
    q->back = new_node;
  }

  q->size++;
  return SUCCESS;
}

err queue_pop(queue *q, int *value) {
  if (q == NULL || value == NULL) {
    return INVALID_PARAMS;
  }

  if (queue_is_empty(q)) {
    return INVALID_PARAMS;
  }

  queue_node *temp = q->front;
  *value = temp->data;
  q->front = temp->next;

  if (q->front == NULL) {
    q->back = NULL;
  }

  free(temp);
  q->size--;

  return SUCCESS;
}

err queue_front(queue *q, int *value) {
  if (q == NULL || value == NULL) {
    return INVALID_PARAMS;
  }

  if (queue_is_empty(q)) {
    return INVALID_PARAMS;
  }

  *value = q->front->data;
  return SUCCESS;
}

err queue_back(queue *q, int *value) {
  if (q == NULL || value == NULL) {
    return INVALID_PARAMS;
  }

  if (queue_is_empty(q)) {
    return INVALID_PARAMS;
  }

  *value = q->back->data;
  return SUCCESS;
}

int queue_is_empty(queue *q) {
  if (q == NULL) {
    return 1;
  }
  return (q->front == NULL);
}

size_t queue_size(queue *q) {
  if (q == NULL) {
    return 0;
  }
  return q->size;
}

void queue_clear(queue *q) {
  if (q == NULL) {
    return;
  }

  while (!queue_is_empty(q)) {
    int temp;
    queue_pop(q, &temp);
  }
}

void queue_free(queue *q) {
  if (q == NULL) {
    return;
  }

  queue_clear(q);
  free(q);
}
