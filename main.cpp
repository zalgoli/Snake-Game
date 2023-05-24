#include "raylib.h"
#include "Snake.h"
#include "Food.h"
#include <string>

int main(void)
{
    InitWindow(800, 450, "Snake Game");
    SetWindowState(FLAG_VSYNC_HINT);

    bool restart = false;

    do {
        restart = false; // Reset restart flag at the beginning of each game
        Snake mySnake;
        float accumulatedTime = 0;
        float stepTime = 0.1f;

        bool isGameOver = false;
        int segmentsToGrow = 0;

        int snakeSize = 1;

        Food myFood;
        myFood.spawn();

        while (!WindowShouldClose()) {

            float deltaTime = GetFrameTime();
            accumulatedTime += deltaTime;

            // Core logic behind the step-based movement of the snake
            if (accumulatedTime > stepTime && !isGameOver) {
                mySnake.move(mySnake.speedX, mySnake.speedY);
                accumulatedTime -= stepTime;

                if (segmentsToGrow > 0) {
                    mySnake.grow();
                    segmentsToGrow--;
                }

                // Handling key bindings
                if (IsKeyDown(KEY_UP)) mySnake.speedX = 0, mySnake.speedY = mySnake.speed * -1;
                if (IsKeyDown(KEY_DOWN)) mySnake.speedX = 0, mySnake.speedY = mySnake.speed;
                if (IsKeyDown(KEY_LEFT)) mySnake.speedX = mySnake.speed * -1, mySnake.speedY = 0;
                if (IsKeyDown(KEY_RIGHT)) mySnake.speedX = mySnake.speed, mySnake.speedY = 0;

                // When the snake collides with itself
                for (int i = 1; i < mySnake.segments.size(); i++) {
                    if (mySnake.segments[0].positionX == mySnake.segments[i].positionX &&
                        mySnake.segments[0].positionY == mySnake.segments[i].positionY)
                    {
                        isGameOver = true;
                    }
                }

                // When the snake collides with the wall
                if (mySnake.segments[0].positionX < 0 || mySnake.segments[0].positionX > GetScreenWidth() ||
                    mySnake.segments[0].positionY < 0 || mySnake.segments[0].positionY > GetScreenHeight())
                {
                    isGameOver = true;
                }

                // Handling collision of Snake and Food (i.e. "eating")
                Rectangle snakeHead = { mySnake.segments[0].positionX, mySnake.segments[0].positionY, mySnake.size, mySnake.size };
                Rectangle foodRect = { myFood.positionX, myFood.positionY, myFood.size, myFood.size };

                if (CheckCollisionRecs(snakeHead, foodRect))
                {
                    segmentsToGrow++;
                    myFood.spawn();
                    snakeSize += 1;
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Displaying Score
            std::string scoreString = "Snake Size: " + std::to_string(mySnake.segments.size());
            const char* scoreText = scoreString.c_str();

            int fontSize = 20;
            Vector2 scoreTextPosition = { GetScreenWidth() / 2 - MeasureText(scoreText, fontSize) / 2, 10 };
            DrawText(scoreText, scoreTextPosition.x, scoreTextPosition.y, fontSize, DARKBLUE);

            // Handling Game Over text logic
            if (isGameOver) {
                const char* gameOverText = "Game Over!";
                const char* pressR = "Press 'R' to play again.";
                int gameOverFontSize = 50;
                int pressRFontSize = 20;

                // Measuring text width and height
                Vector2 gameOverTextSize = MeasureTextEx(GetFontDefault(), gameOverText, gameOverFontSize, 1);
                Vector2 pressRSize = MeasureTextEx(GetFontDefault(), pressR, pressRFontSize, 1);

                // Printing Game Over text at the exact center of the screen
                DrawText(gameOverText, GetScreenWidth() / 2 - (gameOverTextSize.x / 2), GetScreenHeight() / 2 - (gameOverTextSize.y / 2), gameOverFontSize, RED);
                DrawText(pressR, GetScreenWidth() / 2 - (pressRSize.x / 2) + 10, GetScreenHeight() / 2 - pressRSize.y / 2 + 40, pressRFontSize, RED);

                if (IsKeyPressed(KEY_R)) {
                    restart = true;
                    break;
                }
            }
            // Drawing Game elements
            else {
                mySnake.draw();
                DrawRectangle(myFood.positionX, myFood.positionY, myFood.size, myFood.size, RED);
                DrawFPS(10, 10);
            }

            EndDrawing();
        }
    } while (restart);

    CloseWindow();

    return 0;
}
