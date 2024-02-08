#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1

#define FILES_AMOUNT 7

#define FILE_0 "2shipCandle.txt"
#define FILE_1 "4oscils.txt"
#define FILE_2 "Gun.txt"
#define FILE_3 "InfinitLife.txt"
#define FILE_4 "mazeMice.txt"
#define FILE_5 "oscil+nat.txt"
#define FILE_6 "someFigures.txt"

#define MIN_DELAY 8
#define MAX_DELAY 512
#define MS 1000

#define ROWS 25
#define COLUMNS 80

void init_curses_settings();
char **one_line_alloc(int rows, int columns);
void print_state(char **generation, int rows, int columns, int selected_parameter, int delay, int *rules);
int read_from_file(char **generation, int file_number);
void iteration(char **generation, char **next_generation, int rows, int columns, int *rules);
char cell_update(char **generation, int i, int j, int rows, int columns, const int *rules);
void parameter_change(int term, int selected_parameter, int *rules);

int main() {
    char **generation;
    char **next_generation;
    int file_number = 0;

    int error = 0;
    int delay = MAX_DELAY / 4;

    generation = one_line_alloc(ROWS, COLUMNS);
    if (!generation) {
        printf("Memory allocation fail");
        return 0;
    }

    next_generation = one_line_alloc(ROWS, COLUMNS);
    if (!next_generation) {
        printf("Memory allocation fail");
        free(generation);
        return 0;
    }

    printf("Welcome to the game of life!\n");
    printf("Please enter number from 1 to %d of the init position\n", FILES_AMOUNT);

    while (!scanf("%d", &file_number) || file_number <= 0 || file_number > FILES_AMOUNT)
        printf("Please enter number from 1 to %d of the init position\n", FILES_AMOUNT);

    error = read_from_file(generation, file_number);

    if (error != FAIL) {
        init_curses_settings();
        int game = 1;
        int rules[4] = {2, 3, 3, 3};
        int selected_parameter = 0;

        while (game != 0) {
            int key = 0;

            napms(delay);
            clear();

            iteration(generation, next_generation, ROWS, COLUMNS, rules);
            print_state(generation, ROWS, COLUMNS, selected_parameter, delay, rules);

            key = getch();  // ждём нажатия символа
            if ((key == (int)'W' || key == (int)'w' || key == KEY_UP) && delay > MIN_DELAY) delay /= 2;
            if ((key == (int)'S' || key == (int)'s' || key == KEY_DOWN) && delay < MAX_DELAY) delay *= 2;

            if (key == (int)'A' || key == (int)'a' || key == KEY_LEFT)
                parameter_change(-1, selected_parameter, rules);
            if (key == (int)'D' || key == (int)'d' || key == KEY_RIGHT)
                parameter_change(1, selected_parameter, rules);

            if (key == (int)'F' || key == (int)'f') selected_parameter = (selected_parameter + 1) % 4;
            if (key == (int)'R' || key == (int)'r') selected_parameter = (selected_parameter + 3) % 4;

            if (key == (int)'Q' || key == (int)'q') game = 0;

            refresh();  // обновить

            resizeterm(ROWS + 14, COLUMNS);  // Размер рабочей области
        }
        endwin();  // завершение работы с ncurses
    }
    free(generation);
    free(next_generation);

    return 0;
}

int read_from_file(char **generation, int file_number) {
    int error = 0;
    FILE *fp;
    char *files[FILES_AMOUNT] = {FILE_0, FILE_1, FILE_2, FILE_3, FILE_4, FILE_5, FILE_6};
    if ((fp = fopen(files[file_number - 1], "rb+")) != NULL) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                char ch = 0;
                if ((ch = getc(fp)) != EOF) {
                    if (ch == '0' || ch == '1') {
                        generation[i][j] = (ch - '0');
                    } else
                        j--;
                } else
                    error = FAIL;
            }
        }
        fclose(fp);
    } else {
        error = FAIL;
        printf("File not founded\n");
    }
    return error;
}

void init_curses_settings() {
    initscr();  // Переход в curses-режим
    set_escdelay(1);
    resizeterm(ROWS + 14, COLUMNS);  // Размер рабочей области
    noecho();  // Выключаем отображение вводимых символов
    cbreak();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);  // читаем стрелочки
    refresh();             // обновить экран
}

char **one_line_alloc(int rows, int columns) {
    char **array = (char **)malloc(rows * sizeof(char *) + rows * columns * sizeof(char));
    char *ptr = (char *)(array + rows);
    for (int i = 0; i < rows; i++) {
        array[i] = ptr + columns * i;
    }
    return array;
}

void print_state(char **generation, int rows, int columns, int selected_parameter, int delay, int *rules) {
    printw("                   =====  GAME OF LIFE  =====\n\n");
    printw("Use up/down arrow keys or W/S keys to change speed up and down\n");
    printw("Use left/right arrow keys or A/D keys to change game rules\n");
    printw(
        "Use R/F keys to choice the rule you want to change (look at the "
        "cursor)\n");
    printw("Press Q to end game\n\n");

    printw("Survival min condition:  %d  ", rules[0]);
    if (selected_parameter == 0)
        printw("<\n");
    else
        printw("\n");

    printw("Survival max condition:  %d  ", rules[1]);
    if (selected_parameter == 1)
        printw("<\n");
    else
        printw("\n");

    printw("Birth min condition:     %d  ", rules[2]);
    if (selected_parameter == 2)
        printw("<\n");
    else
        printw("\n");

    printw("Birth max condition:     %d  ", rules[3]);
    if (selected_parameter == 3)
        printw("<\n");
    else
        printw("\n");

    printw("Game speed:              %d\n\n\n", MAX_DELAY / delay);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (generation[i][j])
                printw("o");
            else
                printw(" ");
        }
    }
}

void iteration(char **generation, char **next_generation, int rows, int columns, int *rules) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            next_generation[i][j] = cell_update(generation, i, j, rows, columns, rules);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            generation[i][j] = next_generation[i][j];
        }
    }
}

char cell_update(char **generation, int i, int j, int rows, int columns, const int *rules) {
    char alive_neighbours = 0;
    char state = generation[i][j];
    for (int k = i - 1; k <= i + 1; k++) {
        for (int m = j - 1; m <= j + 1; m++) {
            alive_neighbours += generation[(k + rows) % rows][(m + columns) % columns];
        }
    }
    alive_neighbours -= state;

    if (state)
        state = (alive_neighbours >= rules[0] && alive_neighbours <= rules[1]);
    else
        state = (alive_neighbours >= rules[2] && alive_neighbours <= rules[3]);

    return state;
}

void parameter_change(int term, int selected_parameter, int *rules) {
    if (selected_parameter == 0) {
        rules[0] += term;
        if (rules[0] < 0) rules[0] = 0;
        if (rules[0] > rules[1]) rules[0] = rules[1];
    }

    if (selected_parameter == 1) {
        rules[1] += term;
        if (rules[1] > 8) rules[1] = 8;
        if (rules[1] < rules[0]) rules[1] = rules[0];
    }

    if (selected_parameter == 2) {
        rules[2] += term;
        if (rules[2] < 0) rules[2] = 0;
        if (rules[2] > rules[3]) rules[2] = rules[3];
    }

    if (selected_parameter == 3) {
        rules[3] += term;
        if (rules[3] > 8) rules[3] = 8;
        if (rules[3] < rules[2]) rules[3] = rules[2];
    }
}