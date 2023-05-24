#ifndef FOOD_H
#define FOOD_H

#include <random>
#include "raylib.h"

struct Food {
	int positionX;
	int positionY;

	static constexpr int size = 10;

	void spawn();
};

#endif // FOOD_H