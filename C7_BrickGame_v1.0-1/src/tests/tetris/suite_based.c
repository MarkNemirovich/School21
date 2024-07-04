#include "ncurses.h"
#include "tetris_tests.h"

START_TEST(left_doloeb) {
  init_ncurses_settings();
  gameloopForTest();
  endwin();
}
END_TEST

Suite *suite_doloeb(void) {
  Suite *s = suite_create("suite_doloeb");
  TCase *tc = tcase_create("case_doloeb");

  tcase_add_test(tc, left_doloeb);

  suite_add_tcase(s, tc);

  return s;
}