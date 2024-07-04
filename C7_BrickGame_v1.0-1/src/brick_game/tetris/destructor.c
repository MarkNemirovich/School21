#include "../../gui/cli/gui.h"
#include "business_logic.h"

/// @brief Frees the memory allocated for the game information including the
/// game field and figures.
/// @param game_info Pointer to the game_params which memory will be freed.
void free_game_info(game_params *game_info) {
  free_fields(game_info);
  free_figure(game_info);
  game_info = NULL;
}

/// @brief Frees the memory allocated for the game field and next field.
/// @param game_info Pointer to the game_params containing the game field and
/// next field.
void free_fields(game_params *game_info) {
  if (game_info != NULL && game_info->field != NULL) {
    for (int i = 0; i < FIELD_Y_SIZE; i++) {
      free(game_info->field[i]);
      free(game_info->next[i]);
    }
    free(game_info->field);
    free(game_info->next);
  }
}

/// @brief Frees the memory allocated for the game figures.
/// @param game_info Pointer to the game_params containing the game figures.
void free_figure(game_params *game_info) {
  if (game_info != NULL) {
    free_block(game_info->figure_current);
    free_block(game_info->figure_next);
  }
}

/// @brief Free figure dots and itself.
/// @param figure Figure structire.
void free_block(block *figure) {
  if (figure != NULL) {
    if (figure->dots != NULL) {
      for (int i = 0; i < FIGURE_SIZE; i++) {
        free(figure->dots[i]);
      }
      free(figure->dots);
    }
    free(figure);
  }
}

/// @brief Free memory for a temporary dots used in the game.
/// @param dots Pointer to the 2D array of integers representing the figure.
/// @param size Size of the temporary figure (square).
void free_temp_figure(int **dots, int size) {
  if (dots != NULL) {
    for (int i = 0; i < size; i++) {
      free(dots[i]);
    }
    free(dots);
  }
}

/// @brief Frees the memory allocated for the current state game info.
/// @note This function should be called when the current state game info is no
/// longer needed to prevent memory leaks.
void free_game_state() {
  saved_params *current_game_info = get_game_info();
  int is_null = 0;
  if (current_game_info == NULL) is_null = 1;
  if (!is_null) {
    if (current_game_info->field != NULL) {
      for (int i = 0; i < BOTTOM_WALL; i++) {
        if (current_game_info->field[i] != NULL) {
          free(current_game_info->field[i]);
        }
      }
      free(current_game_info->field);
      current_game_info->field = NULL;
    }
    if (current_game_info->next != NULL) {
      for (int i = 0; i < BOTTOM_WALL; i++) {
        if (current_game_info->next[i] != NULL) {
          free(current_game_info->next[i]);
        }
      }
      free(current_game_info->next);
      current_game_info->next = NULL;
    }
  }
}