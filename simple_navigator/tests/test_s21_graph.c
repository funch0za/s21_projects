#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

START_TEST(test_allocate_graph_success) {
  graph *g = NULL;
  err result = allocate_graph(&g, 5);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ptr_nonnull(g);
  ck_assert_int_eq(g->size, 5);
  ck_assert_ptr_nonnull(g->matrix);
  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_nonnull(g->matrix[i]);
  }
  free_graph(g);
}
END_TEST

START_TEST(test_allocate_graph_invalid_params) {
  graph *g = NULL;
  err result = allocate_graph(NULL, 5);
  ck_assert_int_eq(result, INVALID_PARAMS);

  result = allocate_graph(&g, 0);
  ck_assert_int_eq(result, INVALID_PARAMS);

  result = allocate_graph(&g, -1);
  ck_assert_int_eq(result, OUT_OF_MEMORY);
}
END_TEST

START_TEST(test_load_graph_from_file_success) {
  FILE *test_file = fopen("test_graph.txt", "w");
  fprintf(test_file, "3\n");
  fprintf(test_file, "0 1 0\n");
  fprintf(test_file, "1 0 1\n");
  fprintf(test_file, "0 1 0\n");
  fclose(test_file);

  graph *g = NULL;
  err result = load_graph_from_file(&g, "test_graph.txt");
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ptr_nonnull(g);
  ck_assert_int_eq(g->size, 3);
  ck_assert_int_eq(g->matrix[0][1], 1);
  ck_assert_int_eq(g->matrix[1][0], 1);
  ck_assert_int_eq(g->matrix[1][2], 1);

  free_graph(g);
  remove("test_graph.txt");
}
END_TEST

START_TEST(test_load_graph_from_file_invalid_params) {
  graph *g = NULL;
  err result = load_graph_from_file(NULL, "sdifsdjfnjksdnfjksdnfj.txt");
  ck_assert_int_eq(result, INVALID_PARAMS);

  result = load_graph_from_file(&g, NULL);
  ck_assert_int_eq(result, INVALID_PARAMS);
}
END_TEST

START_TEST(test_load_graph_from_file_bad_file) {
  graph *g = NULL;
  err result = load_graph_from_file(&g, "nonexistent.txt");
  ck_assert_int_eq(result, BAD_FILE);
}
END_TEST

START_TEST(test_export_graph_to_dot_success) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 1;
  g->matrix[1][2] = 2;

  err result = export_graph_to_dot(g, "test_graph.dot");
  ck_assert_int_eq(result, SUCCESS);

  FILE *dot_file = fopen("test_graph.dot", "r");
  ck_assert_ptr_nonnull(dot_file);
  fclose(dot_file);

  free_graph(g);
  remove("test_graph.dot");
}
END_TEST

START_TEST(test_export_graph_to_dot_invalid_params) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  err result = export_graph_to_dot(NULL, "test.dot");
  ck_assert_int_eq(result, INVALID_PARAMS);

  result = export_graph_to_dot(g, NULL);
  ck_assert_int_eq(result, INVALID_PARAMS);

  free_graph(g);
}
END_TEST

START_TEST(test_free_graph) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  ck_assert_ptr_nonnull(g);
  free_graph(g);
  g = NULL;
  ck_assert_ptr_null(g);

  free_graph(NULL);
}
END_TEST

START_TEST(test_depth_first_search_valid) {
  graph *g = NULL;
  allocate_graph(&g, 5);
  g->matrix[0][1] = 1;
  g->matrix[0][2] = 1;
  g->matrix[1][3] = 1;
  g->matrix[2][4] = 1;

  int *result = depth_first_search(g, 1);
  ck_assert_ptr_nonnull(result);

  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_depth_first_search_invalid_start) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  int *result = depth_first_search(g, 0);
  ck_assert_ptr_null(result);

  result = depth_first_search(g, 4);
  ck_assert_ptr_null(result);

  free_graph(g);
}
END_TEST

START_TEST(test_depth_first_search_null_graph) {
  int *result = depth_first_search(NULL, 1);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_breadth_first_search_valid) {
  graph *g = NULL;
  allocate_graph(&g, 5);
  g->matrix[0][1] = 1;
  g->matrix[0][2] = 1;
  g->matrix[1][3] = 1;
  g->matrix[2][4] = 1;

  int *result = breadth_first_search(g, 1);
  ck_assert_ptr_nonnull(result);

  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_breadth_first_search_invalid_start) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  int *result = breadth_first_search(g, 0);
  ck_assert_ptr_null(result);

  result = breadth_first_search(g, 5);
  ck_assert_ptr_null(result);

  free_graph(g);
}
END_TEST

