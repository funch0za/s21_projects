#include "frontend.h"
#include "maze_image.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

void init_curses(void) {
  initscr();
  start_color();
  cbreak();

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
}

void draw_maze_image(maze_image_t *maze_img) {
  clear();
  for (int i = 0; i < maze_img->rows; i++) {
    for (int j = 0; maze_img->img[i][j] != '\0'; j++) {
      char ch = maze_img->img[i][j];

      if (ch == '+' || ch == '-' || ch == '|') {
        attron(COLOR_PAIR(1));
        printw("%c", ch);
        attroff(COLOR_PAIR(1));
      } else if (ch == ' ') {
        attron(COLOR_PAIR(2));
        printw("%c", ch);
        attroff(COLOR_PAIR(2));
      } else if (ch == '*') {
        attron(COLOR_PAIR(3));
        printw("%c", ch);
        attroff(COLOR_PAIR(3));
      } else {
        printw("%c", ch);
      }
    }
    printw("\n");
  }

  refresh();
}

void welcome_screen(void) {
  clear();

  attron(COLOR_PAIR(1)); // Только цвет, без жирного
  printw("\n\n\n");
  printw("   =========================================\n");
  printw("   |                                       |\n");
  printw("   |    M   M  AAAAA   ZZZZZ   EEEE        |\n");
  printw("   |    MM MM  A   A      Z    E           |\n");
  printw("   |    M M M  AAAAA     Z     EEEE        |\n");
  printw("   |    M   M  A   A    Z      E           |\n");
  printw("   |    M   M  A   A   ZZZZZ   EEEE        |\n");
  printw("   |                                       |\n");
  printw("   =========================================\n");
  attroff(COLOR_PAIR(1));

  refresh();
}

void select_maze_source(int *user_choice) {
  welcome_screen();

  attron(COLOR_PAIR(4)); // Только цвет, без жирного
  printw("\n\n");
  printw("          Shortest Path Pathfinder\n");
  printw("          ------------------------\n");
  printw("\n");
  printw("          [1] Load maze from file\n");
  printw("          [2] Generate random maze\n");
  printw("          ... or press any other key to exit\n");
  printw("\n");
  printw("          Enter your choice: ");
  attroff(COLOR_PAIR(4));

  refresh();
  scanw("%d", user_choice);

  clear();
}

void select_maze_size(int *rows, int *cols) {
  attron(COLOR_PAIR(4));
  printw("\n\n");
  printw("          Select size of MAZE\n");
  printw("          ==============================\n");
  printw("\n");
  printw("          Enter the number of rows and columns: ");
  refresh();
  echo();
  scanw("%d %d", rows, cols);
  noecho();

  attron(COLOR_PAIR(4));
  printw("\n\n");
  printw("          Size of MAZE: (%d X %d)\n", *rows, *cols);
  printw("\n");
  printw("          Press any key to build MAZE!!!");
  attroff(COLOR_PAIR(4));
  refresh();
  getch();

  clear();

  attroff(COLOR_PAIR(4));
}

void select_start_and_finish(int *start_i, int *start_j, int *finish_i,
                             int *finish_j) {
  attron(COLOR_PAIR(4));
  printw("\n\n");
  printw("          Select Start and Finish Points\n");
  printw("          ==============================\n");
  printw("\n");
  printw("          Enter start point (row col): ");
  refresh();
  echo();
  scanw("%d %d", start_i, start_j);
  noecho();

  printw("\n");
  printw("          Enter finish point (row col): ");
  refresh();
  echo();
  scanw("%d %d", finish_i, finish_j);
  noecho();
  attroff(COLOR_PAIR(4));

  attron(COLOR_PAIR(4));
  printw("\n\n");
  printw("          Start: (%d, %d)\n", *start_i, *start_j);
  printw("          Finish: (%d, %d)\n", *finish_i, *finish_j);
  printw("\n");
  printw("          Press any key to build shortest path!!!");
  attroff(COLOR_PAIR(4));
  refresh();
  getch();

  clear();
}

void show_error(ERR_maze error) {
  clear();

  attron(COLOR_PAIR(3));
  printw("\n\n\n");
  printw("          ******************************\n");
  printw("          *     EEEEE  RRRR   RRRR     *\n");
  printw("          *     E      R   R  R   R    *\n");
  printw("          *     EEE    RRRR   RRRR     *\n");
  printw("          *     E      R  R   R  R     *\n");
  printw("          *     EEEEE  R   R  R   R    *\n");
  printw("          ******************************\n");
  printw("\n");

  switch (error) {
  case MEM_ERR:
    printw("          Memory allocation error!\n");
    printw("          Failed to allocate memory for the maze.\n");
    break;
  case FILE_ERR:
    printw("          File error!\n");
    printw("          Invalid file path or file does not exist.\n");
    break;
  case PARAM_ERR:
    printw("          Parameter error!\n");
    printw(
        "          Invalid maze size or incorrect start/finish coordinates.\n");
    break;
  default:
    printw("          Unknown error!\n");
    break;
  }

  printw("\n");
  printw("          Press any key to continue...");
  attroff(COLOR_PAIR(3));

  refresh();
}

void show_goodbye(void) {
  clear();

  attron(COLOR_PAIR(1));
  printw("\n\n\n");
  printw("          ********************************\n");
  printw("          *     GGGG   OOO   OOO   DDD   *\n");
  printw("          *     G      O   O O   O D   D *\n");
  printw("          *     G  GG  O   O O   O D   D *\n");
  printw("          *     G   G  O   O O   O D   D *\n");
  printw("          *     GGGG   OOO   OOO   DDD   *\n");
  printw("          *                              *\n");
  printw("          *     BBBB   Y   Y  EEEEE      *\n");
  printw("          *     B   B   Y Y   E          *\n");
  printw("          *     BBBB     Y    EEE        *\n");
  printw("          *     B   B    Y    E          *\n");
  printw("          *     BBBB     Y    EEEEE      *\n");
  printw("          ********************************\n");
  printw("\n");
  printw("          Press any key to exit...\n");
  attroff(COLOR_PAIR(1));

  refresh();
}

void get_maze_filename(char *filename, int max_len) {
  attron(COLOR_PAIR(4));
  printw("\n\n");
  printw("          Enter maze filename: ");
  refresh();
  echo();
  getnstr(filename, max_len - 1);
  noecho();
  attroff(COLOR_PAIR(4));
  clear();
}

void stop_curses(void) {
  getch();
  clear();
  endwin();
}
