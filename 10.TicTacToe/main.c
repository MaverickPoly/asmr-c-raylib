#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

// Constants
const int WIDTH = 1000, HEIGHT = 1000;
const int SIZE = 200;
const int OFFSET = 200;


char board[3][3];
char player = 'X';
char displayText[100] = "Player X's turn.";
bool gameOver = false;


bool isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

bool checkWin() {
    // Horizontal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return true;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ') return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') return true;

    // Vertical
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return true;
        }
    }
    return false;
}

void initializeBoard() {
    for (int i = 0;  i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void handleClick() {
    Vector2 position = GetMousePosition();

    if (
        position.x < OFFSET || position.x > OFFSET + SIZE * 3 ||
        position.y < OFFSET || position.y > OFFSET + SIZE * 3
    ) return;

    int row = (position.x - OFFSET) / SIZE;
    int col = (position.y - OFFSET) / SIZE;

    if (board[row][col] != ' ') return;

    board[row][col] = player;


    if (isDraw()) {
        sprintf(displayText, "It is Draw!");
        gameOver = true;
    } else if (checkWin()) {
        sprintf(displayText, "Player %c WON!", player);
        gameOver = true;
    } else {
        player = player == 'X' ? 'O' : 'X';
        sprintf(displayText, "Player %c's turn.", player);
    }

}

void drawBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x = OFFSET + i * SIZE;
            int y = OFFSET + j * SIZE;

            DrawRectangle(x, y, SIZE, SIZE, RAYWHITE);

            char text[2];
            sprintf(text, "%c", board[i][j]);
            DrawText(text, x + 70, y + 70, 72, BLACK);
        }
    }

    for (int i = 1; i < 3; i++) {
        Vector2 startPos = (Vector2) {OFFSET, OFFSET + i * SIZE};
        Vector2 endPos = (Vector2) {OFFSET + SIZE * 3, OFFSET + i * SIZE};
        DrawLineBezier(startPos, endPos, 2, BLACK);
    }
    for (int i = 1; i < 3; i++) {
        Vector2 startPos = (Vector2) {OFFSET + i * SIZE, OFFSET};
        Vector2 endPos = (Vector2) {OFFSET + i * SIZE, OFFSET + SIZE * 3};
        DrawLineBezier(startPos, endPos, 2, BLACK);
    }
}

void restartGame() {
    gameOver = false;
    initializeBoard();
    player = 'X';
    sprintf(displayText, "Player X's turn.");
}


int main() {
    InitWindow(WIDTH, HEIGHT, "Tic Tac Toe!");
    initializeBoard();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        drawBoard();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !gameOver) {
            handleClick();
        } else if (gameOver) {
            DrawText("Press Spacebar to restart...", OFFSET + 70, OFFSET - 80, 40, BLACK);
            if (IsKeyPressed(KEY_SPACE)) {
                restartGame();
            }
        }
        DrawText(displayText, OFFSET + 100, OFFSET + SIZE * 3 + 50, 48, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