START_TEST(test_breadth_first_search_null_graph) {
  int *result = breadth_first_search(NULL, 1);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_breadth_first_search_complex) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  g->matrix[0][1] = 1;
  g->matrix[0][2] = 1;
  g->matrix[1][2] = 1;
  g->matrix[2][3] = 1;

  int *result = breadth_first_search(g, 1);
  ck_assert_ptr_nonnull(result);

  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_breadth_first_search_single_vertex) {
  graph *g = NULL;
  allocate_graph(&g, 1);

  int *result = breadth_first_search(g, 1);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(result[0], 1);

  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_path_between_vertices_simple) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 5;
  g->matrix[1][2] = 3;
  g->matrix[0][2] = 10;

  int result = get_shortest_path_between_vertices(g, 1, 3);
  ck_assert_int_eq(result, 8);

  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_path_between_vertices_direct) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  g->matrix[0][1] = 2;
  g->matrix[0][2] = 6;
  g->matrix[1][2] = 3;
  g->matrix[1][3] = 5;
  g->matrix[2][3] = 1;

  int result = get_shortest_path_between_vertices(g, 1, 4);
  ck_assert_int_eq(result, 6);

  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_path_between_vertices_no_path) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 5;

  int result = get_shortest_path_between_vertices(g, 1, 3);
  ck_assert_int_eq(result, -1);

  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_path_between_vertices_invalid_input) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  int result = get_shortest_path_between_vertices(NULL, 1, 2);
  ck_assert_int_eq(result, -1);

  result = get_shortest_path_between_vertices(g, 0, 2);
  ck_assert_int_eq(result, -1);

  result = get_shortest_path_between_vertices(g, 1, 4);
  ck_assert_int_eq(result, -1);

  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_path_between_vertices_same_vertex) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 5;

  int result = get_shortest_path_between_vertices(g, 2, 2);
  ck_assert_int_eq(result, 0);

  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_paths_between_all_vertices_simple) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 5;
  g->matrix[1][2] = 3;
  g->matrix[0][2] = 10;

  int **result = get_shortest_paths_between_all_vertices(g);
  ck_assert_ptr_nonnull(result);

  ck_assert_int_eq(result[0][0], 0);
  ck_assert_int_eq(result[0][1], 5);
  ck_assert_int_eq(result[0][2], 8);
  ck_assert_int_eq(result[1][0], -1);
  ck_assert_int_eq(result[1][1], 0);
  ck_assert_int_eq(result[1][2], 3);
  ck_assert_int_eq(result[2][0], -1);
  ck_assert_int_eq(result[2][1], -1);
  ck_assert_int_eq(result[2][2], 0);

  for (int i = 0; i < 3; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_paths_between_all_vertices_complex) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  g->matrix[0][1] = 2;
  g->matrix[0][2] = 6;
  g->matrix[1][2] = 3;
  g->matrix[1][3] = 5;
  g->matrix[2][3] = 1;

  int **result = get_shortest_paths_between_all_vertices(g);
  ck_assert_ptr_nonnull(result);

  ck_assert_int_eq(result[0][0], 0);
  ck_assert_int_eq(result[0][1], 2);
  ck_assert_int_eq(result[0][2], 5);
  ck_assert_int_eq(result[0][3], 6);

  ck_assert_int_eq(result[1][0], -1);
  ck_assert_int_eq(result[1][1], 0);
  ck_assert_int_eq(result[1][2], 3);
  ck_assert_int_eq(result[1][3], 4);

  ck_assert_int_eq(result[2][0], -1);
  ck_assert_int_eq(result[2][1], -1);
  ck_assert_int_eq(result[2][2], 0);
  ck_assert_int_eq(result[2][3], 1);

  for (int i = 0; i < 4; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_shortest_paths_between_all_vertices_null_graph) {
  int **result = get_shortest_paths_between_all_vertices(NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_get_shortest_paths_between_all_vertices_single_vertex) {
  graph *g = NULL;
  allocate_graph(&g, 1);

  int **result = get_shortest_paths_between_all_vertices(g);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(result[0][0], 0);

  free(result[0]);
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_simple_graph) {
  graph *g = NULL;
  allocate_graph(&g, 4);

  g->matrix[0][1] = 2;
  g->matrix[0][2] = 4;
  g->matrix[0][3] = 1;
  g->matrix[1][0] = 2;
  g->matrix[1][2] = 3;
  g->matrix[1][3] = 5;
  g->matrix[2][0] = 4;
  g->matrix[2][1] = 3;
  g->matrix[2][3] = 6;
  g->matrix[3][0] = 1;
  g->matrix[3][1] = 5;
  g->matrix[3][2] = 6;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 6);

  ck_assert_int_eq(result[0][1], 2);
  ck_assert_int_eq(result[0][3], 1);
  ck_assert_int_eq(result[1][2], 3);

  for (int i = 0; i < 4; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_path_graph) {
  graph *g = NULL;
  allocate_graph(&g, 5);

  g->matrix[0][1] = 1;
  g->matrix[1][2] = 2;
  g->matrix[2][3] = 3;
  g->matrix[3][4] = 4;

  g->matrix[1][0] = 1;
  g->matrix[2][1] = 2;
  g->matrix[3][2] = 3;
  g->matrix[4][3] = 4;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 5; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 10);

  ck_assert_int_eq(result[0][1], 1);
  ck_assert_int_eq(result[1][2], 2);
  ck_assert_int_eq(result[2][3], 3);
  ck_assert_int_eq(result[3][4], 4);

  for (int i = 0; i < 5; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_complete_graph) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  g->matrix[0][1] = 5;
  g->matrix[0][2] = 1;
  g->matrix[1][2] = 2;

  g->matrix[1][0] = 5;
  g->matrix[2][0] = 1;
  g->matrix[2][1] = 2;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 3);

  ck_assert_int_eq(result[0][2], 1);
  ck_assert_int_eq(result[1][2], 2);

  for (int i = 0; i < 3; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_single_vertex) {
  graph *g = NULL;
  allocate_graph(&g, 1);

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(result[0][0], 0);

  free(result[0]);
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_two_vertices) {
  graph *g = NULL;
  allocate_graph(&g, 2);

  g->matrix[0][1] = 10;
  g->matrix[1][0] = 10;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = i + 1; j < 2; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 10);
  ck_assert_int_eq(result[0][1], 10);

  for (int i = 0; i < 2; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_null_graph) {
  int **result = get_least_spanning_tree(NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_get_least_spanning_tree_empty_graph) {
  graph *g = NULL;
  allocate_graph(&g, 0);

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_null(result);

  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_complex_graph) {
  graph *g = NULL;
  allocate_graph(&g, 6);

  g->matrix[0][1] = 4;
  g->matrix[0][2] = 3;
  g->matrix[1][2] = 1;
  g->matrix[1][3] = 2;
  g->matrix[2][3] = 4;
  g->matrix[3][4] = 2;
  g->matrix[4][5] = 6;
  g->matrix[2][5] = 5;

  g->matrix[1][0] = 4;
  g->matrix[2][0] = 3;
  g->matrix[2][1] = 1;
  g->matrix[3][1] = 2;
  g->matrix[3][2] = 4;
  g->matrix[4][3] = 2;
  g->matrix[5][4] = 6;
  g->matrix[5][2] = 5;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = i + 1; j < 6; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 13);

  ck_assert_int_eq(result[1][2], 1);
  ck_assert_int_eq(result[1][3], 2);
  ck_assert_int_eq(result[3][4], 2);
  ck_assert_int_eq(result[0][2], 3);
  ck_assert_int_eq(result[2][5], 5);

  for (int i = 0; i < 6; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_symmetric) {
  graph *g = NULL;
  allocate_graph(&g, 3);

  g->matrix[0][1] = 7;
  g->matrix[1][0] = 7;
  g->matrix[0][2] = 8;
  g->matrix[2][0] = 8;
  g->matrix[1][2] = 9;
  g->matrix[2][1] = 9;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_int_eq(result[i][j], result[j][i]);
    }
  }

  for (int i = 0; i < 3; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_no_cycles) {
  graph *g = NULL;
  allocate_graph(&g, 4);

  g->matrix[0][1] = 2;
  g->matrix[0][2] = 3;
  g->matrix[0][3] = 4;
  g->matrix[1][2] = 1;
  g->matrix[1][3] = 5;
  g->matrix[2][3] = 6;

  g->matrix[1][0] = 2;
  g->matrix[2][0] = 3;
  g->matrix[3][0] = 4;
  g->matrix[2][1] = 1;
  g->matrix[3][1] = 5;
  g->matrix[3][2] = 6;

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int edge_count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (result[i][j] != 0) {
        edge_count++;
      }
    }
  }
  ck_assert_int_eq(edge_count, 3);

  for (int i = 0; i < 4; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_get_least_spanning_tree_all_edges_same_weight) {
  graph *g = NULL;
  allocate_graph(&g, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      g->matrix[i][j] = 1;
      g->matrix[j][i] = 1;
    }
  }

  int **result = get_least_spanning_tree(g);
  ck_assert_ptr_nonnull(result);

  int total_weight = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      total_weight += result[i][j];
    }
  }
  ck_assert_int_eq(total_weight, 3);

  for (int i = 0; i < 4; i++) {
    free(result[i]);
  }
  free(result);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_null_graph) {
  tsm_result result = solve_traveling_salesman_problem(NULL);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);
}
END_TEST

