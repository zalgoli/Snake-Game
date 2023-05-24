#include "Snake.h"
#include "raylib.h"
#include <vector>

void Snake::move(int deltaX, int deltaY) {
	for (int i = segments.size() - 1; i > 0; i--) {
		segments[i].positionX = segments[i - 1].positionX;
		segments[i].positionY = segments[i - 1].positionY;
	}

	segments[0].positionX += deltaX;
	segments[0].positionY += deltaY;
}


void Snake::grow() {
    int newX, newY;

    if (segments.size() == 1) {
        // If the snake has only one segment, generate the new segment
        // in the opposite direction of its current movement.
        newX = segments[0].positionX - speedX;
        newY = segments[0].positionY - speedY;
    }
    else {
        int lastIndex = segments.size() - 1;
        int secondLastIndex = segments.size() - 2;

        // Determine the direction of the last segment
        int deltaX = segments[lastIndex].positionX - segments[secondLastIndex].positionX;
        int deltaY = segments[lastIndex].positionY - segments[secondLastIndex].positionY;

        // Generate the new segment at the end of the snake based on the direction
        newX = segments[lastIndex].positionX + deltaX;
        newY = segments[lastIndex].positionY + deltaY;
    }

    segments.push_back({ newX, newY });
}


void Snake::draw() {
	for (const auto& segment : segments) {
		DrawRectangle(segment.positionX, segment.positionY, size, size, DARKBLUE);
	}
}


Snake::Snake() {
	
	segments.push_back({ GetScreenWidth() / 2, GetScreenHeight() / 2 });
	speedX = 0;
	speedY = 0;
	speed = 10;

}
