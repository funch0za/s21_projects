#include <curses.h>
#include <unistd.h>

#include "../brick_game/tetris/include/backend.h"
#include "../brick_game/tetris/include/connect.h"
#include "../gui/cli/include/frontend.h"

int main() {
  srand(time(0));

  init_curses();
  draw_welcome();
  WINDOW *game, *hiscore, *score, *level, *next;
  init_windows(&game, &hiscore, &score, &level, &next);

  userInput(Start);

  GameInfo_t cur_tetris = updateCurrentState();
  update_screen(cur_tetris, &game, &hiscore, &score, &level, &next);

  int cnt_score = 0, cnt_level = 0;
  while (!game_is_over()) {
    cur_tetris = updateCurrentState();
    cnt_score = cur_tetris.score;
    cnt_level = cur_tetris.level;
    update_screen(cur_tetris, &game, &hiscore, &score, &level, &next);
    halfdelay(10 - cur_tetris.level);
    input_key();
  }

  delete_windows(&game, &hiscore, &score, &level, &next);
  draw_goodbye(cnt_score, cnt_level);

  endwin();
}
