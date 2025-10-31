#ifndef SNAKE_DESKTOP_H
#define SNAKE_DESKTOP_H

#include <gtk/gtk.h>

#include "../../../brick_game/snake/common/snake_consts.h"
#include "../../../brick_game/snake/common/snake_types.h"

#define _USE_MATH_DEFINES

namespace s21 {

class SnakeDesktop {
 public:
  SnakeDesktop();
  ~SnakeDesktop();

  bool initialize(int argc, char **argv);
  void render(const GameInfo &game_info);
  void showGameOver();
  void showPause();
  void cleanup();

  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *sidebar_box;

  bool game_over;

 private:
  void drawField(const std::vector<std::vector<int>> &field, cairo_t *cr);
  void drawSidebar(const GameInfo &game_info);
  void drawBorders(cairo_t *cr);

  GameInfo current_game_info;
  bool paused;
};

extern SnakeDesktop *game_view_instance;

}  // namespace s21

#endif
