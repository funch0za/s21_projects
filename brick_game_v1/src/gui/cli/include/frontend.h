#ifndef FRONTED_H
#define FRONTED_H

#include <curses.h>
#include <stdio.h>

#include "../../../brick_game/tetris/include/connect.h"
#include "../../../brick_game/tetris/include/objects.h"

#define WELCOME_H 10
#define WELCOME_W 30
#define WELCOME_X 3
#define WELCOME_Y 3

/**
 * @brief Parts of figure. []
 */
#define L_HALF '['
#define R_HALF ']'

/**
 * @brief Window for game map.
 * The window stretches twice as wide as
 * it is necessary to draw figure.
 */
#define GAME_H 22
#define GAME_W 22
#define STRETCH_W 2
#define SHIFT 1
#define GAME_X 0
#define GAME_Y 0

/**
 * @brief Window for score.
 */
#define SCORE_H 3
#define SCORE_W 10
#define SCORE_X (GAME_W + 1)
#define SCORE_Y (GAME_Y)

/**
 * @brief Window for hiscore.
 */
#define HISCORE_H 3
#define HISCORE_W 10
#define HISCORE_X (SCORE_X)
#define HISCORE_Y (SCORE_Y + SCORE_H)

/**
 * @brief Window for level.
 */
#define LEVEL_H 3
#define LEVEL_W 10
#define LEVEL_X (SCORE_X)
#define LEVEL_Y (HISCORE_Y + HISCORE_H)

/**
 * @brief Window for next figure.
 * The window stretches twice as wide as
 * it is necessary to draw figure.
 */
#define NEXT_H 6
#define NEXT_W 10
#define NEXT_X (SCORE_X)
#define NEXT_Y (LEVEL_Y + LEVEL_H)

void draw_welcome();
void init_curses();
void init_windows(WINDOW **game, WINDOW **hiscore, WINDOW **score,
                  WINDOW **level, WINDOW **next);
void del_clear_win(WINDOW **win);
void draw_cell(int x, int y, WINDOW **win, char left, char right);
void draw_map(int **map, int h, int w, WINDOW **win);
void input_key();
void delete_windows(WINDOW **game, WINDOW **hiscore, WINDOW **score,
                  WINDOW **level, WINDOW **next);
void draw_goodbye(int score, int level);
void draw_info(WINDOW **hiscore, WINDOW **score, WINDOW **level, int h, int s,
               int l);
void update_screen(GameInfo_t cur_tetris, WINDOW **game, WINDOW **hiscore,
                   WINDOW **score, WINDOW **level, WINDOW **next);

#endif
