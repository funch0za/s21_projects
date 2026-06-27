#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#include "navigator_err.h"

typedef struct stack_node {
  int data;
  struct stack_node *next;
} stack_node;

typedef struct {
  stack_node *top;
  size_t size;
} stack;

stack *stack_create(void);
err stack_push(stack *s, int value);
err stack_pop(stack *s, int *value);
err stack_top(stack *s, int *value);
int stack_is_empty(stack *s);
size_t stack_size(stack *s);
void stack_clear(stack *s);
void stack_free(stack *s);

#endif
