#include "maze.h"

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ERR_maze.h"
#include "queue.h"

ERR_maze allocate_maze(maze_t **maze, int rows, int cols) {
  *maze = calloc(1, sizeof(maze_t));
  if (!*maze) {
    return MEM_ERR;
  }

  if (0 >= rows || rows > MAX_ROWS || 0 >= cols || cols > MAX_COLS) {
    return PARAM_ERR;
  }

  (*maze)->rows = rows;
  (*maze)->cols = cols;

  (*maze)->path = NULL;
  (*maze)->right_walls = calloc(rows, sizeof(int *));
  (*maze)->bottom_walls = calloc(rows, sizeof(int *));
  if (!(*maze)->right_walls || !(*maze)->bottom_walls) {
    free((*maze)->right_walls);
    free((*maze)->bottom_walls);
    free(*maze);
    *maze = NULL;
    return MEM_ERR;
  }

  for (int i = 0; i < rows; ++i) {
    (*maze)->right_walls[i] = calloc(cols, sizeof(int));
    (*maze)->bottom_walls[i] = calloc(cols, sizeof(int));
    if (!(*maze)->right_walls[i] || !(*maze)->bottom_walls[i]) {
      for (int j = 0; j <= i; ++j) {
        free((*maze)->right_walls[j]);
        free((*maze)->bottom_walls[j]);
      }
      free((*maze)->right_walls);
      free((*maze)->bottom_walls);
      free(*maze);
      *maze = NULL;
      return MEM_ERR;
    }
  }

  return NO_ERR;
}

ERR_maze generate_maze(maze_t **maze, int rows, int cols) {
  srand(time(NULL));

  ERR_maze err = allocate_maze(maze, rows, cols);
  if (err != NO_ERR) {
    return err;
  }

  int next_id = (*maze)->cols;
  int *row = calloc((*maze)->cols, sizeof(int));
  if (row == NULL) {
    return MEM_ERR;
  }
  for (int i = 0; i < (*maze)->cols; ++i) {
    row[i] = i;
  }

  for (int i = 0; i < (*maze)->rows; ++i) {
    for (int j = 0; j < (*maze)->cols - 1; ++j) {
      int flag_add_wall = rand() % 2;

      if (row[j] == row[j + 1] || flag_add_wall) {
        (*maze)->right_walls[i][j] = 1;
      } else {
        (*maze)->right_walls[i][j] = 0;
        int deleted_set = row[j + 1];
        int new_set = row[j];
        for (int k = 0; k < (*maze)->cols; ++k) {
          if (row[k] == deleted_set) {
            row[k] = new_set;
          }
        }
      }
    }

    int *has_bottom_free = calloc(next_id + (*maze)->cols, sizeof(int));
    if (has_bottom_free == NULL) {
      free(row);
      return MEM_ERR;
    }

    for (int j = 0; j < (*maze)->cols; ++j) {
      int current_set = row[j];

      int cnt_cells = 0;
      for (int k = 0; k < (*maze)->cols; ++k) {
        if (row[k] == current_set) {
          cnt_cells++;
        }
      }

      if (cnt_cells == 1) {
        (*maze)->bottom_walls[i][j] = 0;
        has_bottom_free[current_set] = 1;
        continue;
      }

      int add_wall = rand() % 2;

      if (!add_wall) {
        (*maze)->bottom_walls[i][j] = 0;
        has_bottom_free[current_set] = 1;
      } else {
        if (has_bottom_free[current_set]) {
          (*maze)->bottom_walls[i][j] = 1;
        } else {
          (*maze)->bottom_walls[i][j] = 0;
          has_bottom_free[current_set] = 1;
        }
      }
    }
    free(has_bottom_free);
    has_bottom_free = NULL;

    if (i + 1 < (*maze)->rows) {
      for (int j = 0; j < (*maze)->cols; ++j) {
        if ((*maze)->bottom_walls[i][j]) {
          row[j] = next_id++;
        }
      }
    } else {
      for (int j = 0; j < (*maze)->cols - 1; ++j) {
        if (row[j] != row[j + 1]) {
          (*maze)->right_walls[i][j] = 0;
          int old_set = row[j + 1];
          int new_set = row[j];
          for (int k = 0; k < (*maze)->cols; ++k) {
            if (row[k] == old_set) {
              row[k] = new_set;
            }
          }
        }
      }

      for (int j = 0; j < (*maze)->cols; ++j) {
        (*maze)->bottom_walls[i][j] = 1;
      }
    }
  }

  free(row);
  row = NULL;
  return NO_ERR;
}

