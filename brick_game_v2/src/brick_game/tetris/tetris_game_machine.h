#ifndef TETRIS_GAME_MACHINE_H
#define TETRIS_GAME_MACHINE_H

#include <stdbool.h>

#include "tetris.h"
#include "tetris_objects.h"

void start_st();
bool spawn_st();
void rotate_st();
void shift_st(vector_t v);
void attach_st();
void game_over_st();
void pause_st();

/* HELPERS  */

int get_hiscore();
void update_hiscore(int hiscore);
void update_score_level(int count_of_deleted_lines);
#define GAME_IS_OVER (get_tetris_struct()->info.field == NULL)
#define RANDOM (rand() % 7)

#endif
