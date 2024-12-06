#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ansicodes.h"
#include "game.h"
#include "snake.h"
#include "menu.h"

int main() {
	printf(CUR_INV);
	setvbuf(stdout, NULL, _IOFBF, 4096);

	bool running = showMenu() == 0;
	while (running) {
		Map map = initMap(30, 20);
		Snake snake = initSnake(3, 10, 10);
		Game game = initGame(&map, &snake);
		startGame(&game, 0);
		running = showDeathMenu() == 0;
	}

	printf(CUR_VIS);
	return 0;
}

