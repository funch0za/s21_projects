#include "include/frontend.h"

#include <curses.h>

/**
 * @file include/frontend.h"
 * @brief The function that initializes ncurses.
 */
void init_curses() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  refresh();
}

/**
 * @brief Draw start screen.
 */
void draw_welcome() {
  WINDOW *welcome = newwin(WELCOME_H, WELCOME_W, WELCOME_Y, WELCOME_X);

  wprintw(welcome,
          "\n \tTETRIS\n \tSPACE - rotation\n "
          "\tP - pause\n \t> to right\n \t< to left\n \tv down\n\n  Press any "
          "key to start...");

  box(welcome, 0, 0);
  wrefresh(welcome);

  getch();

  wclear(welcome);
  wrefresh(welcome);
  delwin(welcome);
}

/**
 * @brief The function that initializes all windows.
 * This function give pointers for all windows.
 * @param WINDOW **game - window that image  game map
 * @param WINDOW **hiscore - window that image number of hiscore
 * @param WINDOW **score - window that image number of score
 * @param WINDOW **level - window that image number of level
 * @param WINDOW **next - window that image next figure
 */
void init_windows(WINDOW **game, WINDOW **hiscore, WINDOW **score,
                  WINDOW **level, WINDOW **next) {
  *game = newwin(GAME_H, GAME_W, GAME_Y, GAME_X);
  *score = newwin(SCORE_H, SCORE_W, SCORE_Y, SCORE_X);
  *hiscore = newwin(HISCORE_H, HISCORE_W, HISCORE_Y, HISCORE_X);
  *level = newwin(LEVEL_H, LEVEL_W, LEVEL_Y, LEVEL_X);
  *next = newwin(NEXT_H, NEXT_W, NEXT_Y, NEXT_X);

  box(*game, 0, 0);
  box(*score, 0, 0);
  box(*hiscore, 0, 0);
  box(*level, 0, 0);
  box(*next, 0, 0);

  wprintw(*score, "SCORE");
  wprintw(*hiscore, "HIGH SCORE");
  wprintw(*level, "LEVEL");
  wprintw(*next, "NEXT");

  wrefresh(*game);
  wrefresh(*score);
  wrefresh(*hiscore);
  wrefresh(*level);
  wrefresh(*next);
}

/**
 * @brief Draw one cell for map.
 * The function also takes into account that the window
 * is stretched and that one cell has two symbols.
 * @param int x - x coord.
 * @param int y - y coord.
 * @param WINDOW **win - pointer for current window with game map.
 * @param char left - left part of cell.
 * @param char right - right part of cell.
 */
void draw_cell(int x, int y, WINDOW **win, char left, char right) {
  mvwaddch(*win, x + SHIFT, y * STRETCH_W + SHIFT, left | A_BOLD);
  mvwaddch(*win, x + SHIFT, y * STRETCH_W + SHIFT + 1, right | A_BOLD);
}

/**
 * @brief Function for draw game map or next figure.
 * @param int **map - matrix.
 * @param int h - number of rows.
 * @param int w - number of cols.
 * @param WINDOW **win - pointer for current window.
 */
void draw_map(int **map, int h, int w, WINDOW **win) {
  for (int x = 0; x < h; ++x) {
    for (int y = 0; y < w; ++y) {
      if (map[x][y] == 1) {
        draw_cell(x, y, win, L_HALF, R_HALF);
      } else {
        draw_cell(x, y, win, ' ', ' ');
      }
    }
  }

  wrefresh(*win);
}

void del_clear_win(WINDOW **win) {
  wclear(*win);
  wrefresh(*win);
  delwin(*win);
}

/**
 * @param WINDOW **win - pointer for current window with game map.
 * @param WINDOW **hiscore - pointer for window that image number of hiscore.
 * @param WINDOW **score - pointer for window that image number of score.
 * @param WINDOW **level - pointer for window that image number of level.
 */
void delete_windows(WINDOW **game, WINDOW **hiscore, WINDOW **score,
                    WINDOW **level, WINDOW **next) {
  del_clear_win(game);
  del_clear_win(hiscore);
  del_clear_win(score);
  del_clear_win(level);
  del_clear_win(next);
}

/**
 * @brief Function for draw game over screen.
 */
void draw_goodbye(int score, int level) {
  WINDOW *goodbye = newwin(7, 25, 3, 3);

  if (level == WINNER_LEVEL) {
    wprintw(goodbye, "\n YOU WIN !!!\n CONGRATULATIONS !!!\n");
  } else {
    wprintw(goodbye, "\n GAME OVER\n");
  }
  wprintw(goodbye, " SCORE: %d\n LEVEL: %d\n Press Q to close...", score,
          level);

  box(goodbye, 0, 0);

  wrefresh(goodbye);
  while (getch() != 'q') {
  }

  del_clear_win(&goodbye);
}

/**
 * @brief Funciton for draw window for hiscore, score and level.
 * @param WINDOW **hiscore - window that image number of hiscore.
 * @param WINDOW **score - window that image number of score.
 * @param WINDOW **level - window that image number of level.
 * @param int h - number of hiscore.
 * @param int s - number of score.
 * @param int l - number of level.
 */
void draw_info(WINDOW **hiscore, WINDOW **score, WINDOW **level, int h, int s,
               int l) {
  mvwprintw(*hiscore, 1, 1, "%d", h);
  mvwprintw(*score, 1, 1, "%d", s);
  mvwprintw(*level, 1, 1, "%d", l);

  wrefresh(*score);
  wrefresh(*hiscore);
  wrefresh(*level);
}

/**
 * @brief Function for draw all windows.
 * This function run draw_map for game and next maps and run draw info.
 */
void update_screen(GameInfo_t cur_tetris, WINDOW **game, WINDOW **hiscore,
                   WINDOW **score, WINDOW **level, WINDOW **next) {
  draw_map(cur_tetris.field, H_MAP, W_MAP, game);
  draw_map(cur_tetris.next, FIGURE_SZ, FIGURE_SZ, next);
  draw_info(hiscore, score, level, cur_tetris.high_score, cur_tetris.score,
            cur_tetris.level);
}

/**
 * @brief Function for input key and run userInput.
 */
void input_key() {
  int key = getch();

  switch (key) {
    case ERR:
      userInput(Down);
      break;
    case KEY_LEFT:
      userInput(Left);
      break;
    case KEY_RIGHT:
      userInput(Right);
      break;
    case KEY_DOWN:
      userInput(Down);
      break;
    case 'p':
      userInput(Pause);
      break;
    case ' ':
      userInput(Action);
      break;
    case 'q':
      userInput(Terminate);
  }
}
