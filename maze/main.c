#include "ERR_maze.h"
#include "frontend.h"
#include "include/frontend.h"
#include "maze.h"
#include "maze_image.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME_SIZE 256

int main(void) {
  init_curses();

  ERR_maze err = NO_ERR;

  maze_t *maze = NULL;
  maze_image_t *maze_img = NULL;
  maze_image_t *maze_img_with_path = NULL;

  int user_choice;
  select_maze_source(&user_choice);
  switch (user_choice) {
  case 1: {
    char filename[FILENAME_SIZE];
    get_maze_filename(filename, sizeof(filename));
    err = read_maze(&maze, filename);
    break;
  }
  case 2: {
    int rows, cols;
    select_maze_size(&rows, &cols);
    err = generate_maze(&maze, rows, cols);
    if (err == NO_ERR) {
      char filename[FILENAME_SIZE];
      get_maze_filename(filename, sizeof(filename));
      save_maze_to_file(maze, filename);
    }
    break;
  }
  default: {
    show_goodbye();

    stop_curses();

    return 0;
  }
  }
  if (err == NO_ERR) {
    err = create_image_maze(maze, &maze_img);
    if (err == NO_ERR) {
      draw_maze_image(maze_img);

      int start_i, start_j, finish_i, finish_j;
      select_start_and_finish(&start_i, &start_j, &finish_i, &finish_j);
      err = find_path_in_maze(maze, start_i - 1, start_j - 1, finish_i - 1,
                              finish_j - 1);
      if (err == NO_ERR) {
        err = create_image_maze(maze, &maze_img_with_path);
        if (err == NO_ERR) {
          draw_maze_image(maze_img_with_path);
          getch();
        }
      }
    }
  }

  if (err != NO_ERR) {
    show_error(err);
    getch();
  }

  show_goodbye();

  destroy_maze(maze);
  destroy_maze_image(maze_img);
  destroy_maze_image(maze_img_with_path);

  stop_curses();
  return 0;
}