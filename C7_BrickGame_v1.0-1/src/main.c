#include <time.h>

#include "brick_game/tetris/business_logic.h"
#include "gui/cli/gui.h"

int main() {
  srand(time(NULL));  // Инициализация генератора случайных чисел
  init_ncurses_settings();
  run_game();
  endwin();
  return 0;
}