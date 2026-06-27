#ifndef MAZE_H
#define MAZE_H

#include "ERR_maze.h"

#define MAX_ROWS 50
#define MAX_COLS 50

typedef struct {
  int rows;
  int cols;
  int **right_walls;
  int **bottom_walls;
  int **path;
} maze_t;

ERR_maze allocate_maze(maze_t **maze, int rows, int cols);
ERR_maze destroy_maze(maze_t *maze);

ERR_maze generate_maze(maze_t **maze, int rows, int cols);

ERR_maze read_maze(maze_t **maze, const char *filename);
ERR_maze save_maze_to_file(maze_t *maze, const char *filename);
ERR_maze draw_maze(maze_t *maze);

ERR_maze find_path_in_maze(maze_t *maze, int start_i, int start_j, int finish_i,
                           int finish_j);

#endif