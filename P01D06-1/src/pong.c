// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <math.h>
#include <stdio.h>

#define LEFT_BOUND 0
#define RIGHT_BOUND 24
#define UP_BOUND 0
#define DOWN_BOUND 79

int updateBallPos(int ballPos, int ballVelocity);
int newRocketPos(int rocket, int direction);
char bounce(int ballX, int ballY, int leftY, int rightY);
void draw(int leftPos, int rightPos, int ballX, int ballY);
int main() {
    /* Intializes random number generator */
    int scoreL = 0;
    int scoreR = 0;
    int ballVX = 1, ballVY = 1;
    while (scoreL < 21 && scoreR < 21) {
        int ballX = RIGHT_BOUND / 2, ballY = (DOWN_BOUND + 1) / 2, leftY = (DOWN_BOUND + 1) / 2,
            rightY = (DOWN_BOUND + 1) / 2;
        char key = 0, goal = 0, b;
        draw(leftY, rightY, ballX, ballY);
        while (goal == 0) {
            scanf("%c", &key);
            if (key == '\n') continue;
            b = bounce(ballX + ballVX, ballY + ballVY, leftY, rightY);
            printf("%c\n", b);
            switch (b) {
                case 'f':
                    scoreR++;
                    goal = 1;
                    break;
                case 's':
                    scoreL++;
                    goal = 1;
                    break;
                case 'l':
                    ballVX = -ballVX;
                    break;
                case 'r':
                    ballVX = -ballVX;
                    break;
                case 'u':
                    ballVY = -ballVY;
                    break;
                case 'd':
                    ballVY = -ballVY;
                    break;
                default:
                    break;
            }
            ballX = updateBallPos(ballX, ballVX);
            ballY = updateBallPos(ballY, ballVY);

            if (key == 'A' || key == 'a') {
                leftY = newRocketPos(leftY, -1);
                draw(leftY, rightY, ballX, ballY);
            } else if (key == 'Z' || key == 'z') {
                leftY = newRocketPos(leftY, 1);
                draw(leftY, rightY, ballX, ballY);
            } else if (key == 'K' || key == 'k') {
                rightY = newRocketPos(rightY, -1);
                draw(leftY, rightY, ballX, ballY);
            } else if (key == 'M' || key == 'm') {
                rightY = newRocketPos(rightY, 1);
                draw(leftY, rightY, ballX, ballY);
            } else if (key == ' ')
                draw(leftY, rightY, ballX, ballY);
        }
    }
    if (scoreL == 21)
        printf("Right player won!");
    else
        printf("Left player won!");
    return 0;
}

int updateBallPos(int ballPos, int ballVelocity) { return ballPos + ballVelocity; }

int newRocketPos(int rocket, int direction) {
    if (rocket + direction >= 0 && rocket + direction < 80) rocket += direction;
    return rocket;
}

char bounce(int ballX, int ballY, int leftY, int rightY) {
    printf("%d\t", ballX);
    printf("%d\t", ballY);
    printf("%d\t", leftY);
    printf("%d\t", rightY);
    if (ballX == LEFT_BOUND) {
        if ((ballY <= leftY + 2) && (ballY >= leftY - 2))
            return 'l';
        else
            return 'f';
    }
    if (ballX == RIGHT_BOUND) {
        if ((ballY <= rightY + 2) && (ballY >= rightY - 2))
            return 'r';
        else
            return 's';
    }
    if (ballY == UP_BOUND) return 'u';
    if (ballY == DOWN_BOUND) return 'd';
    return 'e';
}
void draw(int leftY, int rightY, int ballX, int ballY) {
    for (int j = 0; j < 24; j++) printf("_");
    printf("\n");
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            if (j == 0) {
                if (i >= leftY - 1 && i <= leftY + 1)
                    printf("]");
                else
                    printf("|");
                continue;
            }
            if (j == 24) {
                if (i >= rightY - 1 && i <= rightY + 1)
                    printf("[");
                else
                    printf("|");
                continue;
            }
            if (j == ballX && i == ballY) {
                printf("*");
            } else {
                if (i == 79) {
                    printf("_");
                } else
                    printf(" ");
            }
        }
        printf("\n");
    }
}