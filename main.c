#include <stdio.h>
#include <conio.h>

#include "ansicodes.h"
#include "game.h"
#include "snake.h"
#include "menu.h"
#include "leaderboard.h"
#include "utils.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20
#define SNAKE_LENGTH 3
#define SNAKE_X MAP_WIDTH/2
#define SNAKE_Y MAP_HEIGHT/2
#define LEADERBOARD_HEIGHT 18

static Leaderboard leaderboard;
static Map map;
static Snake snake;
static Game game;

static bool running = true;
static unsigned seed = 0;
static unsigned lastSeed = 0;

int showWelcome() {
	return showMenu(
		"                               \n"
		"                               \n"
		"           W E L C O M E    T O\n"
		"           S N A K E    G A M E\n"
		"                               \n",
		5, (const char*[]){
			"Start Game",
			"Change Seed",
			"Leaderboard",
			"Credits",
			"Quit"});
}

int showGameOver() {
	char gameover[256];
	float efficiency = (float)game.score / game.steps * 100;
	sprintf(gameover,
		 "           G A M E   O V E R          \n\n"
		 "      Seed       : %d                       \n"
		 "      Score      : %d                       \n"
		 "      Steps      : %d                       \n"
		 "      Efficiency : %.2f%%                   \n",
		 game.seed, game.score, game.steps, efficiency);

	return showMenu(gameover, 4, (const char*[]){
		"Try Again",
		"Main Menu",
		"Save to Leaderboard",
		"Quit"});
}

unsigned inputSeed() {
	char text[128];
	sprintf(text, "CHANGE SEED\n"
		 "- enter 0 for random\n"
		 "- current seed: %d\n"
		 "- last seed: %d\n"
		 "- must be a number\n"
		 "- input -1 to cancel",
		 seed, lastSeed);

	return inputNumber(text, 1);
}

void showCredits() {
	showText(
		"              CREDITS               \n"
		"                                    \n"
		"  - Kenny Bee Utomo                 \n"
		"  - Wesley Sumedha Deano            \n"
		"  - Raden Alexander Christianace    \n"
	);
}

int main() {
	printf(CUR_INV);
	setvbuf(stdout, NULL, _IOFBF, 4096);

	leaderboard = initLeaderboard();
	loadLeaderboard(&leaderboard);

	while (running) {
		int choice = showWelcome();

		switch (choice) {
			case 0:; // Start Game
				int option;
				do {
					map = initMap(MAP_WIDTH, MAP_HEIGHT);
					snake = initSnake(SNAKE_LENGTH, SNAKE_X, SNAKE_Y);
					game = initGame(&map, &snake);
					startGame(&game, seed);

					lastSeed = game.seed;

					Record record = getRecord(&game);

					option = showGameOver();

					if (option == 0) { // Try Again
						seed = lastSeed;
					}

					if (option == 1) { // Main Menu
						seed = 0;
					}

					if (option == 2) { // Save to Leaderboard
						inputString(
							"        Please enter your name        ",
							record.name, 1);

						addRecord(&leaderboard, record);
					}

					if (option == 3) { // Quit
						running = false;
					}
				} while (option == 0);

				break;
			case 1:; // Change Seed
				unsigned newSeed = inputSeed();
				if (newSeed != -1u) {
					seed = newSeed;
				}

				break;
			case 2: // Leaderboard
				if (!leaderboard.isSorted) {
					sortLeaderboard(&leaderboard);
				}

				showLeaderboard(&leaderboard, LEADERBOARD_HEIGHT);
				break;
			case 3: // Credits
				showCredits();
				break;
			case 4: // Quit
				running = false;
				break;
		}
	}

	writeLeaderboard(leaderboard);
	freeLeaderboard(&leaderboard);

	printf(CUR_VIS);
	return 0;
}

