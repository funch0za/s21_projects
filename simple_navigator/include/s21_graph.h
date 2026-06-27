#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stddef.h>

#include "navigator_err.h"

typedef struct {
  size_t size;
  int **matrix;
} graph;

err allocate_graph(graph **g, size_t size);
err load_graph_from_file(graph **g, char *filename);
err export_graph_to_dot(graph *g, char *filename);
void free_graph(graph *g);

#endif
