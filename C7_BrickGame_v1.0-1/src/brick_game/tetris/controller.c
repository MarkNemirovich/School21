#include "business_logic.h"

/// @brief Get the user action based on the input key.
/// @return The user action based on the input key.
int get_user_action() {
  int input_key = getch();
  switch (input_key) {
    case KEY_ENTER_REDEFINE:
      return START;
    case KEY_PAUSE:
      return PAUSE;
    case KEY_ESC:
      return TERMINATE;
    case KEY_LEFT:
      return LEFT;
    case KEY_RIGHT:
      return RIGHT;
    case KEY_UP:
      return UP;
    case KEY_DOWN:
      return DOWN;
    case KEY_SPACE:
      return ACTION;
    default:
      return SKIP;
  }
}

/// @brief Processes the movement of the game dots based on user actions.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param user_action Pointer to the actions enum indicating the current user
/// action.
/// @param collision Pointer to an integer that will be set to 1 if a collision
/// is detected, or 0 otherwise.
void user_shift(game_params *game_info, actions *user_action, int *collision) {
  *user_action = get_user_action();
  move_figure(user_action, game_info);
  *collision = is_collision(game_info);
  napms(10);  // short delay
}