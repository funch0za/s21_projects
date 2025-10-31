#ifndef TETRIS_MACROSES_H
#define TETRIS_MACROSES_H

#include <stdlib.h>

#define FIGURE_SZ 4
#define W_MAP 10
#define H_MAP 20
#define DB_FILENAME "data/hiscore.txt"

#define POINT_CHECK(x, y)                                \
  ((x) < 0 || (y) < 0 || (x) >= H_MAP || (y) >= W_MAP || \
   game_map->points[(x)][(y)] == ON)                     \
      ? NOT_MOVED                                        \
      : MOVED
#define MIN2(a, b) (a) < (b) ? (a) : (b)
#define MIN4(a, b, c, d) MIN2((MIN2(a, b)), (MIN2(c, d)))
#define MAX2(a, b) (a) > (b) ? (a) : (b)
#define MAX4(a, b, c, d) MAX2((MAX2(a, b)), (MAX2(c, d)))

#endif