START_TEST(test_tsm_empty_graph) {
  graph *g = NULL;
  allocate_graph(&g, 0);
  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_single_vertex) {
  graph *g = NULL;
  allocate_graph(&g, 1);
  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_two_vertices_connected) {
  graph *g = NULL;
  allocate_graph(&g, 2);
  g->matrix[0][1] = 5;
  g->matrix[1][0] = 5;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_ge(result.distance, 0.0);
  ck_assert_int_eq(result.vertices[0], result.vertices[2]);
  ck_assert_int_eq(result.vertices[0], 1);
  ck_assert_int_eq(result.vertices[1], 2);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_two_vertices_disconnected) {
  graph *g = NULL;
  allocate_graph(&g, 2);
  g->matrix[0][1] = 0;
  g->matrix[1][0] = 0;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);

  free_graph(g);
}
END_TEST

START_TEST(test_tsm_triangle_equal_edges) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 1;
  g->matrix[0][2] = 1;
  g->matrix[1][2] = 1;
  g->matrix[1][0] = 1;
  g->matrix[2][0] = 1;
  g->matrix[2][1] = 1;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_eq(result.distance, 3.0);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_triangle_different_edges) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 2;
  g->matrix[0][2] = 5;
  g->matrix[1][2] = 3;
  g->matrix[1][0] = 2;
  g->matrix[2][0] = 5;
  g->matrix[2][1] = 3;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_eq(result.distance, 10.0);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_square_complete_graph) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        g->matrix[i][j] = 1;
      }
    }
  }

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_eq(result.distance, 4.0);
  ck_assert_int_eq(result.vertices[0], result.vertices[4]);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_square_with_weights) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  g->matrix[0][1] = 2;
  g->matrix[0][2] = 4;
  g->matrix[0][3] = 3;
  g->matrix[1][0] = 2;
  g->matrix[1][2] = 1;
  g->matrix[1][3] = 5;
  g->matrix[2][0] = 4;
  g->matrix[2][1] = 1;
  g->matrix[2][3] = 6;
  g->matrix[3][0] = 3;
  g->matrix[3][1] = 5;
  g->matrix[3][2] = 6;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert(result.distance > 0);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_disconnected_graph) {
  graph *g = NULL;
  allocate_graph(&g, 5);
  g->matrix[0][1] = 1;
  g->matrix[1][0] = 1;
  g->matrix[2][3] = 1;
  g->matrix[3][2] = 1;
  g->matrix[3][4] = 1;
  g->matrix[4][3] = 1;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);

  free_graph(g);
}
END_TEST

