#include "include/backend.h"

#include <stdbool.h>
#include <stdio.h>

#include "include/macros.h"
#include "include/objects.h"

/**
 * @file include/backend.h
 * @brief Get random number for element from array with figures.
 * @return Random number.
 */
int randomizer() { return rand() % 7; }

/**
 * @brief Create matrix
 * @param rows Rows of 2x array.
 * @param cols Columns of 2x array.
 * @param ***m Pointer of 2x array.
 */
void create_matrix(int rows, int cols, int ***dest) {
  *dest = calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; ++i) {
    (*dest)[i] = calloc(cols, sizeof(int));
  }
}

/**
 * @brief Delete matrx
 * @param rows Rows of 2x array.
 * @param cols Columns of 2x array.
 * @param ***m Pointer of 2x array.
 */
void delete_matrix(int rows, int ***dest) {
  for (int i = 0; i < rows; ++i) {
    free((*dest)[i]);
  }
  free(*dest);
  *dest = NULL;
}

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

/**
 * @brief Function for move the figure.
 * If ROTATE vector is set, the rotation function is run.
 * Otherwise, the figure moves across the field to the RIGHT, LEFT or DOWN.
 * NOT_MOVED can be returned from the function in the case of an error in the
 * parameters or in the case it is impossible to move the figure.
 * @param *f Pointer of current figure.
 * @param v Vector: LEFT, RIGHT, DOWN or ROTATE.
 * @param *game_map Pointer of current game map.
 * @return Status of moving: MOVED or NOT_MOVED.
 */
move_stat figure_move(figure_t *f, vector_t v, map_t *game_map) {
  move_stat result = MOVED;

  if (f == NULL) {
    result = NOT_MOVED;
  }

  if (v == ROTATE_V) {
    result = figure_rotate(f, game_map);
  } else {
    for (int i = 0; result == MOVED && i < FIGURE_SZ; ++i) {
      switch (v) {
        case DOWN_V:
          result = POINT_CHECK(f->points[i].x + 1, f->points[i].y);
          break;
        case RIGHT_V:
          result = POINT_CHECK(f->points[i].x, f->points[i].y + 1);
          break;
        case LEFT_V:
          result = POINT_CHECK(f->points[i].x, f->points[i].y - 1);
          break;
        default:
          result = NOT_MOVED;
          break;
      }
    }

    for (int i = 0; result == MOVED && i < FIGURE_SZ; ++i) {
      switch (v) {
        case DOWN_V:
          f->points[i].x++;
          break;
        case RIGHT_V:
          f->points[i].y++;
          break;
        case LEFT_V:
          f->points[i].y--;
          break;
        default:
          result = NOT_MOVED;
          break;
      }
    }
  }

  return result;
}

/**
 * @brief Function for rotate the figure.
 * This function run from figure_move(...) function.
 * @param *f Pointer of current figure.
 * @param *game_map Point of current game map.
 * @return The same as in the figure_move(...) function.
 */
