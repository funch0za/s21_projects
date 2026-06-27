#include "maze_image.h"
#include "ERR_maze.h"
#include "maze.h"
#include <stdlib.h>

ERR_maze create_image_maze(maze_t *maze, maze_image_t **maze_image) {
  if (maze == NULL || maze->bottom_walls == NULL || maze->right_walls == NULL) {
    return PARAM_ERR;
  }

  int rows = maze->rows;
  int cols = maze->cols;

  *maze_image = calloc(1, sizeof(maze_image_t));

  (*maze_image)->rows = rows * 2 + 1;
  (*maze_image)->cols = cols * 4 + 1;

  (*maze_image)->img = calloc((*maze_image)->rows, sizeof(char *));
  if ((*maze_image)->img == NULL) {
    return MEM_ERR;
  }

  ((*maze_image)->img)[0] = calloc((*maze_image)->cols + 1, sizeof(char));
  if (((*maze_image)->img)[0] == NULL) {
    free((*maze_image)->img);
    (*maze_image)->img = NULL;
    return MEM_ERR;
  }

  int pos = 0;
  ((*maze_image)->img)[0][pos++] = '+';
  for (int j = 0; j < cols; j++) {
    ((*maze_image)->img)[0][pos++] = '-';
    ((*maze_image)->img)[0][pos++] = '-';
    ((*maze_image)->img)[0][pos++] = '-';
    ((*maze_image)->img)[0][pos++] = '+';
  }
  ((*maze_image)->img)[0][pos] = '\0';

  for (int i = 0; i < rows; i++) {
    int row_idx = i * 2 + 1;
    ((*maze_image)->img)[row_idx] =
        calloc((*maze_image)->cols + 1, sizeof(char));
    if (((*maze_image)->img)[row_idx] == NULL) {
      for (int k = 0; k < row_idx; k++) {
        free(((*maze_image)->img)[k]);
      }
      free((*maze_image)->img);
      (*maze_image)->img = NULL;
      return MEM_ERR;
    }

    pos = 0;
    ((*maze_image)->img)[row_idx][pos++] = '|';
    for (int j = 0; j < cols; j++) {
      if (maze->path != NULL && maze->path[i][j] == 1) {
        ((*maze_image)->img)[row_idx][pos++] = ' ';
        ((*maze_image)->img)[row_idx][pos++] = '*';
        ((*maze_image)->img)[row_idx][pos++] = ' ';
      } else {
        ((*maze_image)->img)[row_idx][pos++] = ' ';
        ((*maze_image)->img)[row_idx][pos++] = ' ';
        ((*maze_image)->img)[row_idx][pos++] = ' ';
      }

      if (j == cols - 1) {
        ((*maze_image)->img)[row_idx][pos++] = '|';
      } else if (maze->right_walls[i][j]) {
        ((*maze_image)->img)[row_idx][pos++] = '|';
      } else {
        ((*maze_image)->img)[row_idx][pos++] = ' ';
      }
    }
    ((*maze_image)->img)[row_idx][pos] = '\0';

    int bottom_idx = i * 2 + 2;
    ((*maze_image)->img)[bottom_idx] =
        calloc((*maze_image)->cols + 1, sizeof(char));
    if (((*maze_image)->img)[bottom_idx] == NULL) {
      for (int k = 0; k <= row_idx; k++) {
        free(((*maze_image)->img)[k]);
      }
      free((*maze_image)->img);
      (*maze_image)->img = NULL;
      return MEM_ERR;
    }

    pos = 0;
    ((*maze_image)->img)[bottom_idx][pos++] = '+';
    for (int j = 0; j < cols; j++) {
      if (maze->bottom_walls[i][j]) {
        ((*maze_image)->img)[bottom_idx][pos++] = '-';
        ((*maze_image)->img)[bottom_idx][pos++] = '-';
        ((*maze_image)->img)[bottom_idx][pos++] = '-';
      } else {
        ((*maze_image)->img)[bottom_idx][pos++] = ' ';
        ((*maze_image)->img)[bottom_idx][pos++] = ' ';
        ((*maze_image)->img)[bottom_idx][pos++] = ' ';
      }
      ((*maze_image)->img)[bottom_idx][pos++] = '+';
    }
    ((*maze_image)->img)[bottom_idx][pos] = '\0';
  }

  return NO_ERR;
}

ERR_maze destroy_maze_image(maze_image_t *maze_image) {
  if (maze_image == NULL) {
    return MEM_ERR;
  }

  if (maze_image->img != NULL) {
    for (int i = 0; i < maze_image->rows; ++i) {
      free(maze_image->img[i]);
      maze_image->img[i] = NULL;
    }
  } else {
    return MEM_ERR;
  }

  free(maze_image->img);
  maze_image->img = NULL;

  free(maze_image);
  maze_image = NULL;

  return NO_ERR;
}