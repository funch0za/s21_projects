#include "tetris_input.h"

/**
 * @brief Function for input key and run userInput.
 */
void input_key() {
  int key = getch();

  switch (key) {
    case ERR:
      userInput(Down);
      break;
    case KEY_LEFT:
      userInput(Left);
      break;
    case KEY_RIGHT:
      userInput(Right);
      break;
    case KEY_DOWN:
      userInput(Down);
      break;
    case 'p':
      userInput(Pause);
      break;
    case ' ':
      userInput(Action);
      break;
    case 'q':
      userInput(Terminate);
  }
}
