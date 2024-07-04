#include <time.h>

#include "business_logic.h"

/// @brief Moves the dots according to the user action.
/// @param user_action The action to be performed on the dots.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void move_figure(actions *user_action, game_params *game_info) {
  int can_move = 1;
  switch (*user_action) {
    case DOWN:
      move_pos_figure_down(game_info);
      break;
    case LEFT:
      if ((can_move = can_move_left(game_info)) == 1)
        move_pos_figure_left(game_info);
      break;
    case RIGHT:
      if ((can_move = can_move_right(game_info)) == 1)
        move_pos_figure_right(game_info);
      break;
    case ACTION:
      int **temp_rotated_figure = rotated_figure(game_info);
      if ((can_move = can_rotate(game_info, temp_rotated_figure, can_move)))
        rotate_figure(game_info, temp_rotated_figure);
      free_temp_figure(temp_rotated_figure, FIGURE_SIZE);
      break;
    default:
      break;
  }
  if (can_move) add_next_pos_figure_to_game(game_info);
}

/// @brief Clears the next figure dots.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void clear_next_figure(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (game_info->figure_next->dots[i][j] == BRICK)
        game_info->figure_next->dots[i][j] = EMPTY;
    }
  }
}

/// @brief Generates a new dots for the next figure.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void create_figure_next(game_params *game_info) {
  clear_next_figure(game_info);
  int figure_num = rand() % 8;
  switch (figure_num) {
    case 0:
      create_figure_horizontal(game_info);
      break;
    case 1:
      create_figure_vertical(game_info);
      break;
    case 2:
      create_figure_box(game_info);
      break;
    case 3:
      create_figure_left_angle(game_info);
      break;
    case 4:
      create_figure_right_angle(game_info);
      break;
    case 5:
      create_figure_turn_left(game_info);
      break;
    case 6:
      create_figure_turn_right(game_info);
      break;
    case 7:
      create_figure_triangle(game_info);
      break;
  }
  game_info->figure_next->y0 = 0;
  game_info->figure_next->x0 = FIGURE_CENTER_X;
}

/// @brief Spawns the current dots to the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void spawn_figure_to_game(game_params *game_info) {
  copy_figure_next_to_current(game_info);
  game_info->figure_current->x0 = FIGURE_CENTER_X;
  game_info->figure_current->y0 = 0;
  create_figure_next(game_info);
}

/// @brief Checks if a new dots can be spawned in the game field without
/// collision.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return 1 if the dots can be spawned without collision, 0 otherwise.
int can_spawn_figure(game_params *game_info) {
  int can_spawn = 1;
  int x0 = game_info->figure_next->x0;
  int y0 = game_info->figure_next->y0;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (game_info->figure_next->dots[i][j] == BRICK) {
        if (game_info->field[i + y0][j + x0] == BRICK) {
          can_spawn = 0;
        }
      }
    }
  }
  return can_spawn;
}

/// @brief Checks if the current dots collides with the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return 1 if there is a collision, 0 otherwise.
int is_collision(game_params *game_info) {
  int collision = 0;

  for (int i = FIGURE_SIZE - 1; i >= 0; i--) {
    for (int j = FIGURE_SIZE - 1; j >= 0; j--) {
      if (game_info->figure_current->dots[i][j] == BRICK) {
        if (game_info->field[i + game_info->figure_current->y0 + 1]
                            [j + game_info->figure_current->x0] == BRICK ||
            i + game_info->figure_current->y0 + 1 == BOTTOM_WALL) {
          collision = 1;
        }
      }
    }
  }
  return collision;
}

/// @brief Checks if the current dots can move to the right in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return 1 if the dots can move to the right, 0 otherwise.
int can_move_right(game_params *game_info) {
  int can_move = 1;
  int x0 = game_info->figure_current->x0;
  int y0 = game_info->figure_current->y0;
  for (int i = FIGURE_SIZE - 1; i >= 0; i--) {
    for (int j = FIGURE_SIZE - 1; j >= 0; j--) {
      if (game_info->figure_current->dots[i][j] == BRICK) {
        if (game_info->field[i + y0][j + x0 + 1] == BRICK ||
            (j + x0 + 1) == RIGHT_WALL) {
          can_move = 0;
        }
      }
    }
  }
  return can_move;
}

/// @brief Checks if the current dots can move to the left in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return 1 if the dots can move to the left, 0 otherwise.
int can_move_left(game_params *game_info) {
  int can_move = 1;
  int x0 = game_info->figure_current->x0;
  int y0 = game_info->figure_current->y0;
  for (int i = FIGURE_SIZE - 1; i >= 0; i--) {
    for (int j = FIGURE_SIZE - 1; j >= 0; j--) {
      if (game_info->figure_current->dots[i][j] == BRICK) {
        if (game_info->field[i + y0][j + x0 - 1] == BRICK || (j + x0) == 0) {
          can_move = 0;
        }
      }
    }
  }
  return can_move;
}

