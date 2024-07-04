#include "tetris_tests.h"

int main(void) {
  run_tests();

  return 0;
}

void run_testcase(Suite *testcase, int counter_testcase) {
  if (counter_testcase > 1) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests() {
  int counter_testcase = 1;
  Suite *list_cases[] = {suite_doloeb(), suite_getGameInfo(),
                         suite_updateBestScore(), NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, counter_testcase);
    counter_testcase++;
  }
}

void get_usr_input_test() {
  static int input = 0;
  if (input == 0) {
    ungetch(KEY_ENTER_REDEFINE);
  }
  input++;

  if (input == 1) {
    ungetch(KEY_LEFT);
  } else if (input == 2) {
    ungetch(KEY_LEFT);
  } else if (input == 3) {
    ungetch(KEY_LEFT);
  } else if (input == 4) {
    ungetch(KEY_LEFT);
  } else if (input == 5) {
    ungetch(KEY_LEFT);
  } else if (input == 6) {
    ungetch(KEY_SPACE);
  } else if (input == 7) {
    ungetch(KEY_SPACE);
  } else if (input == 8) {
    ungetch(KEY_SPACE);
  } else if (input == 9) {
    ungetch(KEY_RIGHT);
  } else if (input == 10) {
    ungetch(KEY_RIGHT);
  } else if (input == 11) {
    ungetch(KEY_RIGHT);
  } else if (input == 12) {
    ungetch(KEY_RIGHT);
  } else if (input == 13) {
    ungetch(KEY_RIGHT);
  } else if (input == 14) {
    ungetch(KEY_SPACE);
  } else if (input == 15) {
    ungetch(KEY_RIGHT);
  } else if (input == 16) {
    ungetch(KEY_RIGHT);
  } else if (input == 17) {
    ungetch(KEY_DOWN);
  } else if (input == 18) {
    ungetch(KEY_DOWN);
  } else if (input == 19) {
    ungetch(KEY_DOWN);
  } else if (input == 20) {
    ungetch(KEY_DOWN);
  } else if (input == 21) {
    ungetch(KEY_DOWN);
  } else if (input == 22) {
    ungetch(KEY_DOWN);
  } else if (input == 23) {
    ungetch(KEY_DOWN);
  } else if (input == 24) {
    ungetch(KEY_DOWN);
  } else if (input == 25) {
    ungetch(KEY_DOWN);
  } else if (input == 26) {
    ungetch(KEY_DOWN);
  } else if (input == 27) {
    ungetch(KEY_DOWN);
  } else if (input == 28) {
    ungetch(KEY_DOWN);
  } else if (input == 29) {
    ungetch(KEY_DOWN);
  } else if (input == 30) {
    ungetch(KEY_SPACE);
  } else if (input == 31) {
    ungetch(KEY_PAUSE);
  } else if (input == 32) {
    ungetch(KEY_ENTER_REDEFINE);
    ungetch(KEY_ENTER_REDEFINE);
  } else if (input == 33) {
    ungetch(KEY_DOWN);
  } else if (input == 34) {
    ungetch(KEY_DOWN);
  } else if (input == 35) {
    ungetch(KEY_DOWN);
  } else if (input == 36) {
    ungetch(KEY_DOWN);
  } else if (input == 37) {
    ungetch(KEY_DOWN);
  } else if (input == 38) {
    ungetch(KEY_DOWN);
  } else if (input == 39) {
    ungetch(KEY_DOWN);
  } else if (input == 40) {
    ungetch(KEY_DOWN);
  } else if (input == 41) {
    ungetch(KEY_DOWN);
  } else if (input == 42) {
    ungetch(KEY_DOWN);
  } else if (input == 43) {
    ungetch(KEY_DOWN);
  } else if (input == 44) {
    ungetch(KEY_DOWN);
  } else if (input == 45) {
    ungetch(KEY_ESC);
    ungetch(KEY_ESC);
    ungetch(KEY_ESC);
  } else if (input == 46) {
    ungetch(KEY_ENTER_REDEFINE);
    ungetch(KEY_ENTER_REDEFINE);
    ungetch(KEY_ENTER_REDEFINE);
  } else if (input == 47) {
    ungetch(KEY_ESC);
  }
}

void gameloopForTest() {
  game_params game_info_extnd;

  int error = init_game_info(&game_info_extnd);

  if (!error) {
    automate_states *automaton = get_current_state();
    actions user_action = START;
    int tick_count = 0;
    int collision = 0;
    game_info_extnd.speed = 100;

    frontend();
    ungetch(KEY_ENTER_REDEFINE);
    init_after_menu(&user_action);

    if (user_action == TERMINATE)
      *automaton = END;
    else
      *automaton = SPAWN;
    ungetch(KEY_ENTER_REDEFINE);
    while (*automaton != END) {
      get_usr_input_test();
      run_states_observer(&game_info_extnd, &user_action, &tick_count,
                          &collision);
      frontend();
    }

    clear_terminal_buffer();
    free_game_info(&game_info_extnd);
    free_game_state();
  } else {
    printf("Allocate memory error. Restart the Game.\n");
  }
}