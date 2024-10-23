/*
 * Macroses
 */

#ifndef MACROS_H
#define MACROS_H

#define FIGURE_SZ 4
#define W_MAP 10
#define H_MAP 20
#define DB_FILENAME "data/hiscore.txt"

#define POINT_CHECK(x, y) ((x) < 0 || (y) < 0 || (x) >= H_MAP || (y) >= W_MAP || game_map->points[(x)][(y)] == ON) ? NOT_MOVED : MOVED
#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MIN4(a, b, c, d) MIN((MIN(a, b)), (MIN(c, d)))
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MAX4(a, b, c, d) MAX((MAX(a, b)), (MAX(c, d)))

#endif
