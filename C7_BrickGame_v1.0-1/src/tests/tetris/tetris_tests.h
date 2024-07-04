#ifndef SRC_TESTS_TETRIS
#define SRC_TESTS_TETRIS

#include <check.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../brick_game/tetris/business_logic.h"
#include "../../gui/cli/gui.h"

#endif  // SRC_TESTS_TETRIS

Suite *suite_getGameInfo(void);
Suite *suite_doloeb(void);
Suite *suite_updateBestScore(void);

void run_tests(void);
void run_testcase(Suite *testcase, int counter_testcase);

void get_usr_input_test();

void gameloopForTest();