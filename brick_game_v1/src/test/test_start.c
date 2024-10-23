#include <check.h>

#include "include/test_brick_game_v1.h"

void start() {
  TetrisStatus_t *tetris = get_tetris_struct();

  userInput(Start);
  ck_assert_int_eq(tetris->score, 0);
  ck_assert_int_eq(tetris->speed, 0);
  ck_assert_int_eq(tetris->pause, 0);
  ck_assert_int_eq(tetris->level, 1);
  ck_assert_int_eq(tetris->high_score, get_hiscore());
  ck_assert_ptr_nonnull(tetris->info.field);
  ck_assert_ptr_nonnull(tetris->info.next);

  GameInfo_t gmi = updateCurrentState();

  ck_assert(gmi.score == tetris->score);
  ck_assert(gmi.high_score == tetris->high_score);
  ck_assert(gmi.level == tetris->level);
  ck_assert(gmi.speed == tetris->speed);
  ck_assert(gmi.pause == tetris->pause);
}

void terminate() {
  TetrisStatus_t *tetris = get_tetris_struct();
  tetris->score = 1e9;
  userInput(Terminate);
  ck_assert_ptr_eq(tetris->info.field, NULL);
  ck_assert_ptr_eq(tetris->info.next, NULL);
  ck_assert(game_is_over());
}

START_TEST(test_1) {
  start();
  // SPAWN OK

  TetrisStatus_t *tetris = get_tetris_struct();

  ck_assert(spawn_st());

  for (int i = 0; i < H_MAP; ++i) {
    for (int j = 0; j < W_MAP; ++j) {
      tetris->map.points[i][j] = ON;
    }
  }

  map_delete_filled(&tetris->map);

  // SPAWN FAILED
  ck_assert(!spawn_st());

  // PAUSE
  userInput(Pause);
  ck_assert(tetris->pause);
  userInput(Pause);
  ck_assert(!tetris->pause);
  terminate();
}
END_TEST

START_TEST(test_2) {
  userInput(Start);

  TetrisStatus_t *tetris = get_tetris_struct();

  for (int i = 0; i < 7; ++i) {
    tetris->current = FIGURES_MID[i];
    for (int j = 0; j < 3; ++j) {
      ck_assert(figure_rotate(&tetris->current, &tetris->map) == MOVED);
      userInput(Action);
    }
    for (int j = 0; j < 3; ++j) {
      ck_assert(figure_move(&tetris->current, DOWN_V, &tetris->map) == MOVED);
      userInput(Down);
    }

    ck_assert(figure_move(&tetris->current, LEFT_V, &tetris->map) == MOVED);
    userInput(Left);

    for (int j = 0; j < 3; ++j) {
      userInput(Left);
    }

    ck_assert(figure_move(&tetris->current, LEFT_V, &tetris->map) == NOT_MOVED);

    for (int j = 0; j < 10; ++j) {
      userInput(Right);
    }
    ck_assert(figure_move(&tetris->current, RIGHT_V, &tetris->map) ==
              NOT_MOVED);
  }

  terminate();
}
END_TEST

START_TEST(test_3) {
  start();

  TetrisStatus_t *tetris = get_tetris_struct();
  figure_attach(&tetris->current, &tetris->map);
  for (int i = 0; i < FIGURE_SZ; ++i) {
    ck_assert(tetris->map.points[tetris->current.points[i].x]
                                [tetris->current.points[i].y] == ON);
  }

  // attach_st();

  terminate();
}
END_TEST

START_TEST(test_4) {
  start();
  TetrisStatus_t *tetris = get_tetris_struct();

  update_hiscore(0);

  update_score_level(1);
  ck_assert_int_eq(tetris->score, 100);

  update_score_level(2);
  ck_assert_int_eq(tetris->score, 400);

  update_score_level(3);
  ck_assert_int_eq(tetris->score, 1100);

  update_score_level(4);
  ck_assert_int_eq(tetris->score, 2600);
}
END_TEST

START_TEST(test_5) {
  start();

  TetrisStatus_t *tetris = get_tetris_struct();

  tetris->current = FIGURES_MID[3];

  for (int i = 0; i < 4; ++i) {
    userInput(Down);
  }

  attach_st();

  terminate();
}

Suite *test() {
  Suite *suite = suite_create("test");
  TCase *tc = tcase_create("test_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);

  suite_add_tcase(suite, tc);
  return suite;
}