move_stat figure_rotate(figure_t *f, map_t *game_map) {
  move_stat result = MOVED;

  int up = MIN4(f->points[0].x, f->points[1].x, f->points[2].x, f->points[3].x);
  int left =
      MIN4(f->points[0].y, f->points[1].y, f->points[2].y, f->points[3].y);

  figure_t nf;
  switch (f->type) {
    case F0:
      for (int i = 0; i < FIGURE_SZ; ++i) {
        if (f->pos % 2 == 0) {
          nf.points[i].x = up + i;
          nf.points[i].y = left;
        } else {
          nf.points[i].x = up;
          nf.points[i].y = left + i;
        }
      }
      break;
    case F1:
      if (f->pos == 0) {
        nf.points[0].x = up;
        nf.points[0].y = left + 1;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left;
        }
      } else if (f->pos == 1) {
        nf.points[0].x = up + 1;
        nf.points[0].y = left + 2;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up;
          nf.points[i].y = left + i - 1;
        }
      } else if (f->pos == 2) {
        nf.points[0].x = up + 2;
        nf.points[0].y = left;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left + 1;
        }
      } else {
        nf.points[0].x = up;
        nf.points[0].y = left;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + 1;
          nf.points[i].y = left + i - 1;
        }
      }
      break;
    case F2:
      if (f->pos == 0) {
        nf.points[0].x = up + 2;
        nf.points[0].y = left + 1;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left;
        }
      } else if (f->pos == 1) {
        nf.points[0].x = up + 1;
        nf.points[0].y = left;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up;
          nf.points[i].y = left + i - 1;
        }
      } else if (f->pos == 2) {
        nf.points[0].x = up;
        nf.points[0].y = left;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left + 1;
        }
      } else {
        nf.points[0].x = up;
        nf.points[0].y = left + 2;
        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + 1;
          nf.points[i].y = left + i - 1;
        }
      }
      break;
    case F3:
      for (int i = 0; i < FIGURE_SZ; ++i) {
        nf.points[i] = f->points[i];
      }
      break;
    case F4:
      if (f->pos % 2 == 0) {
        nf.points[0].x = up;
        nf.points[0].y = left;

        nf.points[1].x = up + 1;
        nf.points[1].y = left;

        nf.points[2].x = up + 1;
        nf.points[2].y = left + 1;

        nf.points[3].x = up + 2;
        nf.points[3].y = left + 1;
      } else {
        nf.points[0].x = up;
        nf.points[0].y = left + 1;

        nf.points[1].x = up;
        nf.points[1].y = left + 2;

        nf.points[2].x = up + 1;
        nf.points[2].y = left;

        nf.points[3].x = up + 1;
        nf.points[3].y = left + 1;
      }
      break;
    case F5:
      if (f->pos % 2 == 0) {
        nf.points[0].x = up;
        nf.points[0].y = left + 1;

        nf.points[1].x = up + 1;
        nf.points[1].y = left + 1;

        nf.points[2].x = up + 1;
        nf.points[2].y = left;

        nf.points[3].x = up + 2;
        nf.points[3].y = left;
      } else {
        nf.points[0].x = up;
        nf.points[0].y = left;

        nf.points[1].x = up;
        nf.points[1].y = left + 1;

        nf.points[2].x = up + 1;
        nf.points[2].y = left + 1;

        nf.points[3].x = up + 1;
        nf.points[3].y = left + 2;
      }
      break;
    case F6:
      if (f->pos == 0) {
        nf.points[0].x = up + 1;
        nf.points[0].y = left + 1;

        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left;
        }
      } else if (f->pos == 1) {
        nf.points[0].x = up + 1;
        nf.points[0].y = left + 1;

        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up;
          nf.points[i].y = left + i - 1;
        }
      } else if (f->pos == 2) {
        nf.points[0].x = up + 1;
        nf.points[0].y = left;

        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + i - 1;
          nf.points[i].y = left + 1;
        }
      } else {
        nf.points[0].x = up;
        nf.points[0].y = left + 1;

        for (int i = 1; i < FIGURE_SZ; ++i) {
          nf.points[i].x = up + 1;
          nf.points[i].y = left + i - 1;
        }
      }
      break;
  }

  for (int i = 0; result == MOVED && i < FIGURE_SZ; ++i) {
    result = POINT_CHECK(nf.points[i].x, nf.points[i].y);
  }

  if (result == MOVED) {
    f->pos = (f->pos + 1) % 4;
    for (int i = 0; i < FIGURE_SZ; ++i) {
      f->points[i] = nf.points[i];
    }
  }

  return result;
}

/**
 * @brief Attach the figure on the current game map.
 * @param *f Pointer of current figure.
 * @param *game_map Pointer of current game_map.
 */
void figure_attach(figure_t *f, map_t *game_map) {
  if (f == NULL) {
    return;
  }
  for (int i = 0; i < FIGURE_SZ; ++i) {
    game_map->points[f->points[i].x][f->points[i].y] = ON;
  }
}

/**
 * @brief Check that current figure can attached on game map.
 * @param figure_t *f
 * @param map_t *game_map
 */
bool figure_can_attached(figure_t *f, map_t *game_map) {
  bool result = false;
  for (int i = 0; i < FIGURE_SZ; ++i) {
    if (POINT_CHECK(f->points[i].x + 1, f->points[i].y) == NOT_MOVED) {
      result = true;
    }
  }
  return result;
}

#if 0
/**
 * @brief Init game map.
 * @param *game_map Point of current game map.
 */
void map_init(map_t *game_map) {
  for (int i = 0; i < H_MAP; ++i) {
    for (int j = 0; j < W_MAP; ++j) {
      game_map->points[i][j] = OFF;
    }
  }
}
#endif

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

/**
 * @brief Checking that the game is over.
 */
bool game_is_over() { return get_tetris_struct()->info.field == NULL; }

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
  int hiscore;
  fscanf(fp, "%d", &hiscore);
  fclose(fp);
  return hiscore;
}

void update_hiscore(int hiscore) {
  FILE *fp = fopen(DB_FILENAME, "w");
  fprintf(fp, "%d", hiscore);
  fclose(fp);
}