ERR_maze read_maze(maze_t **maze, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return FILE_ERR;
  }

  int rows, cols;
  if (fscanf(file, "%d %d", &rows, &cols) != 2) {
    fclose(file);
    return FILE_ERR;
  }

  ERR_maze err = allocate_maze(maze, rows, cols);
  if (err != NO_ERR) {
    fclose(file);
    return err;
  }

  for (int i = 0; i < (*maze)->rows; i++) {
    for (int j = 0; j < (*maze)->cols; j++) {
      if (fscanf(file, "%d", &(*maze)->right_walls[i][j]) != 1) {
        fclose(file);
        return FILE_ERR;
      }
    }
  }

  for (int i = 0; i < (*maze)->rows; i++) {
    for (int j = 0; j < (*maze)->cols; j++) {
      if (fscanf(file, "%d", &(*maze)->bottom_walls[i][j]) != 1) {
        fclose(file);
        return FILE_ERR;
      }
    }
  }

  fclose(file);
  return NO_ERR;
}

ERR_maze save_maze_to_file(maze_t *maze, const char *filename) {
  if (maze == NULL || filename == NULL) {
    return PARAM_ERR;
  }

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return FILE_ERR;
  }

  fprintf(file, "%d %d\n", maze->rows, maze->cols);

  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->cols; j++) {
      fprintf(file, "%d ", maze->right_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->cols; j++) {
      fprintf(file, "%d ", maze->bottom_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
  return NO_ERR;
}

ERR_maze destroy_maze(maze_t *maze) {
  if (maze == NULL) {
    return MEM_ERR;
  }

  if (maze->right_walls != NULL && maze->bottom_walls != NULL) {
    for (int i = 0; i < maze->rows; i++) {
      free(maze->right_walls[i]);
      maze->right_walls[i] = NULL;

      free(maze->bottom_walls[i]);
      maze->bottom_walls[i] = NULL;
    }
  } else {
    return MEM_ERR;
  }

  free(maze->right_walls);
  maze->right_walls = NULL;

  free(maze->bottom_walls);
  maze->bottom_walls = NULL;

  free(maze);
  maze = NULL;

  return NO_ERR;
}

ERR_maze find_path_in_maze(maze_t *maze, int start_i, int start_j, int finish_i,
                           int finish_j) {
  if (maze == NULL || maze->right_walls == NULL || maze->bottom_walls == NULL) {
    return PARAM_ERR;
  }

  if (start_i < 0 || start_i >= maze->rows || start_j < 0 ||
      start_j >= maze->cols || finish_i < 0 || finish_i >= maze->rows ||
      finish_j < 0 || finish_j >= maze->cols) {
    return PARAM_ERR;
  }

  int **visited = calloc(maze->rows, sizeof(int *));
  if (visited == NULL) {
    return MEM_ERR;
  }

  for (int i = 0; i < maze->rows; i++) {
    visited[i] = calloc(maze->cols, sizeof(int));
    if (visited[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(visited[j]);
      }
      free(visited);
      return MEM_ERR;
    }
  }

  Point ***prev = calloc(maze->rows, sizeof(Point **));
  if (prev == NULL) {
    for (int i = 0; i < maze->rows; i++) {
      free(visited[i]);
    }
    free(visited);
    return MEM_ERR;
  }

  for (int i = 0; i < maze->rows; i++) {
    prev[i] = calloc(maze->cols, sizeof(Point *));
    if (prev[i] == NULL) {
      for (int j = 0; j < i; j++)
        free(prev[j]);
      free(prev);
      for (int j = 0; j < maze->rows; j++) {
        free(visited[j]);
      }
      free(visited);
      return MEM_ERR;
    }

    for (int j = 0; j < maze->cols; j++) {
      prev[i][j] = malloc(sizeof(Point));
      if (prev[i][j] == NULL) {
        for (int k = 0; k <= i; k++) {
          for (int l = 0; l < j; l++) {
            if (prev[k][l]) {
              free(prev[k][l]);
            }
          }
          if (prev[k]) {
            free(prev[k]);
          }
        }
        free(prev);
        for (int k = 0; k < maze->rows; k++) {
          free(visited[k]);
        }
        free(visited);
        return MEM_ERR;
      }
      prev[i][j]->row = -1;
      prev[i][j]->col = -1;
    }
  }

  queue_t *queue = queue_create();
  if (queue == NULL) {
    for (int i = 0; i < maze->rows; i++) {
      for (int j = 0; j < maze->cols; j++) {
        free(prev[i][j]);
      }
      free(prev[i]);
      free(visited[i]);
    }
    free(prev);
    free(visited);
    return MEM_ERR;
  }

  queue_push(queue, start_i, start_j);
  visited[start_i][start_j] = 1;

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};
  int found = 0;
  Point current;

  while (!queue_is_empty(queue) && !found) {
    current = queue_pop(queue);

    if (current.row == finish_i && current.col == finish_j) {
      found = 1;
      break;
    }

    for (int dir = 0; dir < 4; dir++) {
      int new_row = current.row + dr[dir];
      int new_col = current.col + dc[dir];

      if (new_row < 0 || new_row >= maze->rows || new_col < 0 ||
          new_col >= maze->cols) {
        continue;
      }

      if (visited[new_row][new_col]) {
        continue;
      }

      int has_wall = 0;

      if (dir == 0) {
        if (current.row > 0) {
          has_wall = maze->bottom_walls[current.row - 1][current.col];
        } else {
          has_wall = 1;
        }
      } else if (dir == 1) {
        if (current.row < maze->rows - 1) {
          has_wall = maze->bottom_walls[current.row][current.col];
        } else {
          has_wall = 1;
        }
      } else if (dir == 2) {
        if (current.col > 0) {
          has_wall = maze->right_walls[current.row][current.col - 1];
        } else {
          has_wall = 1;
        }
      } else if (dir == 3) {
        if (current.col < maze->cols - 1) {
          has_wall = maze->right_walls[current.row][current.col];
        } else {
          has_wall = 1;
        }
      }

      if (!has_wall) {
        visited[new_row][new_col] = 1;
        prev[new_row][new_col]->row = current.row;
        prev[new_row][new_col]->col = current.col;
        queue_push(queue, new_row, new_col);
      }
    }
  }

  if (found) {
    if (maze->path == NULL) {
      maze->path = calloc(maze->rows, sizeof(int *));
      if (maze->path != NULL) {
        for (int i = 0; i < maze->rows; i++) {
          maze->path[i] = calloc(maze->cols, sizeof(int));
        }
      }
    }

    if (maze->path != NULL) {
      Point path_point;
      path_point.row = finish_i;
      path_point.col = finish_j;

      while (1) {
        maze->path[path_point.row][path_point.col] = 1;

        if (path_point.row == start_i && path_point.col == start_j) {
          break;
        }

        int next_row = prev[path_point.row][path_point.col]->row;
        int next_col = prev[path_point.row][path_point.col]->col;

        if (next_row == -1 || next_col == -1) {
          break;
        }

        path_point.row = next_row;
        path_point.col = next_col;
      }
    }
  }

  queue_destroy(queue);

  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->cols; j++) {
      if (prev[i][j] != NULL) {
        free(prev[i][j]);
      }
    }
    free(prev[i]);
    free(visited[i]);
  }
  free(prev);
  free(visited);

  return found ? NO_ERR : PARAM_ERR;
}