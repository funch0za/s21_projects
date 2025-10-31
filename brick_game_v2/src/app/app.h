#ifndef APP_H
#define APP_H

#include "../brick_game/snake/controller/snake_controller.h"
#include "../brick_game/tetris/tetris.h"

#if defined(CLI_UI)

#include "../gui/cli/snake/snake_cli.h"
#include "../gui/cli/tetris/tetris_cli.h"

#elif defined(DESKTOP_UI)

#include "../gui/desktop/snake/snake_desktop.h"
#include "../gui/desktop/tetris/tetris_desktop.h"

#else

#include <iostream>

#endif

namespace s21 {

class app {
 public:
  static void menu();
  static void tetris_loop();
  static void snake_loop();
};

}  // namespace s21

#endif
