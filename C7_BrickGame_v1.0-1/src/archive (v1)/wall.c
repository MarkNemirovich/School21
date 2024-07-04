#include "wall.h"

wall *s21_create_field() {
  wall *w = malloc(sizeof(wall));
  dot **dots = (dot **)malloc(WIDTH * sizeof(dot *));
  for (int i = 0; i < WIDTH; i++) {
    dots[i] = (dot *)malloc(HEIGHT * sizeof(dot));
  }
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      dots[x][y] = (dot){x, y, EMPTY};
    }
  }
  w->dots = dots;
  return w;
}

void s21_delete_field(wall *w) {
  for (int i = 0; i < WIDTH; i++) {
    free(w->dots[i]);
  }
  free(w->dots);
  free(w);
}

int s21_delete_rows(wall *w) {
  int counter = 0;  // for score and shift down
  for (int y = 0; y < HEIGHT; y++) {
    int dot_states = 0;
    for (int x = 0; x < WIDTH; x++) {
      dot_states += w->dots[x][y].state;
    }
    if (dot_states / WIDTH)  // all are filled
    {
      s21_delete_row(w, y);
      counter++;
    }
  }
  s21_shift_rows_down(w, counter);
  return counter;
}

void s21_delete_row(wall *w, int index) {
  for (int x = 0; x < WIDTH; x++) {
    w->dots[x][index].state = 0;
  }
}

void s21_shift_rows_down(wall *w, int amount) {
  for (int y = amount; y >= 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
      w->dots[x][y].state = w->dots[x][y - 1].state;  // copy upper dot's state
    }
  }
}