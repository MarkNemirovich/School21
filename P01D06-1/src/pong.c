// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

#define LEFT_BOUND 0
#define RIGHT_BOUND 79
#define UP_BOUND 0
#define DOWN_BOUND 25

int updateBallPos(int ballPos, int ballVelocity);
int newRocketPos(int rocket, int direction);
char bounce(int ballX, int ballY, int leftY, int rightY);
void draw(int leftPos, int rightPos, int ballX, int ballY);

int main() {
    int ballX = 1, ballY = 1, ballVX = 1, ballVY = 1, leftY = 1, rightY = 1;
    char key = 0;
    draw(leftY, rightY, ballX, ballY);
    while (1) {
        key = getchar();
        switch (bounce(ballX + ballVX ,ballY + ballVY,leftY,rightY))
        {
        case 'l':
            ballVX -= ballVX;
            break;        
        case 'r':
            ballVX -= ballVX;
            break;
        case 'u':
            ballVY -= ballVY;            
            break;
        case 'd':
            ballVY -= ballVY;            
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

int updateBallPos(int ballPos, int ballVelocity) { return ballPos + ballVelocity; }

int newRocketPos(int rocket, int direction) {
    if (rocket + direction >= 0 && rocket + direction < 80) rocket += direction;
    if (rocket + direction >= 0 && rocket + direction < 80) rocket += direction;
    return rocket;
}

char bounce(int ballX, int ballY, int leftY, int rightY) {
    if (ballX == LEFT_BOUND && ballY <= leftY - 1 && ballY >= leftY + 1) return 'l';
    if (ballX == RIGHT_BOUND && ballY <= rightY - 1 && ballY >= rightY + 1) return 'l';
    if (ballY == UP_BOUND) return 'u';
    if (ballY == DOWN_BOUND) return 'd';
    return ' ';
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