#include "block.h"

block *s21_create_block(int type) {
  block *b = malloc(sizeof(block));
  dot *dots = (dot *)malloc(BLOCK_SIZE * sizeof(dot));
  b->type = type;
  b->dots = dots;
  b->dots[0] = (dot){START_X, START_Y, FILLED};
  b->dots[1] = (dot){START_X + 1, START_Y, FILLED};
  for (int i = 2; i < BLOCK_SIZE; i++) {
    switch (type) {
      case HORIZONTAL:
      case VERTICAL:
        b->dots[2] = (dot){START_X - 1, START_Y, FILLED};
        b->dots[3] = (dot){START_X + 2, START_Y, FILLED};
        break;
      case L_SHAPE:
      case T_SHAPE:
      case R_SHAPE:
        b->dots[2] = (dot){START_X - 1, START_Y, FILLED};
        b->dots[3] = (dot){type, START_Y - 1, FILLED};
        break;
      case SQUARE:
        b->dots[2] = (dot){START_X, START_Y + 1, FILLED};
        b->dots[3] = (dot){START_X + 1, START_Y + 1, FILLED};
        break;
      case CROSS_LEFT:
        b->dots[2] = (dot){START_X - 1, START_Y - 1, FILLED};
        b->dots[3] = (dot){START_X, START_Y - 1, FILLED};
        break;
      case CROSS_RIGHT:
        b->dots[2] = (dot){START_X - 1, START_Y + 1, FILLED};
        b->dots[3] = (dot){START_X, START_Y + 1, FILLED};
        break;
      default:
        break;
    }
  }
  if (type == HORIZONTAL)
    for (int i = 0; i < BLOCK_SIZE; i++) b->dots[i].y--;
  if (type == VERTICAL) s21_turn_block(b);
  return b;
}

void s21_delete_block(block *b) {
  free(b->dots);
  free(b);
}

void s21_copy_block(block src, block *res) {
  res->type = src.type;
  for (int i = 0; i < BLOCK_SIZE; i++)
    res->dots[i] = (dot){src.dots[i].x, src.dots[i].y, src.dots[i].state};
}

void s21_turn_block(block *b) {
  int x0 = b->dots[0].x;
  int y0 = b->dots[0].y;
  for (int i = 1; i < BLOCK_SIZE; i++) {
    int dx = b->dots[i].x - x0;
    int dy = b->dots[i].y - y0;
    if (dx == 0 || dy == 0)  // on any axis
    {
      b->dots[i].x = x0 - dy;
      b->dots[i].y = y0 + dx;
    } else  // in the corner
    {
      if (dx == dy)
        b->dots[i].x -= 2 * dx;
      else
        b->dots[i].y -= 2 * dy;
    }
  }
}

void s21_shift_right(block *b) {
  for (int i = 0; i < BLOCK_SIZE; i++) b->dots[i].x++;
}
void s21_shift_left(block *b) {
  for (int i = 0; i < BLOCK_SIZE; i++) b->dots[i].x--;
}
void s21_shift_down(block *b) {
  for (int i = 0; i < BLOCK_SIZE; i++) b->dots[i].y++;
}