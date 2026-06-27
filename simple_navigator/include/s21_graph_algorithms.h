#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include "navigator_err.h"
#include "s21_graph.h"

int *depth_first_search(graph *graph, int start_vertex);
int *breadth_first_search(graph *graph, int start_vertex);
int get_shortest_path_between_vertices(graph *graph, int vertex1, int vertex2);
int **get_shortest_paths_between_all_vertices(graph *graph);
int **get_least_spanning_tree(graph *graph);

// TSM
typedef struct {
  int *vertices;
  double distance;
} tsm_result;

#define ANT_COUNT 50
#define TSM_ITERATIONS 100
#define ALPHA 1.0
#define BETA 2.0
#define RATE 0.5
#define Q 100.0

tsm_result solve_traveling_salesman_problem(graph *graph);

#endif
