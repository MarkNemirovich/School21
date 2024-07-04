#include "../../brick_game/tetris/business_logic.h"
#include "gui.h"
#include "string.h"

/// @brief Frontend function responsible for displaying the game interface based
/// on the current state of the game.
void frontend() {
  automate_states *automaton = get_current_state();
  saved_params api_game_info = update_current_state();
  if (*automaton == BEGGING)
    print_menu();
  else if (api_game_info.pause == 1)
    print_pause();
  else if (*automaton == MOVING || *automaton == SHIFTING ||
           *automaton == COLLIDED)
    print_game(api_game_info);
  else if (*automaton == END)
    print_close_game(api_game_info);
}

/// @brief Display the game menu on the screen.
void print_menu() {
  WINDOW *menu_win = newwin(GAME_WALL_Y_END, GAME_WALL_X_END * 2, 0, 0);
  box(menu_win, 0, 0);
  refresh();
  wrefresh(menu_win);
  move(GAME_WALL_Y_START + 2, GAME_WALL_X_END - 5);
  printw("BRICK_GAME");
  move(GAME_WALL_Y_START + 6, GAME_WALL_X_START + 6);
  printw("Press 'Enter' for start the game");
  move(GAME_WALL_Y_START + 10, GAME_WALL_X_START + 6);
  printw("Use arrows for moving the figures");
  move(GAME_WALL_Y_START + 12, GAME_WALL_X_START + 5);
  printw("Use space for rotating the figures");
  move(GAME_WALL_Y_START + 14, GAME_WALL_X_START + 8);
  printw("Press 'P' for pause the game");
  move(GAME_WALL_Y_START + 18, GAME_WALL_X_START + 7);
  printw("Press 'Esc' for close the game");
  refresh();
  wrefresh(menu_win);
}

/// @brief Prints the given text to the center of the screen at the specified y
/// position.
/// @param text The text to be printed to the center of the screen.
/// @param y_pos The y position at which the text will be printed.
void print_text_to_centr(char *text, int y_pos) {
  int text_length = strlen(text);
  int start_x = (GAME_WALL_Y_END * 2 + 5 - text_length) / 2;
  mvprintw(y_pos, start_x, "%s", text);
}

/// @brief Prints the close game message with the player's score and
/// instructions to close the game.
/// @param game_info The structure containing game information including the
/// player's score.
void print_close_game(saved_params game_info) {
  WINDOW *fail_win = newwin(GAME_WALL_Y_END, GAME_WALL_X_END * 2 + 5, 0, 0);
  box(fail_win, 0, 0);  // Draw a box around the window
  refresh();
  char text[30];
  sprintf(text, "Your score %d", game_info.score);
  print_text_to_centr(text, 10);
  print_text_to_centr("Press 'Enter' key for close the game", 15);
  wrefresh(fail_win);
  refresh();
}