#include "business_logic.h"

/// @brief Updates the game score, best score, and level based on the game
/// state.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
void score_update(game_params *game_info) {
  int count_fill_rows = check_full_rows(game_info);
  add_score(game_info, count_fill_rows);
  if (game_info->high_score < game_info->score) write_best_score(game_info);
  lvl_up(game_info);
}

/// @brief Updates the game score based on the number of filled rows cleared.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param count_fill_rows The number of filled rows that have been cleared.
/// This value determines how much the score will be increased.
void add_score(game_params *game_info, int count_fill_rows) {
  switch (count_fill_rows) {
    case 1:
      game_info->score += ONE_ROW;
      break;
    case 2:
      game_info->score += TWO_ROWS;
      break;
    case 3:
      game_info->score += THREE_ROWS;
      break;
    case 4:
      game_info->score += FOUR_ROWS;
      break;
    default:
      break;
  }
}

/// @brief Updates the game level and speed based on the score achieved.
/// @param game_info Pointer to the game_params structure containing extended
/// game information.
/// @param last_score The previous score before the current update. This value
/// is used to determine if a level up condition has been met.
void lvl_up(game_params *game_info) {
  if (game_info->score > LVL_UP * game_info->level &&
      game_info->level < MAX_LVL) {
    game_info->level++;
    if (game_info->speed > MIN_SPEED) game_info->speed -= 10;
  }
}

/// @brief Reads the best score from a file and updates the game information.
/// @param game_info A pointer to the game_params structure containing game
/// information.
void read_best_score(game_params *game_info) {
  FILE *f_best_score = fopen(FILE_PATH, "r");
  int best_score = 0;
  if (f_best_score != NULL) {
    if (fscanf(f_best_score, "%d", &best_score) != 1) {
      fprintf(f_best_score, "%d", 0);
    } else {
      game_info->high_score = best_score;
    }
    fclose(f_best_score);
  } else {
    perror("Error opening best_score.txt");
  }
}

/// @brief Updates the best score in the game based on the current game score.
/// @param game_info Pointer to the game_params structure containing extended
/// game information, including the current game score.
void write_best_score(game_params *game_info) {
  game_info->high_score = game_info->score;
  FILE *f_best_score = fopen(FILE_PATH, "w");
  if (f_best_score != NULL) {
    fprintf(f_best_score, "%d", game_info->score);
    fclose(f_best_score);
  } else {
    perror("Failed to open file for writing");
  }
}
