#include "game.h"
#include "ansicodes.h"
#include "leaderboard.h"
#include "map.h"
#include "snake.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

Game initGame(Map* map, Snake* snake) {
	Game game;
	game.map = map;
	game.snake = snake;
	game.running = false;
	return game;
}

void startGame(Game* game, unsigned seed) {
	if (seed == 0) {
		srand(time(NULL));
		seed = (rand() * rand()) % 1000000;
	}
	srand(seed);

	game->seed = seed;
	game->score = 0;
	game->steps = 0;

	runGame(game);
}

void runGame(Game* game) {
	game->running = true;

	mapSnake(game);
	generateWalls(game, 30, 8, 20);
	addFoods(game, 5);

	while (game->running) {
		if (game->steps % 10 == 0) {
			addFoods(game, 1);
		}
		displayMap(game->map);
		displayStats(game);
		getInput(game);
		mapSnake(game);
		game->steps++;
	}

	endGame(game);
}

void endGame(Game* game) {
	freeMap(game->map);
	freeSnake(game->snake);

	printf(CLEARSCREEN);
	printf(HOME);
	fflush(stdout);
}

void getInput(Game* game) {
	bool invalid;
	do {
		invalid = false;
		switch (getch()) {
			case 'h': case 'a':
				invalid = moveSnakeOnMap(game, left);
				break;
			case 'j': case 's':
				invalid = moveSnakeOnMap(game, down);
				break;
			case 'k': case 'w':
				invalid = moveSnakeOnMap(game, up);
				break;
			case 'l': case 'd':
				invalid = moveSnakeOnMap(game, right);
				break;
			case 'q':
				game->running = false;
				break;
			default:
				invalid = true;
				displayControls();
				fflush(stdout);
				printf(UP UP UP ERASE_DOWN);
				break;
		}
	} while (invalid);
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
