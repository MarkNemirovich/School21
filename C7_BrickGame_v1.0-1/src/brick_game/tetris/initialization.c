#include "../../gui/cli/gui.h"
#include "business_logic.h"

/// @brief Initializes the game information.
/// @param game_info A pointer to the game_params structure to be initialized.
/// @return int Returns 0 if the initialization is successful, otherwise returns
/// an error code.
int init_game_info(game_params *game_info) {
  int error = 0;
  error = alloc_game_info(game_info);
  if (!error) {
    init_figure(game_info);
    init_field(game_info);
  }
  return error;
}

/// @brief Initializes the game field and game information.
/// @param game_info A pointer to the game_params structure to be initialized.
void init_field(game_params *game_info) {
  for (int i = 0; i < FIELD_Y_SIZE; i++) {
    for (int j = 0; j < FIELD_X_SIZE; j++) {
      game_info->field[i][j] = EMPTY;
      game_info->next[i][j] = EMPTY;
    }
  }
  game_info->high_score = 0;
  game_info->level = 1;
  game_info->pause = 0;
  game_info->score = 0;
  game_info->speed = 0;
  read_best_score(game_info);
}

/// @brief Initializes the current and next_field game figures and spawns the
/// current dots to the game field.
/// @param game_info A pointer to the game_params structure containing game
/// information and figures.
void init_figure(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      game_info->figure_current->dots[i][j] = EMPTY;
      game_info->figure_next->dots[i][j] = EMPTY;
    }
  }
  create_figure_next(game_info);
  spawn_figure_to_game(game_info);
}

/// @brief Initializes the ncurses settings for the game interface.
void init_ncurses_settings() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);  // Enables the keypad for the standard screen
  noecho();              // Disables echoing of characters entered by the user
  curs_set(FALSE);
  nodelay(stdscr, TRUE);  // Enables non-blocking input for the standard screen
}

/// @brief Initializes the  current state game info with default values.
/// @param current_state A pointer to the current state game info structure.
void init_game_state(saved_params *current_state) {
  for (int i = 0; i < BOTTOM_WALL; i++) {
    for (int j = 0; j < RIGHT_WALL; j++) {
      current_state->field[i][j] = EMPTY;
      current_state->next[i][j] = EMPTY;
    }
  }
  current_state->high_score = 0;
  current_state->level = 1;
  current_state->pause = 0;
  current_state->score = 0;
  current_state->speed = 0;
}

/// @brief Initializes the user action after the menu
/// @param user_action Pointer to the user action variable that will be updated
/// with the latest user action
void init_after_menu(actions *user_action) {
  *user_action = ACTION;
  while (*user_action != TERMINATE && *user_action != START) {
    *user_action = get_user_action();
  }
}