START_TEST(test_tsm_line_graph) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  g->matrix[0][1] = 1;
  g->matrix[1][2] = 1;
  g->matrix[2][3] = 1;
  g->matrix[1][0] = 1;
  g->matrix[2][1] = 1;
  g->matrix[3][2] = 1;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_null(result.vertices);
  ck_assert_double_eq(result.distance, -1.0);

  free_graph(g);
}
END_TEST

START_TEST(test_tsm_cycle_graph) {
  graph *g = NULL;
  allocate_graph(&g, 5);
  for (int i = 0; i < 5; i++) {
    g->matrix[i][(i + 1) % 5] = 1;
    g->matrix[(i + 1) % 5][i] = 1;
  }

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_eq(result.distance, 5.0);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_vertex_visited_once) {
  graph *g = NULL;
  allocate_graph(&g, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        g->matrix[i][j] = 1;
      }
    }
  }

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);

  int vertex_count[5] = {0};
  for (int i = 0; i < 4; i++) {
    vertex_count[result.vertices[i]]++;
  }

  for (int i = 1; i <= 4; i++) {
    ck_assert_int_eq(vertex_count[i], 1);
  }

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_return_to_start) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 2;
  g->matrix[0][2] = 3;
  g->matrix[1][2] = 4;
  g->matrix[1][0] = 2;
  g->matrix[2][0] = 3;
  g->matrix[2][1] = 4;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_int_eq(result.vertices[0], result.vertices[3]);

  free(result.vertices);
  free_graph(g);
}
END_TEST

