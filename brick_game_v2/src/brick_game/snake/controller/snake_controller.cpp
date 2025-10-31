#include "snake_controller.h"

namespace s21 {

SnakeController::SnakeController() { initializeGame(); }

void SnakeController::userInput(UserAction action, bool hold) {
  model_.processInput(action, hold);
}

GameInfo SnakeController::updateCurrentState() {
  model_.update();
  return model_.getGameInfo();
}

void SnakeController::initializeGame() { model_.initialize(); }

void SnakeController::cleanup() {}

}  // namespace s21
