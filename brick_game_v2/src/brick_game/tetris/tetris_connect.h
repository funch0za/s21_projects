#ifndef CONNECT_H
#define CONNECT_H

#include <stdbool.h>

#include "tetris.h"
#include "tetris_game_machine.h"

#define WINNER_LEVEL 10

#ifdef __cplusplus
extern "C" {
#endif

void userInput(UserAction_t action);
GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif
