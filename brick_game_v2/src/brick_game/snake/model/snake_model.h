#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <vector>

#include "../common/snake_consts.h"
#include "../common/snake_types.h"

namespace s21 {

class SnakeModel {
 public:
  SnakeModel();

  void initialize();
  void update();
  void processInput(UserAction action, bool hold);
  void manualMove();
  void moveForward();

  GameInfo getGameInfo() const;
  bool isGameOver() const;
  bool isPaused() const;
  bool isRunning() const;

 private:
  std::vector<std::pair<int, int>> snake_;
  std::pair<int, int> food_;
  int direction_;
  int next_direction_;

  bool game_over_;
  bool paused_;
  bool running_;

  int score_;
  int high_score_;
  int level_;
  int speed_;
  int tick_counter_;

  std::vector<std::vector<int>> field_;
  std::vector<std::vector<int>> next_;

  void spawnFood();
  void moveSnake();
  void updateField();
  bool checkCollision(int x, int y) const;
  void increaseScore();
  void updateLevel();
};

}  // namespace s21

#endif
