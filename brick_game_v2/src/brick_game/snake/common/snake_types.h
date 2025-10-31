#ifndef SNAKE_TYPES_H
#define SNAKE_TYPES_H

#include <vector>

namespace s21 {

enum class UserAction {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
};

struct GameInfo {
  std::vector<std::vector<int>> field;
  std::vector<std::vector<int>> next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
};

}  // namespace s21

#endif