/// @brief Checks if the current dots can move down in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return 1 if the dots can move down, 0 otherwise.
int can_move_down(game_params *game_info) {
  int can_move = 1;
  int x0 = game_info->figure_current->x0;
  int y0 = game_info->figure_current->y0;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (game_info->figure_current->dots[i][j] == BRICK) {
        if (game_info->field[i + y0 + 1][j + x0] != EMPTY) {
          can_move = 0;
        }
      }
    }
  }
  return can_move;
}

/// @brief Clears the current figure dots from the game field and resets its
/// position.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void clear_current_figure(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (game_info->figure_current->dots[i][j] == BRICK) {
        game_info->figure_current->dots[i][j] = EMPTY;
      }
    }
  }
  game_info->figure_current->x0 = 0;
  game_info->figure_current->y0 = 0;
}

/// @brief Clears the current dots from the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void clear_current_figure_from_game(game_params *game_info) {
  int x0 = game_info->figure_current->x0;
  int y0 = game_info->figure_current->y0;
  for (int i_game = y0, i_figure = 0; i_game < FIGURE_SIZE + y0;
       i_game++, i_figure++) {
    for (int j_game = x0, j_figure = 0; j_game < FIGURE_SIZE + x0;
         j_game++, j_figure++) {
      if (game_info->figure_current->dots[i_figure][j_figure] == BRICK)
        game_info->next[i_game][j_game] = EMPTY;
    }
  }
}

/// @brief Clears the current dots from the game field and adds the next
/// position dots to the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void add_next_pos_figure_to_game(game_params *game_info) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      int y_figure_pixel = i + game_info->figure_current->y0;
      int x_figure_pixel = j + game_info->figure_current->x0;
      if (game_info->figure_current->dots[i][j] == BRICK) {
        game_info->next[y_figure_pixel][x_figure_pixel] =
            game_info->figure_current->dots[i][j];
      }
    }
  }
}

/// @brief Moves the current dots down in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void move_pos_figure_down(game_params *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->y0 = game_info->figure_current->y0 + 1;
}

/// @brief Moves the current dots to the left in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void move_pos_figure_left(game_params *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->x0 = game_info->figure_current->x0 - 1;
}

/// @brief Moves the current dots to the right in the game field.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void move_pos_figure_right(game_params *game_info) {
  clear_current_figure_from_game(game_info);
  game_info->figure_current->x0 = game_info->figure_current->x0 + 1;
}

/// @brief Rotates the current dots by 90 degrees clockwise.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @return A 2D array representing the rotated dots.
int **rotated_figure(game_params *game_info) {
  int **temp_figure;
  temp_figure = alloc_temp_figure();
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      temp_figure[j][FIGURE_SIZE - i - 1] =
          game_info->figure_current->dots[i][j];
    }
  }
  return temp_figure;
}

/// @brief Checks if the current dots can be rotated without intersecting with
/// the game field or reaching its boundaries.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @param temp_figure A pointer to the 2D array representing the rotated dots.
/// @param can_rotate The current state of rotation feasibility.
/// @return 1 if the rotation is feasible, 0 if there is an intersection or
/// boundary reached.
int can_rotate(game_params *game_info, int **temp_figure, int can_rotate) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (temp_figure[i][j] == BRICK) {
        can_rotate =
            check_intersection_when_rotate(game_info, i, j, can_rotate);
      }
    }
  }
  return can_rotate;
}

/// @brief Checks for intersection when rotating the current dots.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @param i The row index of the rotated dots.
/// @param j The column index of the rotated dots.
/// @param can_rotate The current state of rotation feasibility.
/// @return 1 if the rotation is feasible, 0 if there is an intersection or
/// boundary reached.
int check_intersection_when_rotate(game_params *game_info, int i, int j,
                                   int can_rotate) {
  int x_pos_figure = j + game_info->figure_current->x0;
  int y_pos_figure = i + game_info->figure_current->y0;
  if (game_info->field[i + y_pos_figure][j + x_pos_figure] == BRICK) {
    can_rotate = 0;
  } else if (x_pos_figure == RIGHT_WALL || x_pos_figure == -1 ||
             y_pos_figure == BOTTOM_WALL) {
    can_rotate = 0;
  }
  return can_rotate;
}

/// @brief Rotates the current dots by replacing it with the provided rotated
/// dots.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
/// @param temp_figure A pointer to the 2D array representing the rotated dots.
void rotate_figure(game_params *game_info, int **temp_figure) {
  clear_current_figure_from_game(game_info);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      game_info->figure_current->dots[i][j] = temp_figure[i][j];
    }
  }
}

/// @brief Copies the next figure dots to the current dots and resets its
/// position.
/// @param game_info A pointer to the game_params struct containing the game
/// state.
void copy_figure_next_to_current(game_params *game_info) {
  clear_current_figure(game_info);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      game_info->figure_current->dots[i][j] =
          game_info->figure_next->dots[i][j];
    }
  }
}