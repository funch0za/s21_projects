#include "tetris.h"

#include "tetris_matrix_operations.h"
#include "tetris_objects.h"

/**
 * @brief Get tetris structure.
 */
TetrisStatus_t *get_tetris_struct() {
  static TetrisStatus_t tetris;
  return &tetris;
}

/**
 * @brief Delete and clean tetris structure.
 */
void delete_tetris() {
  TetrisStatus_t *tetris = get_tetris_struct();
  delete_matrix(H_MAP, &(tetris->info.field));
  delete_matrix(FIGURE_SZ, &(tetris->info.next));
}
