#include "tetris_game_machine.h"

#include <stdio.h>

#include "tetris_figure.h"
#include "tetris_map.h"
#include "tetris_matrix_operations.h"

/**
 * @file include/fsm.h
 * @brief Function for start game.
 * This function initializes randomizer and tetris.
 * After that runs spawn();
 */
void start_st() {
  TetrisStatus_t *tetris = get_tetris_struct();

  tetris->score = 0;
  tetris->speed = 0;
  tetris->pause = 0;
  tetris->high_score = get_hiscore();
  tetris->level = 1;

  create_matrix(H_MAP, W_MAP, &(tetris->info.field));
  create_matrix(FIGURE_SZ, FIGURE_SZ, &(tetris->info.next));

  tetris->current = FIGURES_MID[RANDOM];
  tetris->next_num = RANDOM;
  tetris->next = FIGURES_LEFT[tetris->next_num];
}

/**
 * @brief Functioin for spwan figure.
 * This function move tetris.next figure in tetris.current figure.
 * After that tetris.next figure get new from randomizer.
 */
bool spawn_st() {
  bool status = true;
  TetrisStatus_t *tetris = get_tetris_struct();
  tetris->current = FIGURES_MID[tetris->next_num];

  for (int i = 0; i < FIGURE_SZ; ++i) {
    if (tetris->map.points[tetris->current.points[i].x]
                          [tetris->current.points[i].y] == ON) {
      status = false;
    }
  }

  if (status == true) {
    tetris->next_num = RANDOM;
    tetris->next = FIGURES_LEFT[tetris->next_num];
  }

  return status;
}

/**
 * @brief Function for shift current figure.
 * @param vector_t LEFT or RIGHT.
 */
void shift_st(vector_t v) {
  TetrisStatus_t *tetris = get_tetris_struct();

  if (!tetris->pause) {
    figure_move(&(tetris->current), v, &(tetris->map));
    if (v == DOWN_V &&
        figure_can_attached(&(tetris->current), &(tetris->map))) {
      attach_st();
    }
  }
}

/**
 * @brief Function for install figure.
 * This function move down figure while figure not can move.
 */
void attach_st() {
  TetrisStatus_t *tetris = get_tetris_struct();
  if (!tetris->pause) {
    figure_attach(&(tetris->current), &(tetris->map));
    update_score_level(map_delete_filled(&(tetris->map)));
    if (!spawn_st()) {
      game_over_st();
    }
  }
}

/**
 * @brief Function for game over state.
 */
void game_over_st() {
  TetrisStatus_t *tetris = get_tetris_struct();
  if (tetris->score > tetris->high_score) {
    update_hiscore(tetris->score);
  }
  delete_tetris();
}

/**
 * @brief Set pause state.
 */
void pause_st() {
  TetrisStatus_t *tetris = get_tetris_struct();
  tetris->pause = !tetris->pause;
}

void update_score_level(int count_of_deleted_lines) {
  TetrisStatus_t *tetris = get_tetris_struct();
  switch (count_of_deleted_lines) {
    case 1:
      tetris->score += 100;
      break;
    case 2:
      tetris->score += 300;
      break;
    case 3:
      tetris->score += 700;
      break;
    case 4:
      tetris->score += 1500;
      break;
    default:
      break;
  }

  tetris->level = tetris->score / 600 + 1;
}

int get_hiscore() {
  FILE *fp = fopen(DB_FILENAME, "r");
  int hiscore = 0;
  if (fp != NULL) {
    fscanf(fp, "%d", &hiscore);
    fclose(fp);
  }
  return hiscore;
}

void update_hiscore(int hiscore) {
  FILE *fp = fopen(DB_FILENAME, "w");
  fprintf(fp, "%d", hiscore);
  fclose(fp);
}
