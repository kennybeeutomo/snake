#include "game.h"
#include "ansicodes.h"
#include "map.h"
#include "snake.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void startGame(Game* game, unsigned seed) {
	if (seed == 0) seed = time(NULL);
	srand(seed);
	setvbuf(stdout, NULL, _IOFBF, 4096);
	printf(CLEARSCREEN);
	game->score = 0;
	game->steps = 0;
	runGame(game);
}

void runGame(Game* game) {
	game->running = true;
	mapSnake(game);
	while (game->running) {
		if (game->steps % 10 == 0) {
			addFood(game);
			addSpike(game, 3);
			addSpike(game, 3);
			addSpike(game, 3);
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
			case 'h':
				if (game->snake->direction != right)
					moveSnakeOnMap(game, left);
				else
					invalid = true;
				break;
			case 'j':
				if (game->snake->direction != up)
					moveSnakeOnMap(game, down);
				else
					invalid = true;
				break;
			case 'k':
				if (game->snake->direction != down)
					moveSnakeOnMap(game, up);
				else
					invalid = true;
				break;
			case 'l':
				if (game->snake->direction != left)
					moveSnakeOnMap(game, right);
				else
					invalid = true;
				break;
			case 'q':
				game->running = false;
				break;
			default:
				invalid = true;
				break;
		}
	} while (invalid);
}

char charAtDirection(Game* game, Direction direction) {
	int x = game->snake->x;
	int y = game->snake->y;
	switch (direction) {
		case right: x++; break;
		case down: y++; break;
		case left: x--; break;
		case up: y--; break;
	}
	if (isInside(game->map, x, y)) {
		return game->map->data[y][x];
	} else {
		return 0;
	}
}

void moveSnakeOnMap(Game* game, Direction direction) {
	switch (charAtDirection(game, direction)) {
		case '*':
			game->score++;
			extendSnake(game->snake);
			break;
		case 0:
		case '#':
		case ' ':
			game->running = false;
			return;
	}
	moveSnake(game->snake, direction);
}

void mapSnake(Game* game) {
	int i = game->snake->length-1;
	int x = game->snake->segments[i].x;
	int y = game->snake->segments[i].y;
	game->map->data[y][x] = '.';
	for (i--; i > 0; --i) {
		x = game->snake->segments[i].x;
		y = game->snake->segments[i].y;
		game->map->data[y][x] = '#';
	}
	x = game->snake->segments[i].x;
	y = game->snake->segments[i].y;
	game->map->data[y][x] = '@';
}

void addFood(Game* game) {
	int x, y;
	do {
		x = rand() % game->map->width;
		y = rand() % game->map->height;
	} while (game->map->data[y][x] != '.');

	game->map->data[y][x] = '*';
}

void addSpike(Game* game, int length) {
	int x, y;
	do {
		x = rand() % game->map->width;
		y = rand() % game->map->height;
	} while (game->map->data[y][x] != '.');

	int* p = (rand() % 2)?&x:&y;
	for (int i = 0; i < length; ++i) {
		(*p)++;
		if (isInside(game->map, x, y)) {
			if (game->map->data[y][x] == '.') {
				game->map->data[y][x] = ' ';
			}
		}
	}
}

void displayStats(Game* game) {
	printf("Score: %d\n", game->score);
	printf("Steps: %d\n", game->steps);
	fflush(stdout);
}

