#include "states.h"

void s21_change_state(states state, ...) {
  va_list args;
  va_start(args, state);
  wall *w = va_arg(args, wall *);  // can be null
  block *b = va_arg(args, block *);
  static int time;
  static actions last_action;
  switch (state) {
    case SPAWN:
      time = DELAY;
      b = s21_spawn(w);
      break;
    case MOVING:
      s21_move(w, b);
      break;
    case SHIFTING:
      // create controlling
      if (time <= 0 || last_action == DOWN)
        s21_move(w, b);
      else {
        last_action = s21_get_action(&time);
        s21_shift(w, b, last_action);
      }
      break;
    case ATTACHING:
      s21_attach(w, b);
      break;
    default:
      s21_end_game(w, b);
      break;
  }
  va_end(args);
}

void s21_start_game() {
  // set score, read record
  srand(time(NULL));
  wall *w = s21_create_field();
  s21_init_controller();
  // s21_change_state(SPAWN, w);
  free(w);
}

block *s21_spawn(wall *w) {
  int random = rand();
  random = rand() % (BLOCK_TYPES);
  block *b = s21_create_block(random);
  if (s21_check_contact(w, b))
    s21_end_game(w, b);
  else
    s21_change_state(SHIFTING, w, b);
  return b;
}

void s21_move(wall *w, block *b) {
  temporary_print(w, b);
  s21_shift_down(b);
  if (s21_check_contact(w, b)) {
    s21_change_state(ATTACHING, w, b);
  } else {
    s21_change_state(SHIFTING, w, b);
  }
}

void s21_shift(wall *w, block *b, actions act) {
  block *temp = s21_create_block(b->type);
  s21_copy_block(*b, temp);
  switch (act) {
    case LEFT:
      s21_shift_left(temp);
      break;
    case RIGHT:
      s21_shift_right(temp);
      break;
    case TURN:
      s21_turn_block(temp);
      break;
    case DOWN:
      do {
        s21_copy_block(*temp, b);
        s21_shift_down(temp);
      } while ((!s21_check_contact(w, temp)));
      break;
    default:
      break;
  }
  if (!s21_check_bounds(temp) && !s21_check_contact(w, temp))
    s21_copy_block(*temp, b);
  s21_delete_block(temp);
  s21_change_state(SHIFTING, w, b);
}

void s21_attach(wall *w, block *b) {
  s21_attach_block(w, b);
  s21_delete_block(b);
  s21_change_state(SPAWN, w);
}

void s21_end_game(wall *w, block *b) {
  // write record
  temporary_print(w, b);
  if (b != NULL) s21_delete_block(b);
  if (w != NULL) s21_delete_field(w);
}

int s21_check_bounds(block *b) {
  int hit = 0;
  for (int i = 0; i < BLOCK_SIZE && !hit; i++) {
    if (b->dots[i].x >= WIDTH || b->dots[i].x < 0) hit = 1;
  }
  return hit;
}

int s21_check_contact(wall *w, block *b) {
  int hit = 0;
  for (int i = 0; i < BLOCK_SIZE && !hit; i++) {
    int x = b->dots[i].x;
    int y = b->dots[i].y;
    if ((y >= 0 && w->dots[x][y].state == FILLED) || y == HEIGHT - 1) {
      hit = 1;
    }
  }
  return hit;
}

void s21_attach_block(wall *w, block *b) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    int x = b->dots[i].x;
    int y = b->dots[i].y;
    w->dots[x][y].state = FILLED;
  }
}

void temporary_print(wall *w, block *b) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int hit = 0;
      for (int i = 0; i < BLOCK_SIZE; i++) {
        if (b->dots[i].x == x && b->dots[i].y == y) hit = 1;
      }
      if (hit)
        printf("2");
      else
        printf("%d", w->dots[x][y].state);
    }
    printf("\n");
  }
}