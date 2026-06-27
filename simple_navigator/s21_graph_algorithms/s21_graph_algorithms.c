#include "s21_graph_algorithms.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "stack.h"

int *depth_first_search(graph *graph, int start_vertex) {
  if (graph == NULL || start_vertex < 1 || start_vertex > (int)graph->size) {
    return NULL;
  }

  stack *s = stack_create();
  if (s == NULL) {
    return NULL;
  }

  int *used = calloc(graph->size, sizeof(int));
  if (used == NULL) {
    stack_free(s);
    return NULL;
  }

  --start_vertex;
  if (stack_push(s, start_vertex) != SUCCESS) {
    stack_free(s);
    free(used);
    return NULL;
  }
  used[start_vertex] = 1;

  int *order = malloc(graph->size * sizeof(int));
  if (order == NULL) {
    stack_free(s);
    free(used);
    return NULL;
  }

  int count = 0;

  while (!stack_is_empty(s)) {
    int from;
    stack_pop(s, &from);
    order[count++] = from + 1;

    for (size_t to = 0; to < graph->size; ++to) {
      if (graph->matrix[from][to] != 0 && used[to] == 0) {
        used[to] = 1;
        if (stack_push(s, to) != SUCCESS) {
          stack_free(s);
          free(used);
          free(order);
          return NULL;
        }
      }
    }
  }

  int *final_order = realloc(order, count * sizeof(int));
  if (final_order == NULL && count > 0) {
    final_order = order;
  } else if (final_order == NULL && count == 0) {
    free(order);
    final_order = NULL;
  }

  stack_free(s);
  free(used);

  return final_order;
}

int *breadth_first_search(graph *graph, int start_vertex) {
  if (graph == NULL || start_vertex < 1 || start_vertex > (int)graph->size) {
    return NULL;
  }

  --start_vertex;
  int *used = calloc(graph->size, sizeof(int));
  if (used == NULL) {
    return NULL;
  }

  queue *q = queue_create();
  if (q == NULL) {
    free(used);
    return NULL;
  }

  used[start_vertex] = 1;
  if (queue_push(q, start_vertex) != SUCCESS) {
    queue_free(q);
    free(used);
    return NULL;
  }

  int *order = malloc(graph->size * sizeof(int));
  if (order == NULL) {
    queue_free(q);
    free(used);
    return NULL;
  }

  int count = 0;

  while (!queue_is_empty(q)) {
    int v;
    if (queue_pop(q, &v) != SUCCESS) {
      break;
    }
    order[count++] = v + 1;

    for (size_t to = 0; to < graph->size; ++to) {
      if (graph->matrix[v][to] != 0 && used[to] == 0) {
        used[to] = 1;
        if (queue_push(q, to) != SUCCESS) {
          queue_free(q);
          free(used);
          free(order);
          return NULL;
        }
      }
    }
  }

  int *final_order = realloc(order, count * sizeof(int));
  if (final_order == NULL && count > 0) {
    final_order = order;
  } else if (final_order == NULL && count == 0) {
    free(order);
    final_order = NULL;
  }

  queue_free(q);
  free(used);

  return final_order;
}

int get_shortest_path_between_vertices(graph *graph, int vertex1, int vertex2) {
  if (graph == NULL || vertex1 < 1 || vertex1 > (int)graph->size ||
      vertex2 < 1 || vertex2 > (int)graph->size) {
    return -1;
  }

  int start = vertex1 - 1;
  int target = vertex2 - 1;

  int *dist = malloc(graph->size * sizeof(int));
  int *used = calloc(graph->size, sizeof(int));

  if (dist == NULL || used == NULL) {
    free(dist);
    free(used);
    return -1;
  }

  for (size_t i = 0; i < graph->size; i++) {
    dist[i] = INT_MAX;
  }
  dist[start] = 0;

  for (size_t count = 0; count < graph->size - 1; count++) {
    int min_dist = INT_MAX;
    int min_index = -1;

    for (size_t i = 0; i < graph->size; i++) {
      if (!used[i] && dist[i] <= min_dist) {
        min_dist = dist[i];
        min_index = i;
      }
    }

    if (min_index == -1) {
      break;
    }

    used[min_index] = 1;

    for (size_t i = 0; i < graph->size; i++) {
      if (!used[i] && graph->matrix[min_index][i] != 0 &&
          dist[min_index] != INT_MAX &&
          dist[min_index] + graph->matrix[min_index][i] < dist[i]) {
        dist[i] = dist[min_index] + graph->matrix[min_index][i];
      }
    }
  }

  int result = (dist[target] != INT_MAX) ? dist[target] : -1;

  free(dist);
  free(used);

  return result;
}

