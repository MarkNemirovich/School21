#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1

#define SURVIVAL_MIN 2
#define SURVIVAL_MAX 3
#define BIRTH_MIN 3
#define BIRTH_MAX 3

#define FILES_AMOUNT 7

#define FILE_0 "2shipCandle.txt"
#define FILE_1 "4oscils.txt"
#define FILE_2 "Gun.txt"
#define FILE_3 "InfinitLife.txt"
#define FILE_4 "mazeMice.txt"
#define FILE_5 "oscil+nat.txt"
#define FILE_6 "someFigures.txt"

#define MIN_DELAY 50
#define MAX_DELAY 500
#define MS 1000

#define ROWS 25
#define COLUMNS 80

void init_curses_settings();
char **one_line_alloc(int rows, int columns);
void print_state(char **generation, int rows, int columns);
int read_from_file(char **generation);
void iteration(char **generation, char **next_generation);
char cell_update(char **generation, int i, int j);

int main() {
    char **generation;
    char **next_generation;
    int error = 0;
    int work = 1;

    generation = one_line_alloc(ROWS, COLUMNS);
    next_generation = one_line_alloc(ROWS, COLUMNS);

    error = read_from_file(generation);

    if (error != FAIL) {
        init_curses_settings();
        int delay = MAX_DELAY;
        while (work) {
            int key = 0;
            napms(delay);
            clear();

            iteration(generation, next_generation);
            print_state(generation, ROWS, COLUMNS);

            key = getch();  // ждём нажатия символа
            if ((key == (int)'W' || key == (int)'w' || key == KEY_UP) && delay > MIN_DELAY) delay -= 50;
            if ((key == (int)'S' || key == (int)'s' || key == KEY_DOWN) && delay < MAX_DELAY) delay += 50;
            if (key == (int)'Q' || key == (int)'q') work = 0;
            refresh();                  // обновить
            resizeterm(ROWS, COLUMNS);  // Размер рабочей области
        }
        endwin();  // завершение работы с ncurses
    }
    free(generation);
    free(next_generation);
    return 0;
}

int read_from_file(char **generation) {
    int error = 0;
    for (int i = 0; error != FAIL && i < ROWS; i++) {
        for (int j = 0; error != FAIL && j < COLUMNS; j++) {
            char ch = 0;
            if ((ch = getchar()) != EOF) {
                if (ch == '0' || ch == '1')
                    generation[i][j] = (ch - '0');
                else
                    j--;
            } else
                error = FAIL;
        }
    }
    return error;
}

void init_curses_settings() {
    initscr();                  // Переход в curses-режим
    set_escdelay(1);            // ms Задержка на обратотки нажатия кнопки
    resizeterm(ROWS, COLUMNS);  // Размер рабочей области
    noecho();                   // Выключаем отображение вводимых символов
    cbreak();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);  // читаем стрелочки
    if (freopen("/dev/tty", "r", stdin) != NULL) TRUE;
    refresh();  // обновить экран
}

char **one_line_alloc(int rows, int columns) {
    char **array = (char **)malloc(rows * sizeof(char *) + rows * columns * sizeof(char));
    char *ptr = (char *)(array + rows);
    for (int i = 0; i < rows; i++) {
        array[i] = ptr + columns * i;
    }
    return array;
}

void print_state(char **generation, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (generation[i][j])
                printw("o");
            else
                printw(" ");
        }
    }
}

void iteration(char **generation, char **next_generation) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            next_generation[i][j] = cell_update(generation, i, j);
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            generation[i][j] = next_generation[i][j];
        }
    }
}

char cell_update(char **generation, int i, int j) {
    char alive_neighbours = 0;
    char state = generation[i][j];
    for (int k = i - 1; k <= i + 1; k++) {
        for (int m = j - 1; m <= j + 1; m++) {
            alive_neighbours += generation[(k + ROWS) % ROWS][(m + COLUMNS) % COLUMNS];
        }
    }
    alive_neighbours -= state;

    if (state)
        state = (alive_neighbours >= SURVIVAL_MIN && alive_neighbours <= SURVIVAL_MAX);
    else
        state = (alive_neighbours >= BIRTH_MIN && alive_neighbours <= BIRTH_MAX);

    return state;
}