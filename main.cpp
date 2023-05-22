#include "raylib.h"

#include <vector>
#include <random>

struct Segment {
    int positionX;
    int positionY;
};

struct Snake {
    std::vector<Segment> segments;
    float speedX;
    float speedY;

    // The snake's size is now fixed, as every segment has the same size
    static constexpr int sizeX = 20;
    static constexpr int sizeY = 20;

    // Constructor to initialize the snake with one segment in the middle of the screen
    Snake() {
        segments.push_back({ GetScreenWidth() / 2, GetScreenHeight() / 2 });
        speedX = 10;
        speedY = 0;
    }

    void move(int deltaX, int deltaY) {
        for (int i = segments.size() - 1; i > 0; i--) {
            segments[i].positionX = segments[i - 1].positionX;
            segments[i].positionY = segments[i - 1].positionY;
        }

        segments[0].positionX += deltaX;
        segments[0].positionY += deltaY;
    }

    void grow() {
        segments.push_back({ segments.back().positionX,segments.back().positionY });
        segments.push_back({ segments.back().positionX,segments.back().positionY });
    }

    void draw() {
        for (const auto& segment : segments) {
            DrawRectangle(segment.positionX, segment.positionY, sizeX, sizeY, DARKBLUE);
        }
    }
};

struct Food {
    int positionX;
    int positionY;

    void Spawn() {
        DrawRectangle(positionX, positionY, 20, 20, RED);
    }
};


int main(void)
{
    InitWindow(800, 450, "Snake Game");
    SetWindowState(FLAG_VSYNC_HINT);

    // Instantiating the Snake
    Snake mySnake;

    // Instantiating the Food
    Food myFood;
    std::random_device rd;
    std::mt19937 engine(rd());

    // Create distributions for Food spawning place
    std::uniform_int_distribution<int> distribution1(0, GetScreenHeight() / 5);
    std::uniform_int_distribution<int> distribution2(0, GetScreenWidth() / 5);

    // Generate random numbers
    int randomHeight = distribution1(engine);
    int randomWidth = distribution2(engine);

    myFood.positionX = randomWidth * 5;
    myFood.positionY = randomHeight * 5;

    float stepTime = 0.15f;
    float accumulatedTime = 0.0f;

    while (!WindowShouldClose())
    {

        float deltaTime = GetFrameTime();

        accumulatedTime += deltaTime;

        if (accumulatedTime > stepTime) {
            mySnake.move(mySnake.speedX, mySnake.speedY);
            accumulatedTime -= stepTime;
        }

        // Moving UP
        if (IsKeyPressed(KEY_UP)) {
            mySnake.speedX = 0;
            mySnake.speedY = -20;
        }

        // Moving DOWN
        if (IsKeyPressed(KEY_DOWN)) {
            mySnake.speedX = 0;
            mySnake.speedY = 20;
        }

        // Moving LEFT
        if (IsKeyPressed(KEY_LEFT)) {
            mySnake.speedX = -20;
            mySnake.speedY = 0;
        }

        // Moving RIGHT
        if (IsKeyPressed(KEY_RIGHT)) {
            mySnake.speedX = 20;
            mySnake.speedY = 0;
        }

        if (CheckCollisionRecs({ (float)mySnake.segments[0].positionX, (float)mySnake.segments[0].positionY, (float)mySnake.sizeX, (float)mySnake.sizeY },
            { (float)myFood.positionX, (float)myFood.positionY, 20.0f, 20.0f }))
        {
            // Generate new random numbers
            int randomHeight = distribution1(engine);
            int randomWidth = distribution2(engine);

            myFood.positionX = randomWidth * 5;
            myFood.positionY = randomHeight * 5;

            mySnake.grow();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);
        mySnake.draw();
        myFood.Spawn();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