int **get_shortest_paths_between_all_vertices(graph *graph) {
  if (graph == NULL || graph->size == 0) {
    return NULL;
  }

  int size = graph->size;

  int **dist = malloc(size * sizeof(int *));
  if (dist == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    dist[i] = malloc(size * sizeof(int));
    if (dist[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(dist[j]);
      }
      free(dist);
      return NULL;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        dist[i][j] = 0;
      } else if (graph->matrix[i][j] != 0) {
        dist[i][j] = graph->matrix[i][j];
      } else {
        dist[i][j] = INT_MAX / 2;
      }
    }
  }

  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (dist[i][k] < INT_MAX / 2 && dist[k][j] < INT_MAX / 2 &&
            dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (dist[i][j] >= INT_MAX / 2) {
        dist[i][j] = -1;
      }
    }
  }

  return dist;
}

int **get_least_spanning_tree(graph *graph) {
  if (graph == NULL || graph->size == 0) {
    return NULL;
  }

  int **mst = malloc(graph->size * sizeof(int *));
  if (mst == NULL) {
    return NULL;
  }

  for (int i = 0; i < (int)graph->size; i++) {
    mst[i] = calloc(graph->size, sizeof(int));
    if (mst[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(mst[j]);
      }
      free(mst);
      return NULL;
    }
  }

  int *used = calloc(graph->size, sizeof(int));
  if (used == NULL) {
    for (int i = 0; i < (int)graph->size; i++) {
      free(mst[i]);
    }
    free(mst);
    return NULL;
  }

  used[0] = 1;

  for (int e = 0; e < (int)graph->size; ++e) {
    int min_weight = INT_MAX;
    int from = -1, to = -1;

    for (int i = 0; i < (int)graph->size; i++) {
      if (used[i]) {
        for (int j = 0; j < (int)graph->size; j++) {
          if (!used[j] && graph->matrix[i][j] != 0 &&
              graph->matrix[i][j] < min_weight) {
            min_weight = graph->matrix[i][j];
            from = i;
            to = j;
          }
        }
      }
    }

    if (from == -1 || to == -1) {
      break;
    }

    mst[from][to] = min_weight;
    mst[to][from] = min_weight;
    used[to] = 1;
  }

  free(used);
  return mst;
}

static int get_next(int cur, int *used, int size, double **ph, int **g) {
  double *probs = malloc(size * sizeof(double));
  double total = 0.0;

  for (int i = 0; i < size; i++) {
    if (!used[i] && g[cur][i] > 0) {
      double ph_pow = pow(ph[cur][i], ALPHA);
      double dist_pow = pow(1.0 / g[cur][i], BETA);
      probs[i] = ph_pow * dist_pow;
      total += probs[i];
    } else {
      probs[i] = 0.0;
    }
  }

  if (total == 0.0) {
    free(probs);
    return -1;
  }

  for (int i = 0; i < size; i++) {
    probs[i] /= total;
  }

  double random_value = (double)rand() / RAND_MAX;
  double cumulative = 0.0;
  int selected = -1;

  for (int i = 0; i < size; i++) {
    if (!used[i] && g[cur][i] > 0) {
      cumulative += probs[i];
      if (random_value <= cumulative) {
        selected = i;
        break;
      }
    }
  }

  free(probs);
  return selected;
}

