#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <vector>

// Building blocks of the Snake
struct Segment {

	int positionX;
	int positionY;

};


// The Snake itself
struct Snake {

	std::vector<Segment> segments;

	static constexpr int size = 10;
	float speedX;
	float speedY;
	float speed;
	int segmentsToGrow;

	Snake();

	// Movement every frame
	void move(int deltaX, int deltaY);

	// Growth when the Snake eats food
	void grow();

	// Drawing the Snake every frame
	void draw();

};

#endif // SNAKE_H