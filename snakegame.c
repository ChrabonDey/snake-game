#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Use <ncurses.h> on Unix systems
#include <unistd.h> // Only for usleep()

#define WIDTH 20
#define HEIGHT 20

int i, j, score, gameOver;
int x, y, fruitX, fruitY, flag;
int tailX[100], tailY[100];
int nTail;

void setup() {
    gameOver = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    label1:
    fruitX = rand() % WIDTH;
    if (fruitX == 0)
        goto label1;
    label2:
    fruitY = rand() % HEIGHT;
    if (fruitY == 0)
        goto label2;
    score = 0;
}

void draw() {
    system("cls"); // Use "clear" on Unix systems
    for (i = 0; i < WIDTH; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int isTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'a':
                flag = 3;
                break;
            case 'd':
                flag = 4;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            y++;
            break;
        case 3:
            x--;
            break;
        case 4:
            x++;
            break;
        default:
            break;
    }

    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
        gameOver = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        label3:
        fruitX = rand() % WIDTH;
        if (fruitX == 0)
            goto label3;
        label4:
        fruitY = rand() % HEIGHT;
        if (fruitY == 0)
            goto label4;
        score += 10;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        usleep(100000); // Sleep for 100 milliseconds
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
