#include "draw.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char **callocMatrix(int height, int width) {
    char **matrix = malloc(height * sizeof(char *));
    if (matrix == NULL) {
        puts("no memory");
    } else {
        for (int y = 0; y < height; y++) {
            matrix[y] = calloc(width, sizeof(char));
            if (matrix[y] == NULL) {
                puts("no memory");
            }
        }
    }
    return matrix;
}

void initGraph(char **graph, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            graph[y][x] = POINT;
        }
        graph[y][width] = '\0';
    }
}

void drawGraph(char **graph, int height) {
    //  printf("\e[1;1H\e[2J");
    for (int y = 0; y < height; y++) {
        puts(graph[y]);
    }
}

void drawEmptyGraph(int height) {
    //   printf("\e[1;1H\e[2J");
    for (int i = 0; i < height; i++) {
        puts("................................................................................");
    }
}

void freeMatrix(char **graph, int height) {
    for (int i = 0; i < height; i++) {
        free(graph[i]);
    }
    free(graph);
}