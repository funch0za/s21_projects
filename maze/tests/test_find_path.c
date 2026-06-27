#include "../include/ERR_maze.h"
#include "../include/maze.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

maze_t *create_test_maze(int rows, int cols) {
  maze_t *maze = NULL;
  ERR_maze err = allocate_maze(&maze, rows, cols);
  if (err != NO_ERR) {
    return NULL;
  }
  return maze;
}

void destroy_test_maze(maze_t *maze) { destroy_maze(maze); }

void clear_path(maze_t *maze) {
  if (maze->path != NULL) {
    for (int i = 0; i < maze->rows; i++) {
      memset(maze->path[i], 0, maze->cols * sizeof(int));
    }
  }
}

// Тесты для generate_maze
START_TEST(test_generate_maze_alloc) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 10, 10);
  ck_assert_int_eq(err, NO_ERR);
  ck_assert_ptr_nonnull(maze);
  ck_assert_int_eq(maze->rows, 10);
  ck_assert_int_eq(maze->cols, 10);
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_generate_maze_min_size) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 1, 1);
  ck_assert_int_eq(err, NO_ERR);
  ck_assert_ptr_nonnull(maze);
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_generate_maze_max_size) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 50, 50);
  ck_assert_int_eq(err, NO_ERR);
  ck_assert_ptr_nonnull(maze);
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_generate_maze_invalid_size) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 0, 10);
  ck_assert_int_eq(err, PARAM_ERR);
  err = generate_maze(&maze, 51, 10);
  ck_assert_int_eq(err, PARAM_ERR);
  err = generate_maze(&maze, 10, 0);
  ck_assert_int_eq(err, PARAM_ERR);
  err = generate_maze(&maze, 10, 51);
  ck_assert_int_eq(err, PARAM_ERR);
}
END_TEST

START_TEST(test_generate_maze_no_null_walls) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 5, 5);
  ck_assert_int_eq(err, NO_ERR);
  ck_assert_ptr_nonnull(maze->right_walls);
  ck_assert_ptr_nonnull(maze->bottom_walls);
  for (int i = 0; i < 5; i++) {
    ck_assert_ptr_nonnull(maze->right_walls[i]);
    ck_assert_ptr_nonnull(maze->bottom_walls[i]);
  }
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_generate_maze_borders) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 5, 5);
  ck_assert_int_eq(err, NO_ERR);

  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(maze->bottom_walls[4][i], 1);
  }

  destroy_test_maze(maze);
}
END_TEST

// Тесты для save_maze_to_file
START_TEST(test_save_maze_to_file) {
  maze_t *maze = NULL;
  ERR_maze err = generate_maze(&maze, 3, 3);
  ck_assert_int_eq(err, NO_ERR);

  err = save_maze_to_file(maze, "test_maze.txt");
  ck_assert_int_eq(err, NO_ERR);

  FILE *file = fopen("test_maze.txt", "r");
  ck_assert_ptr_nonnull(file);

  int rows, cols;
  fscanf(file, "%d %d", &rows, &cols);
  ck_assert_int_eq(rows, 3);
  ck_assert_int_eq(cols, 3);

  fclose(file);
  remove("test_maze.txt");
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_save_maze_null) {
  ERR_maze err = save_maze_to_file(NULL, "test.txt");
  ck_assert_int_eq(err, PARAM_ERR);
}
END_TEST

START_TEST(test_save_maze_invalid_filename) {
  maze_t *maze = NULL;
  generate_maze(&maze, 3, 3);
  ERR_maze err = save_maze_to_file(maze, "/invalid/path/test.txt");
  ck_assert_int_eq(err, FILE_ERR);
  destroy_test_maze(maze);
}
END_TEST

// Тесты для find_path_in_maze с файловым вводом
START_TEST(test_path_from_file) {
  FILE *file = fopen("test_input_maze.txt", "w");
  fprintf(file, "3 3\n");
  fprintf(file, "0 0 1\n");
  fprintf(file, "1 0 0\n");
  fprintf(file, "0 0 1\n");
  fprintf(file, "1 0 1\n");
  fprintf(file, "0 0 0\n");
  fprintf(file, "1 1 1\n");
  fclose(file);

  maze_t *maze = NULL;
  ERR_maze err = read_maze(&maze, "test_input_maze.txt");
  ck_assert_int_eq(err, NO_ERR);

  err = find_path_in_maze(maze, 0, 0, 2, 2);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[2][2], 1);

  remove("test_input_maze.txt");
  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_correct_route) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 2, 2);
  ck_assert_int_eq(err, NO_ERR);

  int valid_path = (maze->path[0][0] == 1 && maze->path[2][2] == 1);

  int has_continuity = 0;
  if (maze->path[0][1] == 1 || maze->path[1][0] == 1) {
    has_continuity = 1;
  }

  ck_assert_int_eq(valid_path, 1);

  destroy_test_maze(maze);
}
END_TEST

