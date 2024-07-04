#ifndef __S21_TETRIS_CONTROLLER_H__
#define __S21_TETRIS_CONTROLLER_H__

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum actions {
  LEFT,   // key_left
  RIGHT,  // key_right
  DOWN,   // key_down
  TURN,   // ENTER
  BEGIN,  // 1
  PAUSE,  // SPACE
  QUIT,   // ESCAPE
  NOTHING = -1
} actions;
void s21_init_controller();
actions s21_get_action(int *time);

#endif