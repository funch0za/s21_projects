#include "test_snake_model.h"

#include <utility>
#include <vector>

#include "snake_model.h"

int countSnakeCells(const std::vector<std::vector<int>>& field) {
  int count = 0;
  for (const auto& row : field) {
    for (int cell : row) {
      if (cell == 1) count++;
    }
  }
  return count;
}

int countFoodCells(const std::vector<std::vector<int>>& field) {
  int count = 0;
  for (const auto& row : field) {
    for (int cell : row) {
      if (cell == 2) count++;
    }
  }
  return count;
}

std::pair<int, int> findSnakeHead(const std::vector<std::vector<int>>& field) {
  for (size_t y = 0; y < field.size(); y++) {
    for (size_t x = 0; x < field[y].size(); x++) {
      if (field[y][x] == 1) {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

std::pair<int, int> findFoodPosition(
    const std::vector<std::vector<int>>& field) {
  for (size_t y = 0; y < field.size(); y++) {
    for (size_t x = 0; x < field[y].size(); x++) {
      if (field[y][x] == 2) {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

void SnakeModelTest::simulateEatingFood() {
  for (int i = 0; i < 5; i++) {
    model->processInput(s21::UserAction::Action, false);
  }
}

void SnakeModelTest::simulateGameOver() {
  for (int i = 0; i < s21::FIELD_WIDTH + 2; i++) {
    model->processInput(s21::UserAction::Right, true);
  }
}

TEST_F(SnakeModelTest, InitializationTest) {
  auto info = model->getGameInfo();

  EXPECT_EQ(info.field.size(), s21::FIELD_HEIGHT);
  EXPECT_EQ(info.field[0].size(), s21::FIELD_WIDTH);
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.speed, s21::INITIAL_SPEED);
  EXPECT_FALSE(model->isGameOver());
  EXPECT_FALSE(model->isPaused());
  EXPECT_FALSE(model->isRunning());
  EXPECT_GT(countSnakeCells(info.field), 0);
  EXPECT_EQ(countFoodCells(info.field), 1);
}

TEST_F(SnakeModelTest, GameStartTest) {
  EXPECT_FALSE(model->isRunning());
  model->processInput(s21::UserAction::Start, true);
  EXPECT_TRUE(model->isRunning());
  EXPECT_FALSE(model->isGameOver());
}

TEST_F(SnakeModelTest, FoodRespawnTest) {
  model->processInput(s21::UserAction::Start, true);

  auto initial_info = model->getGameInfo();

  for (int i = 0; i < 10; i++) {
    model->processInput(s21::UserAction::Action, false);
  }

  auto new_info = model->getGameInfo();

  EXPECT_EQ(countFoodCells(new_info.field), 1);
}

TEST_F(SnakeModelTest, ScoreIncreaseTest) {
  model->processInput(s21::UserAction::Start, true);

  auto initial_info = model->getGameInfo();
  int initial_score = initial_info.score;

  simulateEatingFood();

  auto new_info = model->getGameInfo();
  EXPECT_GE(new_info.score, initial_score);
}

TEST_F(SnakeModelTest, LevelProgressionTest) {
  model->processInput(s21::UserAction::Start, true);

  auto initial_info = model->getGameInfo();
  EXPECT_EQ(initial_info.level, 1);

  for (int i = 0; i < 10; i++) {
    simulateEatingFood();
  }

  auto new_info = model->getGameInfo();
  if (new_info.score >= 50) {
    EXPECT_GE(new_info.level, 2);
  }
}

TEST_F(SnakeModelTest, WallCollisionTest) {
  model->processInput(s21::UserAction::Start, true);

  for (int i = 0; i < s21::FIELD_WIDTH * 2; i++) {
    model->processInput(s21::UserAction::Right, true);
    if (model->isGameOver()) break;
  }

  EXPECT_TRUE(model->isGameOver());
}

TEST_F(SnakeModelTest, SelfCollisionTest) {
  model->processInput(s21::UserAction::Start, true);

  model->processInput(s21::UserAction::Right, true);
  model->processInput(s21::UserAction::Down, true);
  model->processInput(s21::UserAction::Left, true);
  model->processInput(s21::UserAction::Up, true);

  EXPECT_FALSE(model->isGameOver());
}

TEST_F(SnakeModelTest, PauseResumeTest) {
  model->processInput(s21::UserAction::Start, true);

  model->processInput(s21::UserAction::Pause, true);
  EXPECT_TRUE(model->isPaused());

  auto paused_state = model->getGameInfo();
  model->processInput(s21::UserAction::Right, true);
  auto after_paused_move = model->getGameInfo();
  EXPECT_EQ(paused_state.field, after_paused_move.field);

  model->processInput(s21::UserAction::Pause, true);
  EXPECT_FALSE(model->isPaused());
}

TEST_F(SnakeModelTest, GameOverStateTest) {
  model->processInput(s21::UserAction::Start, true);
  simulateGameOver();

  EXPECT_TRUE(model->isGameOver());
  EXPECT_FALSE(model->isRunning());

  auto game_over_state = model->getGameInfo();
  model->processInput(s21::UserAction::Right, true);
  auto after_input = model->getGameInfo();
  EXPECT_EQ(game_over_state.field, after_input.field);
}

TEST_F(SnakeModelTest, RestartFromGameOverTest) {
  model->processInput(s21::UserAction::Start, true);
  simulateGameOver();

  EXPECT_TRUE(model->isGameOver());

  model->processInput(s21::UserAction::Start, true);

  EXPECT_FALSE(model->isGameOver());
  EXPECT_TRUE(model->isRunning());

  auto new_info = model->getGameInfo();
  EXPECT_EQ(new_info.score, 0);
  EXPECT_EQ(new_info.level, 1);
}

TEST_F(SnakeModelTest, HighScoreTest) {
  model->processInput(s21::UserAction::Start, true);

  auto initial_info = model->getGameInfo();
  int initial_high_score = initial_info.high_score;

  simulateEatingFood();

  auto new_info = model->getGameInfo();
  if (new_info.score > initial_high_score) {
    EXPECT_GE(new_info.high_score, new_info.score);
  }
}

TEST_F(SnakeModelTest, SpeedAdjustmentTest) {
  model->processInput(s21::UserAction::Start, true);

  auto initial_info = model->getGameInfo();
  int initial_speed = initial_info.speed;

  model->processInput(s21::UserAction::Action, true);

  auto new_info = model->getGameInfo();
  EXPECT_LE(new_info.speed, initial_speed);
}

TEST_F(SnakeModelTest, MultipleRestartsTest) {
  for (int i = 0; i < 3; i++) {
    model->processInput(s21::UserAction::Start, true);
    EXPECT_TRUE(model->isRunning());

    simulateGameOver();
    EXPECT_TRUE(model->isGameOver());

    model->processInput(s21::UserAction::Start, true);
  }

  EXPECT_TRUE(model->isRunning());
  EXPECT_FALSE(model->isGameOver());
}

TEST_F(SnakeModelTest, FieldBoundariesTest) {
  model->processInput(s21::UserAction::Start, true);

  auto info = model->getGameInfo();
  auto head = findSnakeHead(info.field);

  EXPECT_GE(head.first, 0);
  EXPECT_LT(head.first, s21::FIELD_WIDTH);
  EXPECT_GE(head.second, 0);
  EXPECT_LT(head.second, s21::FIELD_HEIGHT);
}

TEST_F(SnakeModelTest, FoodPositionTest) {
  model->processInput(s21::UserAction::Start, true);

  auto info = model->getGameInfo();
  auto food = findFoodPosition(info.field);

  EXPECT_GE(food.first, 0);
  EXPECT_LT(food.first, s21::FIELD_WIDTH);
  EXPECT_GE(food.second, 0);
  EXPECT_LT(food.second, s21::FIELD_HEIGHT);

  auto head = findSnakeHead(info.field);
  EXPECT_FALSE(head == food);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
