#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "ansicodes.h"
#include "map.h"
#include "utils.h"

int showMenu(const char* text, int numChoices, const char* choices[]) {
    int choice = 0;
	printf(CLEARSCREEN);
    while (1) {
		printf(HOME);
        
        printf("===========================================\n");
		puts(text);
        printf("===========================================\n");

		for (int c = 0; c < numChoices; ++c) {
			if (choice == c) printf(INVERSE);
			printf("   %s   \n", choices[c]);
			printf(RESET);
		}

        printf("============================================\n");
        printf("w/k = move up, s/j = move down\n");
		fflush(stdout);

		switch (getch()) {
			case 'k':
			case 'w':
				choice = mod(choice-1, numChoices);
				break;
			case 'j':
			case 's':
				choice = mod(choice+1, numChoices);
				break;
			case ' ':
			case 13:
				return choice;
		}
    }
}

int inputNumber(const char* text, bool clear) {
	if (clear) {
		printf(CLEARSCREEN);
		printf(HOME);
	}
	printf(CUR_VIS);

	int number;

	printf("===========================================\n");
	puts(text);
	printf("===========================================\n");
	printf("> ");
	fflush(stdout);
	if (scanf("%d", &number) != 1) {
		scanf("%*[^\n]");
	}
	getchar();

	printf(CUR_INV);
	return number;
}

void inputString(const char* text, char* string, bool clear) {
	if (clear) {
		printf(CLEARSCREEN);
		printf(HOME);
	}

	printf(CUR_VIS);

	printf("===========================================\n");
	puts(text);
	printf("===========================================\n");
	printf("> ");
	fflush(stdout);
	scanf("%[^\n]", string);
	getchar();

	printf(CUR_INV);
}

void showText(const char* text) {
	printf(CLEARSCREEN);
	printf(HOME);

	printf("===========================================\n");
	puts(text);
	printf("===========================================\n");
	puts("Press any key to continue...");
	fflush(stdout);
	getch();
}
