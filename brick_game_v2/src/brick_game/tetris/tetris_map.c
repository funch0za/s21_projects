#include "tetris_map.h"

#include <stdbool.h>

/**
 * @brief Delete filled line on the current game map.
 * @param *game_map Pointer of current game map.
 */
int map_delete_filled(map_t *game_map) {
  int count_of_deleted = 0;

  /*
  gap - count of line which need to delete
  last_not_filled - flag that last NOT (line full OF or full ON)
  */
  bool is_on[H_MAP];
  for (int i = H_MAP - 1; i >= 0; --i) {
    is_on[i] = true;

    /* check current line */
    for (int j = 0; j < W_MAP; ++j) {
      if (game_map->points[i][j] == OFF) {
        is_on[i] = false;
      }
    }

    if (is_on[i]) {
      ++count_of_deleted;
    }
  }

  int current_coord = H_MAP - 1;
  for (int i = H_MAP - 1; i >= 0; --i) {
    if (!is_on[i]) {
      is_on[i] = true;
      for (int j = 0; j < W_MAP; ++j) {
        game_map->points[current_coord][j] = game_map->points[i][j];
      }
      --current_coord;
    }
  }

  return count_of_deleted;
}
