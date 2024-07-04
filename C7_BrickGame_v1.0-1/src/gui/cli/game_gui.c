#include "gui.h"

/// @brief Prints the game interface including the game panel and score panel.
/// @param game_info The structure containing the game information.
void print_game(saved_params game_info) {
  print_game_panel(game_info);
  print_score_panel(game_info);
  refresh();
}

/// @brief Prints the game panel within the game interface.
/// @param game_info The structure containing the game information.
void print_game_panel(saved_params game_info) {
  WINDOW *game_win = newwin(GAME_WALL_Y_END, GAME_WALL_X_END, 0, 0);
  box(game_win, 0, 0);  // Draw a box around the window
  for (int i = 0; i < BOTTOM_WALL; i++) {
    for (int j = 0, GUIj = 1; j < RIGHT_WALL; j++, GUIj += 2) {
      if (game_info.next[i][j] == BRICK) {
        // Print a brick symbol at the specified position
        mvwprintw(game_win, i + 1, GUIj, BRICK_GUI);
      } else {
        mvwprintw(game_win, i + 1, GUIj, EMPTY_GUI);
      }
    }
  }
  wrefresh(game_win);
}

void print_next_figure(saved_params game_info, WINDOW *panel_win) {
  mvwprintw(panel_win, 12, 7, "NEXT FIGURE:");
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0, GUIj = 1; j < FIGURE_SIZE; j++, GUIj += 2) {
      if (game_info.field[i][j] == BRICK) {
        mvwprintw(panel_win, i + 13, GUIj + 7, BRICK_GUI);
      }
    }
  }
}

/// @brief Prints the score panel within the game interface.
/// @param game_info The structure containing the game information.
void print_score_panel(saved_params game_info) {
  WINDOW *panel_win = newwin(GAME_WALL_Y_END, GAME_WALL_X_END + 5,
                             GAME_WALL_Y_START, GAME_WALL_X_END);
  box(panel_win, 0, 0);
  move(1, GAME_WALL_X_END + 1);
  printw("Best Score: %d", game_info.high_score);
  move(4, GAME_WALL_X_END + 1);
  printw("Score: %d", game_info.score);
  move(7, GAME_WALL_X_END + 1);
  printw("Level: %d", game_info.level);
  move(10, GAME_WALL_X_END + 1);
  printw("Speed: %d", game_info.speed);
  print_next_figure(game_info, panel_win);
  wrefresh(panel_win);
}

/// @brief Displays the pause screen with a message and instructions.
void print_pause() {
  WINDOW *pause_win = newwin(5, 35, 8, 7);
  box(pause_win, 0, 0);
  wrefresh(pause_win);
  mvwprintw(pause_win, 1, 15, "PAUSE");
  mvwprintw(pause_win, 3, 6, "PRESS 'ENTER' TO CONTINUE");
  wrefresh(pause_win);
  //  delwin(pause_win);  // Delete the pause screen window
}
