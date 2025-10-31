#ifndef TETRIS_H
#define TETRIS_H

#include "tetris_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

TetrisStatus_t *get_tetris_struct();

#ifdef __cplusplus
}
#endif

void delete_tetris();

#endif
