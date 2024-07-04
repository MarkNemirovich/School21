#include "business_logic.h"

/// @brief Sets the dots for a horizontal line in the next_field dots container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_horizontal(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    game_info->figure_next->dots[i][1] = BRICK;
  }
}

/// @brief Sets the dots for a vertical line in the next_field dots container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_vertical(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    game_info->figure_next->dots[1][i] = BRICK;
  }
}

/// @brief Sets the dots for a square in the next_field dots container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_box(game_params *game_info) {
  for (int i = 1; i < FIGURE_SIZE / 2 + 1; i++) {
    for (int j = 1; j < FIGURE_SIZE / 2 + 1; j++) {
      game_info->figure_next->dots[i][j] = BRICK;
    }
  }
}

/// @brief Sets the dots for a left angle shape in the next_field dots
/// container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_left_angle(game_params *game_info) {
  game_info->figure_next->dots[1][1] = BRICK;
  for (int i = 1; i < FIGURE_SIZE; i++) {
    game_info->figure_next->dots[2][i] = BRICK;
  }
}

/// @brief Sets the dots for a triangle shape in the next_field dots container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_triangle(game_params *game_info) {
  game_info->figure_next->dots[1][2] = BRICK;
  for (int i = 1; i < FIGURE_SIZE; i++) {
    game_info->figure_next->dots[2][i] = BRICK;
  }
}

/// @brief Sets the dots for a right shape in the next_field dots container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_right_angle(game_params *game_info) {
  game_info->figure_next->dots[1][3] = BRICK;
  for (int i = 1; i < FIGURE_SIZE; i++) {
    game_info->figure_next->dots[2][i] = BRICK;
  }
}

/// @brief Sets the dots for a right-oriented turn shape in the next_field dots
/// container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_turn_right(game_params *game_info) {
  for (int i = 1; i < FIGURE_SIZE / 2 + 1; i++) {
    game_info->figure_next->dots[i][FIGURE_SIZE - i] = BRICK;
    game_info->figure_next->dots[i][FIGURE_SIZE - i - 1] = BRICK;
  }
}

/// @brief Sets the dots for a left-oriented turn shape in the next_field dots
/// container.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_turn_left(game_params *game_info) {
  for (int i = 1; i < FIGURE_SIZE / 2 + 1; i++) {
    game_info->figure_next->dots[i][i] = BRICK;
    game_info->figure_next->dots[i][i + 1] = BRICK;
  }
}