// Старые тесты find_path
START_TEST(test_path_1x1) {
  maze_t *maze = create_test_maze(1, 1);
  ck_assert_ptr_nonnull(maze);

  ERR_maze err = find_path_in_maze(maze, 0, 0, 0, 0);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_2x2_no_walls) {
  maze_t *maze = create_test_maze(2, 2);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 1, 1);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[1][1], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_2x2_with_wall) {
  maze_t *maze = create_test_maze(2, 2);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }
  maze->bottom_walls[0][0] = 1;

  ERR_maze err = find_path_in_maze(maze, 0, 0, 0, 1);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[0][1], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_invalid_start) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  ERR_maze err = find_path_in_maze(maze, -1, 0, 2, 2);
  ck_assert_int_eq(err, PARAM_ERR);

  err = find_path_in_maze(maze, 3, 0, 2, 2);
  ck_assert_int_eq(err, PARAM_ERR);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_invalid_finish) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  ERR_maze err = find_path_in_maze(maze, 0, 0, -1, 2);
  ck_assert_int_eq(err, PARAM_ERR);

  err = find_path_in_maze(maze, 0, 0, 3, 2);
  ck_assert_int_eq(err, PARAM_ERR);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_3x3) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 2, 2);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[2][2], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_impossible_path) {
  maze_t *maze = create_test_maze(2, 2);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      maze->right_walls[i][j] = 1;
      maze->bottom_walls[i][j] = 1;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 1, 1);
  ck_assert_int_eq(err, PARAM_ERR);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_horizontal) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 0, 2);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[0][1], 1);
  ck_assert_int_eq(maze->path[0][2], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_vertical) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 2, 0);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[1][0], 1);
  ck_assert_int_eq(maze->path[2][0], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_path_with_dead_end) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  maze->right_walls[0][1] = 1;

  ERR_maze err = find_path_in_maze(maze, 0, 0, 2, 2);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][1], 0);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_same_start_finish) {
  maze_t *maze = create_test_maze(3, 3);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 1, 1, 1, 1);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[1][1], 1);

  destroy_test_maze(maze);
}
END_TEST

START_TEST(test_max_size_no_walls) {
  maze_t *maze = create_test_maze(50, 50);
  ck_assert_ptr_nonnull(maze);

  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      maze->right_walls[i][j] = 0;
      maze->bottom_walls[i][j] = 0;
    }
  }

  ERR_maze err = find_path_in_maze(maze, 0, 0, 49, 49);
  ck_assert_int_eq(err, NO_ERR);

  ck_assert_int_eq(maze->path[0][0], 1);
  ck_assert_int_eq(maze->path[49][49], 1);

  destroy_test_maze(maze);
}
END_TEST

Suite *find_path_suite(void) {
  Suite *s = suite_create("Maze Tests");

  TCase *tc_generate = tcase_create("Generate Maze");
  tcase_add_test(tc_generate, test_generate_maze_alloc);
  tcase_add_test(tc_generate, test_generate_maze_min_size);
  tcase_add_test(tc_generate, test_generate_maze_max_size);
  tcase_add_test(tc_generate, test_generate_maze_invalid_size);
  tcase_add_test(tc_generate, test_generate_maze_no_null_walls);
  tcase_add_test(tc_generate, test_generate_maze_borders);

  TCase *tc_save = tcase_create("Save Maze");
  tcase_add_test(tc_save, test_save_maze_to_file);
  tcase_add_test(tc_save, test_save_maze_null);
  tcase_add_test(tc_save, test_save_maze_invalid_filename);

  TCase *tc_path = tcase_create("Find Path");
  tcase_add_test(tc_path, test_path_1x1);
  tcase_add_test(tc_path, test_path_2x2_no_walls);
  tcase_add_test(tc_path, test_path_2x2_with_wall);
  tcase_add_test(tc_path, test_path_3x3);
  tcase_add_test(tc_path, test_path_horizontal);
  tcase_add_test(tc_path, test_path_vertical);
  tcase_add_test(tc_path, test_path_with_dead_end);
  tcase_add_test(tc_path, test_same_start_finish);
  tcase_add_test(tc_path, test_max_size_no_walls);
  tcase_add_test(tc_path, test_path_from_file);
  tcase_add_test(tc_path, test_path_correct_route);

  TCase *tc_error = tcase_create("Error Cases");
  tcase_add_test(tc_error, test_invalid_start);
  tcase_add_test(tc_error, test_invalid_finish);
  tcase_add_test(tc_error, test_impossible_path);

  suite_add_tcase(s, tc_generate);
  suite_add_tcase(s, tc_save);
  suite_add_tcase(s, tc_path);
  suite_add_tcase(s, tc_error);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = find_path_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}