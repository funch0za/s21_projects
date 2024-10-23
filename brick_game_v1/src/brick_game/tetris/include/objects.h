#ifndef OBJECT_H
#define OBJECT_H

#include "macros.h"

/**
 * @brief Enums for statuses.
 */
typedef enum { ON = 1, OFF = 0 } point_stat;
typedef enum { MOVED, NOT_MOVED } move_stat;
typedef enum { FILLED, NOT_FILLED } map_stat;
typedef enum { ROTATE_V, DOWN_V, RIGHT_V, LEFT_V } vector_t;

/**
  @brief Enums for type of figures.
*/

typedef enum { F0, F1, F2, F3, F4, F5, F6 } type_f;

/**
 * @brief Struct for figure points.
 */
typedef struct {
  struct {
    int x, y;
  } points[FIGURE_SZ];
  type_f type;
  int pos;
} figure_t;

/**
 * @brief Struct for game map.
 */
typedef struct {
  point_stat points[H_MAP][W_MAP];
} map_t;

/**
 * @brief Enum for User actions. This enum need to connect.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Main struct for connect backend and frontend.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Main struct for backend.
 */
typedef struct {
  figure_t current;
  figure_t next;
  int next_num;
  map_t map;

  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  GameInfo_t info;
} TetrisStatus_t;

#endif
