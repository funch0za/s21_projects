#include "snake_model.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

namespace s21 {

SnakeModel::SnakeModel() {
  std::srand(std::time(nullptr));
  initialize();
}

void SnakeModel::initialize() {
  field_.resize(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH, 0));
  next_.resize(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH, 0));

  snake_.clear();
  direction_ = 1;
  game_over_ = false;
  paused_ = false;
  running_ = false;

  int start_x = FIELD_WIDTH / 2;
  int start_y = FIELD_HEIGHT / 2;
  snake_.push_back({start_x, start_y});
  snake_.push_back({start_x - 1, start_y});
  snake_.push_back({start_x - 2, start_y});
  snake_.push_back({start_x - 3, start_y});

  score_ = 0;

  std::ifstream hiscore_file("hiscore_snake.txt");
  high_score_ = 0;
  if (hiscore_file) {
    hiscore_file >> high_score_;
    hiscore_file.close();
  }
  level_ = 1;
  speed_ = INITIAL_SPEED;

  spawnFood();
  updateField();
}

void SnakeModel::update() { updateField(); }

void SnakeModel::processInput(UserAction action, bool hold) {
  if (hold) {
    switch (action) {
      case UserAction::Start:
        if (!running_ || game_over_) {
          initialize();
          running_ = true;
          paused_ = false;
          game_over_ = false;
        }
        break;

      case UserAction::Pause:
        if (running_ && !game_over_) {
          paused_ = !paused_;
        }
        break;

      case UserAction::Terminate:
        running_ = false;
        game_over_ = true;
        break;

      case UserAction::Left:
        if (running_ && !paused_ && !game_over_ && direction_ != 1) {
          direction_ = 3;
          moveSnake();
        }
        break;

      case UserAction::Right:
        if (running_ && !paused_ && !game_over_ && direction_ != 3) {
          direction_ = 1;
          moveSnake();
        }
        break;

      case UserAction::Up:
        if (running_ && !paused_ && !game_over_ && direction_ != 2) {
          direction_ = 0;
          moveSnake();
        }
        break;

      case UserAction::Down:
        if (running_ && !paused_ && !game_over_ && direction_ != 0) {
          direction_ = 2;
          moveSnake();
        }
        break;

      case UserAction::Action:
        if (running_ && !paused_ && !game_over_) {
          speed_ = std::max(speed_ - 1, 0);
        }
        break;
    }
  } else if (action == UserAction::Action) {
    if (running_ && !paused_ && !game_over_) {
      moveSnake();
    }
  }
}

void SnakeModel::moveSnake() {
  if (snake_.empty()) return;

  auto head = snake_.front();

  switch (direction_) {
    case 0:
      head.second--;
      break;
    case 1:
      head.first++;
      break;
    case 2:
      head.second++;
      break;
    case 3:
      head.first--;
      break;
  }

  if (checkCollision(head.first, head.second)) {
    game_over_ = true;
    running_ = false;
    return;
  }

  snake_.insert(snake_.begin(), head);

  if (head.first == food_.first && head.second == food_.second) {
    increaseScore();
    spawnFood();
  } else {
    if (snake_.size() > 1) {
      snake_.pop_back();
    }
  }

  updateField();
}

void SnakeModel::spawnFood() {
  int x, y;
  bool valid;

  do {
    x = std::rand() % FIELD_WIDTH;
    y = std::rand() % FIELD_HEIGHT;
    valid = true;

    for (const auto &segment : snake_) {
      if (segment.first == x && segment.second == y) {
        valid = false;
        break;
      }
    }
  } while (!valid);

  food_ = {x, y};
}

bool SnakeModel::checkCollision(int x, int y) const {
  if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) {
    return true;
  }

  for (size_t i = 1; i < snake_.size(); i++) {
    if (snake_[i].first == x && snake_[i].second == y) {
      return true;
    }
  }

  return false;
}

void SnakeModel::increaseScore() {
  ++score_;
  updateLevel();
}

void SnakeModel::updateLevel() { level_ = (score_ / 5) + 1; }

void SnakeModel::updateField() {
  for (auto &row : field_) {
    std::fill(row.begin(), row.end(), 0);
  }

  for (const auto &segment : snake_) {
    if (segment.second >= 0 && segment.second < FIELD_HEIGHT &&
        segment.first >= 0 && segment.first < FIELD_WIDTH) {
      field_[segment.second][segment.first] = 1;
    }
  }

  if (food_.second >= 0 && food_.second < FIELD_HEIGHT && food_.first >= 0 &&
      food_.first < FIELD_WIDTH) {
    field_[food_.second][food_.first] = 2;
  }
}

GameInfo SnakeModel::getGameInfo() const {
  return {field_, next_, score_, high_score_, level_, speed_, paused_ ? 1 : 0};
}

bool SnakeModel::isGameOver() const { return game_over_; }

bool SnakeModel::isPaused() const { return paused_; }

bool SnakeModel::isRunning() const { return running_; }

}  // namespace s21
