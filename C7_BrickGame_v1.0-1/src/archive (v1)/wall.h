#ifndef __S21_TETRIS_WALL_H__
#define __S21_TETRIS_WALL_H__

#include <stdio.h>
#include <stdlib.h>

#include "dot.h"

#define WIDTH 10
#define HEIGHT 20

typedef struct wall {
  dot **dots;
} wall;

wall *s21_create_field();
void s21_delete_field(wall *w);
int s21_delete_rows(wall *w);
void s21_delete_row(wall *w, int index);
void s21_shift_rows_down(wall *w, int index);

#endif