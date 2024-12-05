#pragma once

#include <stdbool.h>

#include "map.h"
#include "snake.h"

typedef struct {
	Map* map;
	Snake* snake;
	bool running;
	int score;
	int steps;
} Game;

void startGame(Game* game, unsigned seed);
void runGame(Game* game);
void endGame(Game* game);

void getInput(Game* game);

void mapSnake(Game* game);
void moveSnakeOnMap(Game* game, Direction direction);

void addFood(Game* game);
void addSpike(Game* game, int length);

void displayStats(Game* game);
