#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "map.h"
#include "snake.h"
#include "leaderboard.h"

#define AUTOSAVE_NAME "save"
#define SAVENAME_SIZE 128
#define SEED_LENGTH 6

typedef struct {
	Map* map;
	Snake* snake;
	int running;
	int score;
	int steps;
	unsigned seed;
	char lastAction;
	FILE* save;
	char saveName[SAVENAME_SIZE];
} Game;

void initGame(Game* game, Map* map, Snake* snake, unsigned seed);
void generateGame(Game* game);
void setGameSeed(Game* game, unsigned seed);
void runGame(Game* game, bool isLoaded);
void endGame(Game* game);

void loadSeed(Game* game, FILE* file);
void traceInput(Game* game, FILE* file, bool slowMode);
int parseInput(Game* game, char key);
void getInput(Game* game);

void saveGame(Game* game, const char* fileName);
void saveGameUI(Game* game);
int loadGame(Game* game, const char* fileName, bool slowMode);
int loadGameUI(Game* game);

void gameTick(Game* game);
void mapSnake(Game* game);
int moveSnakeOnMap(Game* game, Direction direction);

void addFoods(Game* game, int quantity);
void generateWalls(Game* game, int quantity, int length, int turnChance);

void displayStats(Game* game);
void displayControls();

Record getRecord(Game* game);
