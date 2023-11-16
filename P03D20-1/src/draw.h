#ifndef GRAPH_H
#define GRAPH_H

#define _USE_MATH_DEFINES
#define WIDTH 80
#define HEIGHT 25
#define POINT '.'
#define STAR '*'

char **calloc_matrix(int height, int width);
void init_graph(char **graph, int height, int width);
void draw_graph(char **graph, int height);
void free_matrix(char **graph, int height);
void draw_empty_graph(int height);
#endif