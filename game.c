#include "game.h"
#include "ansicodes.h"
#include "leaderboard.h"
#include "map.h"
#include "menu.h"
#include "snake.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

void initGame(Game* game, Map* map, Snake* snake, unsigned seed) {
	game->score = 0;
	game->steps = 0;
	game->lastAction = 0;
	game->running = false;
	game->map = map;
	game->snake = snake;
	strcpy(game->saveName, AUTOSAVE_NAME);
	setGameSeed(game, seed);
}

void generateGame(Game* game) {
	mapSnake(game);
	generateWalls(game, 30, 8, 20);
	addFoods(game, 5);
}

void setGameSeed(Game* game, unsigned seed) {
	if (seed == 0) {
		srand(time(NULL));
		seed = (rand() * rand()) % 1000000;
	}
	srand(seed);
	game->seed = seed;
}

void runGame(Game* game, bool isLoaded) {
	if (isLoaded) {
		game->save = fopen(game->saveName, "ab");
	} else {
		game->save = fopen(game->saveName, "wb");
		fwrite(&game->seed, sizeof(game->seed), 1, game->save);
	}
	setvbuf(game->save, NULL, _IOFBF, 4096);

	game->running = true;
	while (game->running) {
		gameTick(game);
		displayMap(game->map);
		displayStats(game);
		getInput(game);
		if (game->lastAction != 0 && game->running) {
			fwrite(&game->lastAction, sizeof(char), 1, game->save);
		}
		mapSnake(game);
	}

	fflush(game->save);
	fclose(game->save);

	endGame(game);
}

void endGame(Game* game) {
	freeMap(game->map);
	freeSnake(game->snake);

	printf(CLEARSCREEN);
	printf(HOME);
	fflush(stdout);
}

void pause(Game* game) {
	int choice = showMenu(
		"        GAME PAUSED",
		2, (const char*[]){
			"Resume",
			"Quit",
		});

	switch (choice) {
		case 0: // Resume
			break;
		case 1: // Quit
			game->running = false;
			break;
	}
}

void loadSeed(Game* game, FILE* file) {
	unsigned seed;
	fread(&seed, sizeof(unsigned), 1, file);
	setGameSeed(game, seed);
}

void traceInput(Game* game, FILE* file, bool slowMode) {
	char keystroke;
	game->running = true;
	while (game->running && fread(&keystroke, sizeof(char), 1, file) != 0) {
		gameTick(game);
		if (slowMode) {
			displayMap(game->map);
			displayStats(game);
			getch();
		}
		parseInput(game, keystroke);
		mapSnake(game);
	}
}

int parseInput(Game* game, char key) {
	int retVal = 0;
	bool isAnAction = false;
	switch (key) {
		case 'h': case 'a':
			retVal = moveSnakeOnMap(game, left);
			isAnAction = true;
			break;
		case 'j': case 's':
			retVal = moveSnakeOnMap(game, down);
			isAnAction = true;
			break;
		case 'k': case 'w':
			retVal = moveSnakeOnMap(game, up);
			isAnAction = true;
			break;
		case 'l': case 'd':
			retVal = moveSnakeOnMap(game, right);
			isAnAction = true;
			break;
		case 'q': case 'p':
			pause(game);
			break;
		default:
			retVal = 1;
			displayControls();
			fflush(stdout);
			printf(UP UP UP ERASE_DOWN);
			break;
	}

	if (isAnAction) {
		game->steps++;
		game->lastAction = key;
	} else {
		game->lastAction = 0;
	}

	return retVal;
}

void getInput(Game* game) {
	bool invalid = false;
	char key;
	do {
		key = getch();
		invalid = parseInput(game, key);
	} while (invalid);
}

int loadGame(Game* game, const char* fileName, bool slowMode) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		showText("        SAVE FILE DOESN'T EXIST");
		return 1;
	}

	if (strcmp(fileName, AUTOSAVE_NAME) != 0) {
		strcpy(game->saveName, fileName);
	}

	loadSeed(game, file);
	generateGame(game);
	traceInput(game, file, slowMode);

	fclose(file);
	return 0;
}

int loadGameUI(Game* game) {
	char fileName[SAVENAME_SIZE];
	inputString(
		"        INPUT SAVE FILE TO LOAD",
		fileName, 1);
	return loadGame(game, fileName, false);
}

void handleSnakeCollision(Game* game) {
	switch (mapGetChar(game->map, game->snake->x, game->snake->y)) {
		case '*':
			game->score++;
			extendSnake(game->snake);
			addFoods(game, 1);
			break;
		case 0: case '#': case ' ':
			game->running = false;
			freopen(game->saveName, "wb", game->save);
			fwrite(&game->seed, sizeof(unsigned), 1, game->save);
			fflush(game->save);
			break;
	}
}

void gameTick(Game* game) {
	if (game->steps % 10 == 0) {
		addFoods(game, 1);
	}
}

int moveSnakeOnMap(Game* game, Direction direction) {
	if ((direction + 2) % 4 == game->snake->direction) return 1;
	moveSnake(game->snake, direction);
	handleSnakeCollision(game);
	return 0;
}

void mapSnake(Game* game) {
	Segment* sg;
	for (int i = 0; i < game->snake->length; ++i) {
		sg = &game->snake->segments[i];
		mapSetChar(game->map, sg->x, sg->y, sg->type);
	}
}

void addFoods(Game* game, int quantity) {
	for (int q = 0; q < quantity; ++q) {
		int x, y;
		if (mapRandomCharPos(game->map, &x, &y, ".", 1, " ")) continue;
		mapSetChar(game->map, x, y, '*');
	}
}

void generateWalls(Game* game, int quantity, int length, int turnChance) {
	for (int q = 0; q < quantity; ++q) {
		int x, y;
		mapRandomCharPos(game->map, &x, &y, ".", 1, " ");
		Direction direction = rand() % 4;

		for (int l = 0; l < length; ++l) {
			mapReplaceChar(game->map, x, y, ' ', ".");

			switch (direction) {
				case right: x++; break;
				case down: y++; break;
				case left: x--; break;
				case up: y--; break;
			}

			if ((rand() % 100) < turnChance) {
				direction = rand() % 2 ?
					mod(direction + 1, 4) :
					mod(direction - 1, 4);
			}
		}
	}
}

void displayStats(Game* game) {
	printf("Score : %d\n", game->score);
	printf("Steps : %d\n", game->steps);
	printf("Seed  : %u\n", game->seed);
	printf("Snake : %d ", game->snake->length);
	printSnake(game->snake);
	printf("\n");
	fflush(stdout);
}

void displayControls() {
	printf(
		"Controls:\n"
		"wasd or hjkl : move snake\n"
		"q            : quit\n"
	);
}

Record getRecord(Game* game) {
	Record record = {0};
	record.seed = game->seed;
	record.score = game->score;
	record.steps = game->steps;
	return record;
}
