#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack *stack_create(void) {
  stack *s = (stack *)calloc(1, sizeof(stack));
  if (s == NULL) {
    return NULL;
  }
  s->top = NULL;
  s->size = 0;
  return s;
}

err stack_push(stack *s, int value) {
  if (s == NULL) {
    return INVALID_PARAMS;
  }

  stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
  if (new_node == NULL) {
    return OUT_OF_MEMORY;
  }

  new_node->data = value;
  new_node->next = s->top;
  s->top = new_node;
  s->size++;

  return SUCCESS;
}

err stack_pop(stack *s, int *value) {
  if (s == NULL || value == NULL) {
    return INVALID_PARAMS;
  }

  if (stack_is_empty(s)) {
    return INVALID_PARAMS;
  }

  stack_node *temp = s->top;
  *value = temp->data;
  s->top = temp->next;
  free(temp);
  s->size--;

  return SUCCESS;
}

err stack_top(stack *s, int *value) {
  if (s == NULL || value == NULL) {
    return INVALID_PARAMS;
  }

  if (stack_is_empty(s)) {
    return INVALID_PARAMS;
  }

  *value = s->top->data;
  return SUCCESS;
}

int stack_is_empty(stack *s) {
  if (s == NULL) {
    return 1;
  }
  return (s->top == NULL);
}

size_t stack_size(stack *s) {
  if (s == NULL) {
    return 0;
  }
  return s->size;
}

void stack_clear(stack *s) {
  if (s == NULL) {
    return;
  }

  while (!stack_is_empty(s)) {
    int temp;
    stack_pop(s, &temp);
  }
}

void stack_free(stack *s) {
  if (s == NULL) {
    return;
  }

  stack_clear(s);
  free(s);
}
