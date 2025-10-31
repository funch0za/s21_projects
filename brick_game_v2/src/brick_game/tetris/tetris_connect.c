#include "tetris_connect.h"

#include "tetris_game_machine.h"

/**
 * @file include/connect.h
 * @brief Function that works with user input.
 * @param action from user (enum {})
 * @param hold
 */
void userInput(UserAction_t action) {
  switch (action) {
    case Start:
      start_st();
      break;
    case Pause:
      pause_st();
      break;
    case Terminate:
      game_over_st();
      break;
    case Left:
      shift_st(LEFT_V);
      break;
    case Right:
      shift_st(RIGHT_V);
      break;
    case Action:
      shift_st(ROTATE_V);
      break;
    case Down:
      shift_st(DOWN_V);
      break;
    case Up:
      break;
  }
}

/**
 * @brief Function that return game info struct.
 * The function copy information from TetrisStatus_t, GameInfo is part of
 * TetrisStatus_t. If the game is over, function return struct with NULL field.
 * @return Game info.
 */
GameInfo_t updateCurrentState() {
  TetrisStatus_t *tetris = get_tetris_struct();

  tetris->info.score = tetris->score;
  tetris->info.high_score = tetris->high_score;
  tetris->info.level = tetris->level;
  tetris->info.speed = tetris->speed;
  tetris->info.pause = tetris->pause;

  for (int i = 0; tetris->info.field != NULL && i < H_MAP; ++i) {
    for (int j = 0; j < W_MAP; ++j) {
      tetris->info.field[i][j] = tetris->map.points[i][j];
    }
  }

  for (int i = 0; tetris->info.field != NULL && i < FIGURE_SZ; ++i) {
    if (tetris->current.points[i].x >= 0) {
      tetris->info
          .field[tetris->current.points[i].x][tetris->current.points[i].y] = 1;
    }
  }

  for (int i = 0; tetris->info.next != NULL && i < FIGURE_SZ; ++i) {
    for (int j = 0; j < FIGURE_SZ; ++j) {
      tetris->info.next[i][j] = OFF;
    }
  }

  for (int i = 0; tetris->info.next != NULL && i < FIGURE_SZ; ++i) {
    tetris->info.next[tetris->next.points[i].x][tetris->next.points[i].y] = 1;
  }

  return tetris->info;
}
