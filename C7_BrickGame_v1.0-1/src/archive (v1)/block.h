#ifndef __S21_TETRIS_BLOCK_H__
#define __S21_TETRIS_BLOCK_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dot.h"

#define BLOCK_SIZE 4
#define BLOCK_TYPES 8
#define START_X 4
#define START_Y 1

typedef enum figure_type {
  HORIZONTAL,  // 0 4 in a horisontal row
  VERTICAL,    // 1 4 in a vertical row
  SQUARE,      // 2 2 in a row, 2 rows
  L_SHAPE,     // 3 3 in a row, 1 above left dot
  T_SHAPE,     // 4 3 in a row, 1 above mid dot
  R_SHAPE,     // 5 3 in a row, 1 above right dot
  CROSS_LEFT,  // 6 2 in a row, upper row shifted by 1 to the left
  CROSS_RIGHT  // 7 2 in a row, upper row shifted by 1 to the right
} figure_type;

typedef struct block {
  dot *dots;
  figure_type type;
} block;

block *s21_create_block(int type);
void s21_delete_block(block *b);
void s21_turn_block(block *b);  //(clockwise rotation)
void s21_shift_right(block *b);
void s21_shift_left(block *b);
void s21_shift_down(block *b);
void s21_copy_block(block src, block *res);

#endif