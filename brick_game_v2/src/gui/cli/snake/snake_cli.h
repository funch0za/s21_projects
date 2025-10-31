#ifndef SNAKE_CLI
#define SNAKE_CLI

#include <ncurses.h>

#include "../../../brick_game/snake/common/snake_consts.h"
#include "../../../brick_game/snake/common/snake_types.h"

namespace s21 {

class SnakeCLI {
 public:
  SnakeCLI();
  ~SnakeCLI();

  bool initialize();
  void render(const GameInfo &game_info);
  void showGameOver();
  void showPause();
  void cleanup();

 private:
  void drawField(const std::vector<std::vector<int>> &field);
  void drawSidebar(const GameInfo &game_info);
  void drawBorders();
};

}  // namespace s21

#endif
