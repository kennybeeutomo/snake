#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "ansicodes.h"
#include "map.h"
#include "utils.h"

int showMenu() {
    int choice = 0;
    while (1) {
		printf(CLEARSCREEN);
		printf(HOME);
        
        printf("===========================================\n");
        printf("            W  E  L  C  O  M  E            \n");
        printf("    T  O    S  N  A  K  E    G  A  M  E    \n");
        printf("===========================================\n");
        
        if (choice == 0) {
            printf("  > Start Game\n");
            printf("    Exit\n");
        } else {
            printf("    Start Game\n");
            printf("  > Exit\n");
        }

        printf("============================================\n");
        printf("Use 'w' or 's' keys to navigate.\n");
		fflush(stdout);

		switch (getch()) {
			case 'k':
			case 'w':
				choice = mod(choice-1, 2);
				break;
			case 'j':
			case 's':
				choice = mod(choice+1, 2);
				break;
			case ' ':
			case 13:
				return choice;
		}
    }
}

int showDeathMenu() {
    int choice = 0;
    while (1) {
		printf(CLEARSCREEN);
		printf(HOME);

        printf("=============================================\n");
        printf("            Y  O  U    D  I  E  D            \n");
        printf("=============================================\n");

        if (choice == 0) {
            printf("  > Play Again\n");
            printf("    Exit\n");
        } else {
            printf("    Play Again\n");
            printf("  > Exit\n");
        }

        printf("=============================================\n");
        printf("Use 'w' or 's' keys to navigate.\n");
		fflush(stdout);

		switch (getch()) {
			case 'k':
			case 'w':
				choice = mod(choice-1, 2);
				break;
			case 'j':
			case 's':
				choice = mod(choice+1, 2);
				break;
			case ' ':
			case 13:
				return choice;
		}
    }
}

