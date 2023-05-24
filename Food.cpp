#include "Food.h"
#include "raylib.h"
#include <random>

void Food::spawn() {

	// Random number generator device
	std::random_device rd;

	// Seeding high-quality generator
	std::mt19937 engine(rd());

	// Creating distribution
	std::uniform_int_distribution<int> distribution1(0, GetScreenWidth() - size);
	std::uniform_int_distribution<int> distribution2(0, GetScreenHeight() - size);

	// Assign random numbers to member variables
	positionX = distribution1(engine);
	positionY = distribution2(engine);

	}
