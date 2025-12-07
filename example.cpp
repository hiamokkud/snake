#include "raylib.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
struct BodyCell
{
    int x, y;
};
enum Direction
{
    Up,
    Down,
    Left,
    Right
};
int main(int argc, char **argv)
{
    int gameFieldWidth = 20, gameFieldHeight = 20;
    int screenWidth = 800, screenHeight = 600;

    std::vector<BodyCell> snake;
    snake.push_back(BodyCell{gameFieldWidth / 2, gameFieldHeight / 2});
    snake.push_back(BodyCell{gameFieldWidth / 2 - 1, gameFieldHeight / 2});
    snake.push_back(BodyCell{gameFieldWidth / 2 - 2, gameFieldHeight / 2});

    Direction snakeDirection = Up;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - logo raylib");

    auto counter = std::chrono::steady_clock::now();

    while (!WindowShouldClose())
    {
        bool updateSnake = false;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - counter) > std::chrono::milliseconds(2000))
        {
            updateSnake = true;
            counter = std::chrono::steady_clock::now();
        }

        if (IsKeyDown(KEY_A))
            snakeDirection = Left;
        else if (IsKeyDown(KEY_S))
            snakeDirection = Down;
        else if (IsKeyDown(KEY_D))
            snakeDirection = Right;
        else if (IsKeyDown(KEY_W))
            snakeDirection = Up;

        if (updateSnake)
        {
            { // snake movement
                BodyCell nextPosition = snake[0];
                std::cout << nextPosition.x << " " << nextPosition.y << std::endl;
                if (snakeDirection == Left)
                    nextPosition.x = nextPosition.x == 0 ? gameFieldWidth - 1 : nextPosition.x - 1;
                else if (snakeDirection == Right)
                    nextPosition.x = nextPosition.x == gameFieldWidth - 1 ? 0 : nextPosition.x + 1;
                else if (snakeDirection == Up)
                    nextPosition.y = nextPosition.y == gameFieldHeight - 1 ? 0 : nextPosition.y + 1;
                else if (snakeDirection == Down)
                    nextPosition.y = nextPosition.y == 0 ? gameFieldHeight - 1 : nextPosition.y - 1;
                for (int i = 0; i < snake.size(); i++)
                {
                    BodyCell currentPosition = snake[i];
                    snake[i] = nextPosition;
                    nextPosition = currentPosition;
                }
            }

            ClearBackground(RAYWHITE);
            for (int i = 0; i < snake.size(); i++)
            {
                DrawRectangle(snake[i].x * screenWidth / gameFieldWidth, (gameFieldHeight - snake[i].y - 1) * screenHeight / gameFieldHeight, screenWidth / gameFieldWidth, screenHeight / gameFieldHeight, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}