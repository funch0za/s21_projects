#include "snake_cli.h"

#include <iostream>

#include "../../../brick_game/snake/common/snake_consts.h"

namespace s21 {

SnakeCLI::SnakeCLI() {}

SnakeCLI::~SnakeCLI() { cleanup(); }

bool SnakeCLI::initialize() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  if (!has_colors()) {
    endwin();
    std::cerr << "Terminal does not support colors!" << std::endl;
    return false;
  }

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);

  return true;
}

void SnakeCLI::render(const GameInfo &game_info) {
  clear();
  drawBorders();
  drawField(game_info.field);
  drawSidebar(game_info);

  if (game_info.pause) {
    showPause();
  }

  refresh();
}

void SnakeCLI::drawField(const std::vector<std::vector<int>> &field) {
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      int cell = field[y][x];
      if (cell == 1) {
        attron(COLOR_PAIR(1));
        mvprintw(y + 1, x * 2 + 2, "[]");
        attroff(COLOR_PAIR(1));
      } else if (cell == 2) {
        attron(COLOR_PAIR(2));
        mvprintw(y + 1, x * 2 + 2, "()");
        attroff(COLOR_PAIR(2));
      }
    }
  }
}

void SnakeCLI::drawSidebar(const GameInfo &game_info) {
  int sidebar_x = FIELD_WIDTH * 2 + 4;

  attron(COLOR_PAIR(3));
  mvprintw(2, sidebar_x, "SCORE: %d", game_info.score);
  mvprintw(3, sidebar_x, "HIGH: %d", game_info.high_score);
  mvprintw(4, sidebar_x, "LEVEL: %d", game_info.level);
  mvprintw(5, sidebar_x, "SPEED: %d", game_info.speed);
  mvprintw(6, sidebar_x, "R - run the game");
  mvprintw(7, sidebar_x, "arrow keys - control");
  mvprintw(8, sidebar_x, "P - pause");
  mvprintw(9, sidebar_x, "Q - exit");
  mvprintw(10, sidebar_x, "SPACE - boost the snake");
  attroff(COLOR_PAIR(3));
}

void SnakeCLI::drawBorders() {
  attron(COLOR_PAIR(4));

  for (int x = 0; x < FIELD_WIDTH + 2; x++) {
    mvprintw(0, x * 2, "##");
    mvprintw(FIELD_HEIGHT + 1, x * 2, "##");
  }

  for (int y = 0; y < FIELD_HEIGHT + 2; y++) {
    mvprintw(y, 0, "#");
    mvprintw(y, (FIELD_WIDTH + 1) * 2, "#");
  }

  attroff(COLOR_PAIR(4));
}

void SnakeCLI::showGameOver() {
  mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "GAME OVER!");
  mvprintw(FIELD_HEIGHT / 2 + 1, FIELD_WIDTH - 8, "Press START to restart");
  refresh();
}

void SnakeCLI::showPause() {
  mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH, "PAUSED");
  refresh();
}

void SnakeCLI::cleanup() {
  clear();
  endwin();
}

}  // namespace s21
