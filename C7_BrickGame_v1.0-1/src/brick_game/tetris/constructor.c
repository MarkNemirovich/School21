#include "../../gui/cli/gui.h"
#include "business_logic.h"

/// @brief Allocates memory for the game information including the game field
/// and figures.
/// @param game_info Pointer to the game_params structure where the
/// memory will be allocated.
/// @return Returns 0 if memory allocation is successful, otherwise returns 1.
int alloc_game_info(game_params *game_info) {
  int error = 0;
  error = allocate_memory_fields(game_info);
  if (!error) {
    error = allocate_memory_figures(game_info);
    if (error) {
      free_fields(game_info);
    }
  }
  return error;
}

/// @brief Allocates memory for the game field and next field of the game.
/// @param game_info Pointer to the game_params structure where the
/// memory will be allocated.
/// @return Returns 0 if memory allocation is successful, otherwise returns 1.
int allocate_memory_fields(game_params *game_info) {
  int error = 0;
  game_info->next = (int **)malloc(FIELD_Y_SIZE * sizeof(int *));
  game_info->field = (int **)malloc(FIELD_Y_SIZE * sizeof(int *));
  if (game_info->next != NULL && game_info->field != NULL) {
    error = allocate_memory_field(game_info->next) ||
            allocate_memory_field(game_info->field);
  }
  if (error) {
    if (game_info->next != NULL) {
      free(game_info->next);
    }
    if (game_info->field != NULL) {
      free(game_info->field);
    }
  }
  return error;
}

/// @brief Allocates memory for the game field and next field of the game.
/// @param field Pointer to the field matrix where the memory will be allocated.
/// @return Returns 0 if memory allocation is successful, otherwise returns 1.
int allocate_memory_field(int **field) {
  int error = 0;
  for (int i = 0; i < FIELD_Y_SIZE && !error; i++) {
    field[i] = (int *)malloc(FIELD_X_SIZE * sizeof(int));
    if (field[i] == NULL) {
      error = 1;
      for (int j = 0; j <= i; j++) {
        if (field[j] != NULL) {
          free(field[j]);
        }
      }
    }
  }
  return error;
}

/// @brief Allocates memory for the game field and next field of the game.
/// @param game_info Pointer to the game_params structure where the
/// memory will be allocated.
/// @return Returns 0 if memory allocation is successful, otherwise returns 1.
int allocate_memory_figures(game_params *game_info) {
  int error = 0;
  game_info->figure_current = malloc(sizeof(block));
  game_info->figure_next = malloc(sizeof(block));
  if (game_info->figure_current != NULL && game_info->figure_next != NULL) {
    error = allocate_memory_figure(game_info->figure_current) ||
            allocate_memory_figure(game_info->figure_next);
  }
  if (error) {
    if (game_info->figure_current != NULL) {
      free(game_info->figure_current);
    }
    if (game_info->figure_next != NULL) {
      free(game_info->figure_next);
    }
  }
  return error;
}

/// @brief Allocates memory for the game field and next field of the game.
/// @param figure Pointer to the figure structure where the
/// memory will be allocated.
/// @return Returns 0 if memory allocation is successful, otherwise returns 1.
int allocate_memory_figure(block *figure) {
  int error = 0;
  figure->dots = malloc(FIGURE_SIZE * sizeof(int *));
  if (figure->dots == NULL) {
    error = 1;
  }
  if (!error) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      figure->dots[i] = malloc(FIGURE_SIZE * sizeof(int));
      if (figure->dots[i] == NULL) {
        error = 1;
        for (int j = 0; j <= i; j++) {
          if (figure->dots[j] != NULL) {
            free(figure->dots[j]);
          }
        }
        free(figure->dots);
      }
    }
  }
  return error;
}

/// @brief Allocates memory for a temporary dots used in the game.
/// @return Returns a pointer to the allocated memory for the temporary dots if
/// successful, otherwise returns NULL.
int **alloc_temp_figure() {
  int **dots = (int **)malloc(FIGURE_SIZE * sizeof(int *));
  if (dots == NULL) return NULL;
  for (int i = 0; i < FIGURE_SIZE && dots != NULL; i++) {
    dots[i] = (int *)malloc(FIGURE_SIZE * sizeof(int));
    if (dots[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(dots[j]);
      }
      free(dots);
      dots = NULL;
    } else {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        dots[i][j] = 0;
      }
    }
  }
  return dots;
}

/// @brief Allocates memory for the current state game info.
/// @param current_state A pointer to the current state game info structure.
/// @return 0 if successful, 1 if memory allocation fails.
int alloc_game_states(saved_params *current_state) {
  int error = 0;
  current_state->field = malloc(BOTTOM_WALL * sizeof(int *));
  current_state->next = malloc(BOTTOM_WALL * sizeof(int *));
  if (current_state->field != NULL && current_state->next != NULL) {
    error = alloc_game_state(current_state->field);
    alloc_game_state(current_state->next);
  }
  if (error) {
    if (current_state->field != NULL) {
      free(current_state->next);
    }
    if (current_state->field != NULL) {
      free(current_state->next);
    }
  }
  return error;
}

/// @brief Allocates memory for the current state game info.
/// @param current_state A pointer to the current state game info structure.
/// @return 0 if successful, 1 if memory allocation fails.
int alloc_game_state(int **field) {
  int error = 0;
  for (int i = 0; i < BOTTOM_WALL && !error; i++) {
    field[i] = malloc(RIGHT_WALL * sizeof(int));
    if (field[i] == NULL) {
      for (int j = 0; j <= i; j++) {
        free(field[j]);
      }
      free(field);
      error = 1;
    }
  }
  return error;
}