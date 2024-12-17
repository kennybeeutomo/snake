#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "ansicodes.h"
#include "map.h"
#include "utils.h"

int showMenu(const char* text, const char* choices[], int numChoices) {
    int choice = 0;
    while (1) {
		printf(CLEARSCREEN);
		printf(HOME);
        
        printf("===========================================\n");
		puts(text);
        printf("===========================================\n");

		for (int c = 0; c < numChoices; ++c) {
			if (choice == c) {
				printf(" > ");
			} else {
				printf("   ");
			}
			puts(choices[c]);
		}

        printf("============================================\n");
        printf("Use 'w/k' or 's/j' keys to navigate.\n");
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

int inputNumber(const char* text) {
	printf(CLEARSCREEN);
	printf(HOME);
	printf(CUR_VIS);

	int number;

	printf("===========================================\n");
	printf("%s\n", text);
	printf("===========================================\n");
	printf("> ");
	fflush(stdout);
	scanf("%d", &number);
	getchar();

	printf(CUR_INV);
	return number;
}
