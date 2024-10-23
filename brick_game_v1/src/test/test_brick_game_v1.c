#include "include/test_brick_game_v1.h"

unsigned int run_suite(Suite *suite, char *file_logs) {
  // создаем раней
  SRunner *srunner = srunner_create(suite);

  // результаты записываем в файл
  srunner_set_log(srunner, file_logs);
  srunner_run_all(srunner, CK_ENV);
  // кол-во зафейленых тестов
  int count_failed_tests = srunner_ntests_failed(srunner);

  // освобождаем память которая была определена для ранера
  srunner_free(srunner);

  return count_failed_tests;
}

int main() {
  int cnt_failed = 0;

#if TEST_START
  cnt_failed += run_suite(test(), "test/logs/test.log");
#endif
}
