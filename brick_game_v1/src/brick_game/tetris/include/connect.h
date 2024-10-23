#ifndef CONNECT_H
#define CONNECT_H

#include <stdbool.h>

#include "backend.h"
#include "fsm.h"

#define WINNER_LEVEL 10
void userInput(UserAction_t action);
GameInfo_t updateCurrentState();

#endif
