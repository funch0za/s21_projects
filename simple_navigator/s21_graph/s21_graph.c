#include "s21_graph.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

err allocate_graph(graph **g, size_t size) {
  if (g == NULL || size <= 0) {
    return INVALID_PARAMS;
  }

  *g = calloc(1, sizeof(graph));
  if (*g == NULL) {
    return OUT_OF_MEMORY;
  }

  (*g)->size = size;

  (*g)->matrix = calloc((*g)->size, sizeof(int *));

  if ((*g)->matrix == NULL) {
    free(*g);
    *g = NULL;
    return OUT_OF_MEMORY;
  }

  for (size_t i = 0; i < size; ++i) {
    (*g)->matrix[i] = calloc(size, sizeof(int));
    if ((*g)->matrix[i] == NULL) {
      for (size_t j = 0; j < i; ++j) {
        free((*g)->matrix[j]);
      }
      free((*g)->matrix);
      free(*g);
      *g = NULL;
      return OUT_OF_MEMORY;
    }
  }

  return SUCCESS;
}

err load_graph_from_file(graph **g, char *filename) {
  if (g == NULL || filename == NULL) {
    return INVALID_PARAMS;
  }

  if (*g != NULL) {
    free_graph(*g);
    *g = NULL;
  }

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return BAD_FILE;
  }

  size_t size;
  if (fscanf(file, "%zu", &size) != 1) {
    fclose(file);
    return BAD_FILE;
  }

  err result = allocate_graph(g, size);
  if (result != SUCCESS) {
    fclose(file);
    return result;
  }

  for (size_t i = 0; i < (*g)->size; i++) {
    for (size_t j = 0; j < (*g)->size; j++) {
      if (fscanf(file, "%d", &(*g)->matrix[i][j]) != 1) {
        free_graph(*g);
        *g = NULL;
        fclose(file);
        return BAD_FILE;
      }
    }
  }

  fclose(file);
  return SUCCESS;
}

err export_graph_to_dot(graph *g, char *filename) {
  if (g == NULL || filename == NULL) {
    return INVALID_PARAMS;
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return BAD_FILE;
  }

  fprintf(file, "digraph G {\n");
  fprintf(file, "    rankdir=LR;\n");
  fprintf(file,
          "    node [shape=circle, style=filled, fillcolor=lightblue];\n");

  for (size_t i = 0; i < g->size; i++) {
    fprintf(file, "    %zu [label=\"%zu\"];\n", i, i + 1);
  }

  for (size_t i = 0; i < g->size; i++) {
    for (size_t j = 0; j < g->size; j++) {
      if (g->matrix[i][j] != 0) {
        if (g->matrix[i][j] == 1) {
          fprintf(file, "    %zu -> %zu;\n", i, j);
        } else {
          fprintf(file, "    %zu -> %zu [label=\"%d\", fontsize=10];\n", i, j,
                  g->matrix[i][j]);
        }
      }
    }
  }

  fprintf(file, "}\n");
  fclose(file);

  return SUCCESS;
}

void free_graph(graph *g) {
  if (g) {
    if (g->matrix) {
      for (size_t i = 0; i < g->size; ++i) {
        free(g->matrix[i]);
      }
      free(g->matrix);
    }
    free(g);
  }
}
