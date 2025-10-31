#ifndef TEST_SNAKE_MODEL_H
#define TEST_SNAKE_MODEL_H

#include <gtest/gtest.h>

#include <vector>

#include "snake_model.h"

int countSnakeCells(const std::vector<std::vector<int>>& field);
int countFoodCells(const std::vector<std::vector<int>>& field);
std::pair<int, int> findSnakeHead(const std::vector<std::vector<int>>& field);
std::pair<int, int> findFoodPosition(
    const std::vector<std::vector<int>>& field);

class SnakeModelTest : public ::testing::Test {
 protected:
  void SetUp() override { model = new s21::SnakeModel(); }

  void TearDown() override { delete model; }

  void simulateEatingFood();
  void simulateGameOver();

  s21::SnakeModel* model;
};

#endif
