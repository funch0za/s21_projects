#ifndef CLI_PARAMS
#define CLI_PARAMS

#define WINNER_LEVEL 10

#define WELCOME_H 10
#define WELCOME_W 30
#define WELCOME_X 3
#define WELCOME_Y 3

#define GOODBYE_H 5
#define GOODBYE_W 25
#define GOODBYE_Y 3
#define GOODBYE_X 3

/**
 * @brief Parts of figure. []
 */
#define L_HALF '['
#define R_HALF ']'

/**
 * @brief Window for game map.
 * The window stretches twice as wide as
 * it is necessary to draw figure.
 */
#define GAME_H 22
#define GAME_W 22
#define STRETCH_W 2
#define SHIFT 1
#define GAME_X 0
#define GAME_Y 0

/**
 * @brief Window for score.
 */
#define SCORE_H 5
#define SCORE_W 15
#define SCORE_X (GAME_W + 1)
#define SCORE_Y (GAME_Y)

/**
 * @brief Window for hiscore.
 */
#define HISCORE_H 5
#define HISCORE_W 15
#define HISCORE_X (SCORE_X)
#define HISCORE_Y (SCORE_Y + SCORE_H)

/**
 * @brief Window for level.
 */
#define LEVEL_H 5
#define LEVEL_W 15
#define LEVEL_X (SCORE_X)
#define LEVEL_Y (HISCORE_Y + HISCORE_H)

#endif