START_TEST(test_tsm_positive_distance) {
  graph *g = NULL;
  allocate_graph(&g, 3);
  g->matrix[0][1] = 5;
  g->matrix[0][2] = 7;
  g->matrix[1][2] = 3;
  g->matrix[1][0] = 5;
  g->matrix[2][0] = 7;
  g->matrix[2][1] = 3;

  tsm_result result = solve_traveling_salesman_problem(g);
  ck_assert_ptr_nonnull(result.vertices);
  ck_assert_double_gt(result.distance, 0.0);

  free(result.vertices);
  free_graph(g);
}
END_TEST

Suite *graph_suite(void) {
  Suite *s = suite_create("s21_navigator");

  TCase *tc_s21_graph = tcase_create("s21_graph");
  tcase_add_test(tc_s21_graph, test_allocate_graph_success);
  tcase_add_test(tc_s21_graph, test_allocate_graph_invalid_params);
  tcase_add_test(tc_s21_graph, test_load_graph_from_file_success);
  tcase_add_test(tc_s21_graph, test_load_graph_from_file_invalid_params);
  tcase_add_test(tc_s21_graph, test_load_graph_from_file_bad_file);
  tcase_add_test(tc_s21_graph, test_export_graph_to_dot_success);
  tcase_add_test(tc_s21_graph, test_export_graph_to_dot_invalid_params);
  tcase_add_test(tc_s21_graph, test_free_graph);
  suite_add_tcase(s, tc_s21_graph);

  TCase *tc_s21_graph_algorithms_DFS_BFS =
      tcase_create("s21_graph_algorithms: BFS and DFS");
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_depth_first_search_valid);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_depth_first_search_invalid_start);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_depth_first_search_null_graph);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_breadth_first_search_valid);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_breadth_first_search_invalid_start);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_breadth_first_search_null_graph);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_breadth_first_search_complex);
  tcase_add_test(tc_s21_graph_algorithms_DFS_BFS,
                 test_breadth_first_search_single_vertex);
  suite_add_tcase(s, tc_s21_graph_algorithms_DFS_BFS);

  TCase *tc_s21_graph_algorithms_dijkstra_floyd =
      tcase_create("s21_graph_algorithms: dijkstra and floyd");
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_path_between_vertices_simple);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_path_between_vertices_direct);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_path_between_vertices_no_path);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_path_between_vertices_invalid_input);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_path_between_vertices_same_vertex);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_paths_between_all_vertices_simple);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_paths_between_all_vertices_complex);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_paths_between_all_vertices_null_graph);
  tcase_add_test(tc_s21_graph_algorithms_dijkstra_floyd,
                 test_get_shortest_paths_between_all_vertices_single_vertex);
  suite_add_tcase(s, tc_s21_graph_algorithms_dijkstra_floyd);

  TCase *tc_s21_graph_algorithms_MST =
      tcase_create("s21_graph_algorithms: MST");
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_simple_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_path_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_complete_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_single_vertex);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_two_vertices);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_null_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_empty_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_complex_graph);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_symmetric);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_no_cycles);
  tcase_add_test(tc_s21_graph_algorithms_MST,
                 test_get_least_spanning_tree_all_edges_same_weight);
  suite_add_tcase(s, tc_s21_graph_algorithms_MST);

  TCase *tc_s21_graph_algorithms_tsm = tcase_create("TSM");
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_null_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_empty_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_single_vertex);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_two_vertices_connected);
  tcase_add_test(tc_s21_graph_algorithms_tsm,
                 test_tsm_two_vertices_disconnected);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_triangle_equal_edges);
  tcase_add_test(tc_s21_graph_algorithms_tsm,
                 test_tsm_triangle_different_edges);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_square_complete_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_square_with_weights);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_disconnected_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_line_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_cycle_graph);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_vertex_visited_once);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_return_to_start);
  tcase_add_test(tc_s21_graph_algorithms_tsm, test_tsm_positive_distance);

  suite_add_tcase(s, tc_s21_graph_algorithms_tsm);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = graph_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
