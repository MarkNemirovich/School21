#ifndef __S21_TETRIS_STATES_H__
#define __S21_TETRIS_STATES_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "block.h"
#include "controller.h"
#include "dot.h"
#include "wall.h"

#define DELAY 1000  // change to a variable later

typedef enum states {
  START,      // 4 in a horisontal row
  SPAWN,      // 4 in a vertical row
  MOVING,     // 2 in a row, 2 rows
  SHIFTING,   // 3 in a row, 1 above left dot
  ATTACHING,  // 3 in a row, 1 above mid dot
  END         // 2 in a row, upper row shifted by 1 to the right
} states;

void s21_start_game();
block *s21_spawn(wall *w);
void s21_attach(wall *w, block *b);
void s21_end_game();
void s21_change_state(states new_state, ...);
int s21_check_bounds(block *b);
int s21_check_contact(wall *w, block *b);
void s21_move(wall *w, block *b);
void s21_shift(wall *w, block *b, actions act);
void s21_attach_block(wall *w, block *b);

// temporary
void temporary_print(wall *w, block *b);

// not realized yet
void s21_show_next_block();

#endif