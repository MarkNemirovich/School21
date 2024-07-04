#ifndef __S21_BRICKS_GAME_H__
#define __S21_BRICKS_GAME_H__

#include <time.h>

#include "ncurses.h"
#include "stdio.h"
#include "stdlib.h"

#define EMPTY 0
#define BRICK 1

#define FIELD_X_START 4
#define FIELD_Y_START 1

#define RIGHT_WALL 10
#define BOTTOM_WALL 20

#define FIELD_Y_SIZE 25
#define FIELD_X_SIZE 19

#define FIGURE_CENTER_X 3
#define FIGURE_SIZE 4

#define KEY_PAUSE 112
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_ENTER_REDEFINE 10

#define START_LVL 1
#define MAX_LVL 10
#define MIN_SPEED 10

#define FILE_PATH "brick_game/tetris/best_score.txt"

/// @brief Possible actions a user can take.
typedef enum {
  START,
  PAUSE,
  TERMINATE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
  SKIP
} actions;

/// @brief States of the game automaton which controls the game flow.
typedef enum {
  BEGGING,
  SPAWN,
  MOVING,
  SHIFTING,
  COLLIDED,
  ATTACHING,
  END
} automate_states;

/// @brief Possible actions a user can take.
typedef enum {
  ONE_ROW = 100,
  TWO_ROWS = 300,
  THREE_ROWS = 700,
  FOUR_ROWS = 1500,
  LVL_UP = 600
} score_values;

/// @brief Represents a game figure structure.
typedef struct {
  int x0;
  int y0;
  int **dots;
} block;

/// @brief Stores the basic state and configuration of the game.
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} saved_params;

/// @brief Stores the extended state and configuration of the game, including
/// the current and next figures.
typedef struct {
  int **field;
  int **next;
  block *figure_current;
  block *figure_next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int lose;
} game_params;

/// AUTOMATES
saved_params update_current_state();
saved_params *get_game_info();
void copy_game_info_to_the_current(game_params *game_info);
automate_states *get_current_state();

/// CONTROLLER
int get_user_action();
void user_shift(game_params *game_info, actions *user_action, int *collision);

/// CORE
void run_game();
void run_states_observer(game_params *game_info, actions *user_action,
                         int *tick_count, int *collision);
int turn_tick(game_params *game_info, int *tick_count);
void clear_terminal_buffer();
int check_full_rows(game_params *game_info);
void remove_full_line(game_params *game_info, int start_row);
void copy_next_field_to_current(game_params *game_info, int rows, int cols);

/// CONSTRUCTOR
int alloc_game_info(game_params *game_info);
int allocate_memory_fields(game_params *game_info);
int allocate_memory_field(int **field);
int allocate_memory_figures(game_params *game_info);
int allocate_memory_figure(block *figure);
int **alloc_temp_figure();
int alloc_game_states(saved_params *current_state);
int alloc_game_state(int **field);

/// DESTRUCTOR
void free_game_info(game_params *game_info);
void free_fields(game_params *game_info);
void free_figure(game_params *game_info);
void free_block(block *figure);
void free_temp_figure(int **dots, int size);
void free_game_state();

/// FIGURES ///
void create_figure_next(game_params *game_info);
void spawn_figure_to_game(game_params *game_info);
void copy_figure_next_to_current(game_params *game_info);
void clear_current_figure_from_game(game_params *game_info);
void clear_current_figure(game_params *game_info);
void clear_next_figure(game_params *game_info);

void move_figure(actions *user_action, game_params *game_info);
void move_pos_figure_down(game_params *game_info);
void move_pos_figure_left(game_params *game_info);
void move_pos_figure_right(game_params *game_info);
void add_next_pos_figure_to_game(game_params *game_info);
void rotate_figure(game_params *game_info, int **temp_figure);
int **rotated_figure(game_params *game_info);

int is_collision(game_params *game_info);
int can_spawn_figure(game_params *game_info);
int can_move_left(game_params *game_info);
int can_move_right(game_params *game_info);
int can_rotate(game_params *game_info, int **temp_figure, int can_rotate);
int check_intersection_when_rotate(game_params *game_info, int i, int j,
                                   int can_rotate);

/// GENERATOR ///
void create_figure_horizontal(game_params *game_info);
void create_figure_vertical(game_params *game_info);
void create_figure_box(game_params *game_info);
void create_figure_left_angle(game_params *game_info);
void create_figure_right_angle(game_params *game_info);
void create_figure_turn_right(game_params *game_info);
void create_figure_turn_left(game_params *game_info);
void create_figure_triangle(game_params *game_info);

/// INITIALIZATION ///
int init_game_info(game_params *game_info);
void init_figure(game_params *game_info);
void init_field(game_params *game_info);
void init_ncurses_settings();
void init_game_state(saved_params *current_state);
void init_after_menu(actions *user_action);

/// SCORE ///
void score_update(game_params *game_info);
void add_score(game_params *game_info, int count_fill_rows);
void lvl_up(game_params *game_info);
void read_best_score(game_params *game_info);
void write_best_score(game_params *game_info);

#endif