#include "tetris_tests.h"

START_TEST(test_based) {
  game_params *game_info = malloc(sizeof(game_params));

  int error = init_game_info(game_info);
  ck_assert_int_eq(error, 0);

  update_current_state(game_info);

  free_game_info(game_info);
  free_game_state();
}
END_TEST

Suite *suite_getGameInfo(void) {
  Suite *s = suite_create("suite_moves");
  TCase *tc = tcase_create("case_moves");

  tcase_add_test(tc, test_based);

  suite_add_tcase(s, tc);

  return s;
}