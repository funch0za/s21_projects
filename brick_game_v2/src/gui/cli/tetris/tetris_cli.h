#ifndef TETRIS_CLI_H
#define TETRIS_CLI_H

#ifdef __APPLE__
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "../../../brick_game/tetris/tetris_connect.h"
#include "../../../brick_game/tetris/tetris_objects.h"
#include "../cli_params.h"

/**
 * @brief Window for next figure.
 * The window stretches twice as wide as
 * it is necessary to draw figure.
 */
#define NEXT_H 6
#define NEXT_W 10
#define NEXT_X (SCORE_X)
#define NEXT_Y (LEVEL_Y + LEVEL_H)

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
