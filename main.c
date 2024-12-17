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

	int seed = 0;
	bool running = true;
	Map map;
	Snake snake;
	Game game;

	while (running) {
		int choice = showMenu(
			"           W E L C O M E    T O\n"
			"           S N A K E    G A M E",
			(const char*[]){
				"Start Game",
				"Edit Seed",
				"Show Leaderboard",
				"Exit"}
			, 4);

		switch (choice) {
			case 0:
				map = initMap(30, 20);
				snake = initSnake(3, 10, 10);
				game = initGame(&map, &snake);
				startGame(&game, seed);
				running = showMenu(
					"           G A M E   O V E R        ",
				    (const char*[]){"Main Menu", "Exit"}, 2) == 0;
				break;
			case 1:
				seed = inputNumber("Set seed (enter 0 for random)");
				break;
			case 2:
				// showLeaderboard();
				break;
			case 3:
				running = false;
				break;
		}

	}

	printf(CUR_VIS);
	return 0;
}

