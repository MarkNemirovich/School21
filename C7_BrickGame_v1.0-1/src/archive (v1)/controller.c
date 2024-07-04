#include "controller.h"

#include "wall.h"

void s21_init_controller() {
  initscr();  // Переход в curses-режим
  set_escdelay(1);
  resizeterm(WIDTH + 14, HEIGHT);  // Размер рабочей области
  noecho();  // Выключаем отображение вводимых символов
  cbreak();
  nodelay(stdscr, TRUE);
  curs_set(0);
  keypad(stdscr, TRUE);  // читаем стрелочки
  refresh();             // обновить экран
}

actions s21_get_action(int *time) {
  // read symbols
  actions action = NOTHING;
  while (*time-- > 0 && action == NOTHING) {
    int key = getch();
    switch (key) {
      case KEY_LEFT:
        action = LEFT;
        break;
      case KEY_RIGHT:
        action = RIGHT;
        break;
      case KEY_DOWN:
        action = DOWN;
        break;
      default:
        action = NOTHING;
        break;
    }
  }
  return action;
}