#include "business_logic.h"

/// @brief Updates the current state of the game.
/// @return The current game state.
saved_params update_current_state() {
  saved_params *game_info = get_game_info();
  return *game_info;
}

/// @brief Retrieves the current game state.
/// @return A pointer to the current game state.
saved_params *get_game_info() {
  static saved_params current_state;
  static int is_inited = 0;
  if (!is_inited) {
    alloc_game_states(&current_state);
    init_game_state(&current_state);
    is_inited = 1;
  }
  return &current_state;
}

/// @brief Copies the extended game info to the current game info.
/// @param game_info The extended game info to copy.
void copy_game_info_to_the_current(game_params *game_info) {
  saved_params *current_game_info = get_game_info();
  for (int i = 0; i < BOTTOM_WALL; i++) {
    for (int j = 0; j < RIGHT_WALL; j++) {
      current_game_info->next[i][j] = game_info->next[i][j];
    }
  }
  for (int i = 0; i < FIGURE_SIZE; i++)
    for (int j = 0; j < FIGURE_SIZE; j++)
      current_game_info->field[i][j] = game_info->figure_next->dots[i][j];
  current_game_info->high_score = game_info->high_score;
  current_game_info->level = game_info->level;
  current_game_info->pause = game_info->pause;
  current_game_info->score = game_info->score;
  current_game_info->speed = game_info->speed;
}

/// @brief Retrieves the current automaton state from the current state.
/// @return A pointer to the current automaton state.
automate_states *get_current_state() {
  static automate_states automaton;
  static int is_inited = 0;
  if (is_inited == 0) {
    automaton = BEGGING;
    is_inited = 1;
  }
  return &automaton;
}