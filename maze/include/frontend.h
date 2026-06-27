#ifndef FRONTED_H
#define FRONTED_H

#include "ERR_maze.h"
#include "maze_image.h"
#include "queue.h"
#include <curses.h>

void init_curses(void);
void stop_curses(void);
void select_maze_source(int *user_choice);
void draw_maze_image(maze_image_t *img);
void welcome_screen(void);
void select_start_and_finish(int *start_i, int *start_j, int *finish_i,
                             int *finish_j);
void select_maze_size(int *rows, int *cols);
void show_error(ERR_maze error);
void get_maze_filename(char *filename, int max_len);

void show_goodbye(void);

#endif
