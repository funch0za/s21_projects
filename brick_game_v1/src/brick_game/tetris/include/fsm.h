/*
 * FSM model
 */

#ifndef FSM_H
#define FSM_H

#include "backend.h"
#include "objects.h"

void start_st();
bool spawn_st();
void rotate_st();
void shift_st(vector_t v);
void attach_st();
void game_over_st();
void pause_st();

#endif
