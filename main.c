#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "snake.h"
#include "menu.h"

int main() {
	setvbuf(stdout, NULL, _IOFBF, 4096);

	bool running = true;

	running = showMenu();
	while (running) {
		Map map = initMap(30, 20);
		Snake snake = initSnake(6, 10, 10);
		Game game = {&map, &snake};
		startGame(&game, 1);
		running = showDeathMenu();
	}

	return 0;
}

