#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "../common/snake_types.h"
#include "../model/snake_model.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController();

  void userInput(UserAction action, bool hold);
  GameInfo updateCurrentState();

  void initializeGame();
  void cleanup();

 private:
  SnakeModel model_;
};

}  // namespace s21

#endif
