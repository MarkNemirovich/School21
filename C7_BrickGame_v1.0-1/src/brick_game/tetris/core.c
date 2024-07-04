#include "../../gui/cli/gui.h"
#include "business_logic.h"
#include "string.h"

/// @brief Main game loop that controls the flow of the game.
void run_game() {
  game_params game_information;
  int error = init_game_info(&game_information);
  if (!error) {
    automate_states *state = get_current_state();
    actions user_action = START;
    int tick_count = 0;
    int collision = 0;
    game_information.speed = 100;
    frontend();
    init_after_menu(&user_action);
    if (user_action == TERMINATE)
      *state = END;
    else
      *state = SPAWN;

    while (*state != END) {
      run_states_observer(&game_information, &user_action, &tick_count,
                          &collision);
      frontend();
    }
    clear_terminal_buffer();
    free_game_info(&game_information);
    free_game_state();
  }
}

/// @brief Main game loop that controls the flow of the game.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param user_action Pointer to the actions enum indicating the current user
/// action.
/// @param tick_count Pointer to an integer tracking the number of ticks since
/// the last action.
/// @param collision Pointer to an integer indicating whether a collision has
/// occurred. 1 or 0.
void run_states_observer(game_params *game_info, actions *user_action,
                         int *tick_count, int *collision) {
  automate_states *state = get_current_state();
  if (*state == SPAWN) {
    spawn_figure_to_game(game_info);
    *collision = 0;
    *state = MOVING;
  } else if (game_info->pause) {
    clear_terminal_buffer();
    game_info->pause = 0;
    *user_action = START;
  } else if (*state == MOVING) {
    if (turn_tick(game_info, tick_count)) {
      *state = SHIFTING;
    } else {
      if (*user_action == PAUSE) {
        game_info->pause = 1;
      } else {
        user_shift(game_info, user_action, collision);
      }
      if (*collision)
        *state = COLLIDED;
      else if (*user_action == TERMINATE)
        *state = END;
    }
  } else if (*state == COLLIDED) {
    score_update(game_info);
    copy_next_field_to_current(game_info, BOTTOM_WALL, RIGHT_WALL);
    *state = ATTACHING;
  } else if (*state == ATTACHING) {
    if (can_spawn_figure(game_info))
      *state = SPAWN;
    else
      *state = END;
  } else if (*state == SHIFTING) {
    *state = MOVING;
  } else if (*state == BEGGING) {
    *state = SPAWN;
  }
  copy_game_info_to_the_current(game_info);
}

/// @brief Determines if a game tick should be skipped based on the game's speed
/// setting.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param tick_count Pointer to an integer tracking the number of ticks since
/// the last action. This value is reset to 0 if the tick is skipped, or
/// incremented otherwise.
/// @return int Returns 1 if the tick is skipped, or 0 otherwise.
int turn_tick(game_params *game_info, int *tick_count) {
  int is_skipped = 0;
  if (*tick_count >= game_info->speed) {
    *tick_count = 0;
    move_pos_figure_down(game_info);
    add_next_pos_figure_to_game(game_info);
    is_skipped = 1;
  }
  *tick_count += 1;
  return is_skipped;
}

/// @brief Clears the terminal input buffer.
void clear_terminal_buffer() {
  char off_pause;
  while ((off_pause = getch()) != KEY_ENTER_REDEFINE) {
    ;
  }
}

/// @brief Checks and counts the number of full rows in the game field.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @return int The number of full rows found and removed from the game field.
int check_full_rows(game_params *game_info) {
  int count_fill_rows = 0;
  for (int i = BOTTOM_WALL - 1; i >= 0 && count_fill_rows < 4; i--) {
    int is_row_full = 1;
    for (int j = RIGHT_WALL - 1; j >= 0 && is_row_full; j--) {
      if (game_info->next[i][j] == EMPTY) {
        is_row_full = 0;
      }
    }
    if (is_row_full) {
      remove_full_line(game_info, i);
      count_fill_rows++;
      i++;
    }
  }
  return count_fill_rows;
}

/// @brief Removes a full line from the game field by shifting all rows above it
/// down.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param tick_count Pointer to an integer tracking the number of ticks since
/// the last action. This value is reset to 0 if the tick is skipped, or
/// incremented otherwise.
/// @param start_row The row index of the first row of the full line to be
/// removed.
void remove_full_line(game_params *game_info, int start_row) {
  for (int i = start_row; i > 0; i--) {
    for (int j = 0; j < RIGHT_WALL; j++) {
      game_info->next[i][j] = game_info->next[i - 1][j];
    }
  }
  for (int j = 0; j < RIGHT_WALL; j++) {
    game_info->next[0][j] = EMPTY;
  }
}

/// @brief Copies the contents of the next_field game field to the current game
/// field.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param rows rows The number of rows in the game field.
/// @param cols The number of columns in the game field.
void copy_next_field_to_current(game_params *game_info, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      game_info->field[i][j] = game_info->next[i][j];
    }
  }
}