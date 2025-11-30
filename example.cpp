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
    snake.push_back(BodyCell{gameFieldWidth / 2-1, gameFieldHeight / 2});
    snake.push_back(BodyCell{gameFieldWidth / 2-2, gameFieldHeight / 2});


    Direction snakeDirection = Up;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - logo raylib");

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A))
            snakeDirection = Left;
        else if (IsKeyDown(KEY_S))
            snakeDirection = Down;
        else if (IsKeyDown(KEY_D))
            snakeDirection = Right;
        else if (IsKeyDown(KEY_W))
            snakeDirection = Up;

        { // moving snake
            BodyCell nextPosition = snake[0];
            std::cout<<nextPosition.x<<" "<<nextPosition.y<<std::endl;
            if (snakeDirection == Left)
                nextPosition.x += -1;
            else if (snakeDirection == Right)
                nextPosition.x += +1;
            else if (snakeDirection == Up)
                nextPosition.y += +1;
            else if (snakeDirection == Down)
                nextPosition.y += -1;
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

        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    CloseWindow();

    return 0;
}