static double calc_dist(int *path, int size, int **g) {
  double dist = 0.0;
  for (int i = 0; i < size - 1; i++) {
    if (g[path[i]][path[i + 1]] == 0) {
      return DBL_MAX;
    }
    dist += g[path[i]][path[i + 1]];
  }
  if (g[path[size - 1]][path[0]] == 0) {
    return DBL_MAX;
  }
  dist += g[path[size - 1]][path[0]];
  return dist;
}

tsm_result solve_traveling_salesman_problem(graph *graph) {
  tsm_result result;
  result.vertices = NULL;
  result.distance = -1.0;

  if (graph == NULL || graph->size == 0 || graph->size == 1) {
    return result;
  }

  double **ph = malloc(graph->size * sizeof(double *));
  for (int i = 0; i < (int)graph->size; i++) {
    ph[i] = malloc(graph->size * sizeof(double));
    for (int j = 0; j < (int)graph->size; j++) {
      ph[i][j] = 1.0;
    }
  }

  double best_dist = DBL_MAX;
  int *best_path = malloc(graph->size * sizeof(int));

  srand(time(NULL));

  for (int i = 0; i < TSM_ITERATIONS; i++) {
    int **ant_paths = malloc(ANT_COUNT * sizeof(int *));
    double *ant_dist = malloc(ANT_COUNT * sizeof(double));

    for (int ant = 0; ant < ANT_COUNT; ant++) {
      ant_paths[ant] = malloc(graph->size * sizeof(int));
      int *used = calloc(graph->size, sizeof(int));

      int start = rand() % (int)graph->size;
      ant_paths[ant][0] = start;
      used[start] = 1;

      for (int j = 1; j < (int)graph->size; j++) {
        int cur = ant_paths[ant][j - 1];
        int next = get_next(cur, used, graph->size, ph, graph->matrix);

        if (next == -1) {
          ant_dist[ant] = DBL_MAX;
          break;
        }

        ant_paths[ant][j] = next;
        used[next] = 1;
      }

      if (ant_dist[ant] != DBL_MAX) {
        ant_dist[ant] = calc_dist(ant_paths[ant], graph->size, graph->matrix);

        if (ant_dist[ant] < best_dist) {
          best_dist = ant_dist[ant];
          for (int i = 0; i < (int)graph->size; i++) {
            best_path[i] = ant_paths[ant][i];
          }
        }
      } else {
        ant_dist[ant] = DBL_MAX;
      }

      free(used);
    }

    for (int i = 0; i < (int)graph->size; i++) {
      for (int j = 0; j < (int)graph->size; j++) {
        ph[i][j] *= (1.0 - RATE);
      }
    }

    for (int ant = 0; ant < ANT_COUNT; ant++) {
      if (ant_dist[ant] != DBL_MAX) {
        double delta = Q / ant_dist[ant];
        for (int i = 0; i < (int)graph->size - 1; i++) {
          int from = ant_paths[ant][i];
          int to = ant_paths[ant][i + 1];
          ph[from][to] += delta;
          ph[to][from] += delta;
        }
        int from = ant_paths[ant][graph->size - 1];
        int to = ant_paths[ant][0];
        ph[from][to] += delta;
        ph[to][from] += delta;
      }
    }

    for (int ant = 0; ant < ANT_COUNT; ant++) {
      free(ant_paths[ant]);
    }
    free(ant_paths);
    free(ant_dist);
  }

  if (best_dist == DBL_MAX) {
    free(best_path);
    for (int i = 0; i < (int)graph->size; i++) {
      free(ph[i]);
    }
    free(ph);
    result.vertices = NULL;
    result.distance = -1.0;
    return result;
  }

  result.vertices = malloc((graph->size + 1) * sizeof(int));
  for (int i = 0; i < (int)graph->size; i++) {
    result.vertices[i] = best_path[i] + 1;
  }
  result.vertices[graph->size] = result.vertices[0];
  result.distance = best_dist;

  free(best_path);
  for (int i = 0; i < (int)graph->size; i++) {
    free(ph[i]);
  }
  free(ph);

  return result;
}
