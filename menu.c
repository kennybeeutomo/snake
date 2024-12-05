#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "ansicodes.h"
#include "map.h"

int showMenu() {
    int choice = 0;
    char key;
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

        key = getch(); 
        if (key == 'w') {  
            choice = 0;
        } else if (key == 's') { 
            choice = 1;
        } else if (key == 13) { 
            if (choice == 0) {
				return 1;
            } else if (choice == 1) {
				return 0;
            }
        }
    }
}

int showDeathMenu() {
    int choice = 0;
    char key;
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

        key = getch();
        if (key == 'w') {
            choice = 0;
        } else if (key == 's') {
            choice = 1;
        } else if (key == 13) {
            if (choice == 0) {
				return 1;
            } else if (choice == 1) {
                // showLeaderboard();
                return 0; 
            }
        }
    }
}

