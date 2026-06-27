#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "navigator_err.h"
#include "s21_graph.h"
#include "s21_graph_algorithms.h"

#define FILENAME_LEN 200

int main(void) {
  printf("Welcome to\n");
  printf("---------------------------------------\n");
  printf("█▄░█ ▄▀▄ █░░░█ ▀█▀ ▄▀▀ ▄▀▄ ▀█▀ ▄▀▀▄ █▀▄\n");
  printf("█▀██ █▄█ ░█░█░ ░█░ █░█ █▄█ ░█░ █░░█ █▀▄\n");
  printf("▀░░▀ ▀░▀ ░░▀░░ ▀▀▀ ░▀▀ ▀░▀ ░▀░ ░▀▀░ ▀░▀\n");
  printf("---------------------------------------\n");

  char filename[FILENAME_LEN];
  printf("Enter the file name:\n");
  fgets(filename, FILENAME_LEN, stdin);
  filename[strcspn(filename, "\n")] = 0;
  graph *g = NULL;

  if (load_graph_from_file(&g, filename) != BAD_FILE) {
    printf("Number of vertices: %zu\n", g->size);
    printf("Matrix:\n");
    for (int i = 0; i < (int)g->size; ++i) {
      for (int j = 0; j < (int)g->size; ++j) {
        printf("%d ", g->matrix[i][j]);
      }
      printf("\n");
    }

    printf("\n---------------------------------------\n");
    for (int v = 1; v <= (int)g->size; ++v) {
      int *DFS = depth_first_search(g, v);

      printf("Depth-first search results starting from vertex %d:\n", v);
      for (int i = 0; i < (int)g->size; ++i) {
        printf(" %d ", DFS[i]);
      }
      printf("\n");

      free(DFS);
    }
    printf("---------------------------------------\n");

    printf("\n--------------------------------------\n");
    for (int v = 1; v <= (int)g->size; ++v) {
      int *BFS = breadth_first_search(g, v);

      printf("Breadth-first search results starting from vertex %d:\n", v);
      for (int i = 0; i < (int)g->size; ++i) {
        printf(" %d ", BFS[i]);
      }
      printf("\n");

      free(BFS);
    }
    printf("--------------------------------------\n");

    printf("\n--------------------------------------\n");
    printf(
        "Finding the shortest path between two random vertices using "
        "Dijkstra's algorithm:\n");
    int start = rand() % g->size;
    int end = rand() % g->size;

    int shortest_path = get_shortest_path_between_vertices(g, start, end);
    printf(
        "Start vertex: %d\nFinish vertex: %d\nThe length of the shortest path: "
        "%d\n",
        start, end, shortest_path);
    printf("--------------------------------------\n");

    printf("\n--------------------------------------\n");
    int **floyd_result = get_shortest_paths_between_all_vertices(g);
    printf("Shortest paths between all vertices:\n");
    for (int i = 0; i < (int)g->size; ++i) {
      for (int j = 0; j < (int)g->size; ++j) {
        printf("%d ", floyd_result[i][j]);
      }
      free(floyd_result[i]);
      floyd_result[i] = NULL;
      printf("\n");
    }
    free(floyd_result);
    printf("--------------------------------------\n");

    printf("\n--------------------------------------\n");
    int **MST = get_least_spanning_tree(g);
    printf("Least spanning tree:\n");
    for (int i = 0; i < (int)g->size; ++i) {
      for (int j = 0; j < (int)g->size; ++j) {
        printf("%d ", MST[i][j]);
      }
      free(MST[i]);
      MST[i] = NULL;
      printf("\n");
    }
    free(MST);
    printf("--------------------------------------\n");

    printf("\n--------------------------------------\n");
    printf("Traveling Salesman Problem (Ant Algorithm):\n");
    tsm_result tsm = solve_traveling_salesman_problem(g);
    if (tsm.vertices != NULL && tsm.distance > 0) {
      printf("Best route found:\n");
      for (int i = 0; i <= (int)g->size; i++) {
        printf("%d ", tsm.vertices[i]);
      }
      printf("\nRoute length: %.2f\n", tsm.distance);
      free(tsm.vertices);
    } else {
      printf("No valid route found! The graph may be disconnected!\n");
    }
    printf("--------------------------------------\n");

    free_graph(g);

  } else {
    printf("The file does not exist!!!\n");
  }

  return 0;
}
