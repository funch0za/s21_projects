#ifndef MAZE_IMAGE_H
#define MAZE_IMAGE_H

#include "ERR_maze.h"
#include "maze.h"

typedef struct {
  int rows;
  int cols;
  char **img;
} maze_image_t;

ERR_maze create_image_maze(maze_t *maze, maze_image_t **maze_image);
ERR_maze destroy_maze_image(maze_image_t *maze_image);

#endif
