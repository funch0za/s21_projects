#ifndef TETRIS_MAP_H
#define TETRIS_MAP_H

#include "tetris_objects.h"

void map_init(map_t *game_map);
map_stat map_check(map_t *game_map);
void map_move_line(int x, int xnew, map_t *game_map);
int map_delete_filled(map_t *game_map);

#endif
