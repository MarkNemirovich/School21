#ifndef __S21_BRICKS_GAME_GUI_H__
#define __S21_BRICKS_GAME_GUI_H__

#include "../../brick_game/tetris/business_logic.h"

#define GAME_WALL_Y_START 0
#define GAME_WALL_X_START 0
#define GAME_WALL_Y_END 22
#define GAME_WALL_X_END 22

#define SCORE_WALL_Y_END 42
#define SCORE_WALL_X_END 22

#define EMPTY_GUI "__"
#define BRICK_GUI "[]"

void frontend();

void print_menu();
void print_pause();

void print_game(saved_params game_info);
void print_score_panel(saved_params game_info);
void print_game_panel(saved_params game_info);
void print_close_game(saved_params game_info);
void print_text_to_centr(char *text, int y_pos);

#endif