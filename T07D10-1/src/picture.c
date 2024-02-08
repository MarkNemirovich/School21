#include <stdio.h>
#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

void output(int n, int m, int **matrix);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform(*picture_data, picture, N, M);

    make_picture(picture, N, M);
    return 0;
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);
    int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);
    int length_tree_foliage = sizeof(tree_foliage) / sizeof(tree_foliage[0]);
    int length_tree_trunk = sizeof(tree_trunk) / sizeof(tree_trunk[0]);
    int sun_data_rows = sizeof(sun_data) / sizeof(sun_data[0]);
    int sun_data_cols = sizeof(sun_data[0]) / sizeof(sun_data[0][0]);

    // foliage
    for (int i = 0; i < length_tree_foliage; i++) {
        picture[i + 2][3] = tree_foliage[i];
        picture[i + 2][4] = tree_foliage[i];
        picture[3][i + 2] = tree_foliage[i];
        picture[4][i + 2] = tree_foliage[i];
    }
    // trunk
    for (int i = 0; i < length_tree_trunk; i++) {
        picture[i + 6][3] = tree_trunk[i];
        picture[i + 6][4] = tree_trunk[i];
        picture[10][i + 2] = tree_trunk[i];
    }
    // sun
    for (int i = 0; i < sun_data_rows; i++)
        for (int j = 0; j < sun_data_cols; j++) {
            picture[i + 1][j + 7] = sun_data[i][j];
        }

    // boards
    for (int i = 0; i < length_frame_h; i++) {
        picture[i][0] = frame_h[i];
        picture[i][6] = frame_h[i];
        picture[i][12] = frame_h[i];
    }
    for (int i = 0; i < length_frame_w; i++) {
        picture[0][i] = frame_w[i];
        picture[7][i] = frame_w[i];
        picture[14][i] = frame_w[i];
    }
    output(n, m, picture);
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void output(int n, int m, int **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}