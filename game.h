#pragma once

#include <stdbool.h>

#include "map.h"
#include "snake.h"
#include "leaderboard.h"

typedef struct {
	Map* map;
	Snake* snake;
	bool running;
	int score;
	int steps;
	unsigned seed;
} Game;

Game initGame(Map* map, Snake* snake);
void startGame(Game* game, unsigned seed);
void runGame(Game* game);
void endGame(Game* game);

void getInput(Game* game);

void mapSnake(Game* game);
int moveSnakeOnMap(Game* game, Direction direction);

void addFoods(Game* game, int quantity);
void generateWalls(Game* game, int quantity, int length, int turnChance);

void displayStats(Game* game);
void displayControls();

Record getRecord(Game* game);
