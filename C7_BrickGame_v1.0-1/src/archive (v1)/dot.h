#ifndef __S21_TETRIS_DOT_H__
#define __S21_TETRIS_DOT_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum dot_state { EMPTY, FILLED } dot_state;

typedef struct dot {
  int x;
  int y;
  dot_state state;
} dot;

#endif