#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "ansicodes.h"
#include "map.h"

void showMenu() {
    int choice = 0;
    char key;
    while (1) {
		printf(CLEARSCREEN);
        
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

        key = getch(); 
        if (key == 'w') {  
            choice = 0;
        } else if (key == 's') { 
            choice = 1;
        } else if (key == 13) { 
            if (choice == 0) {
                break;
            } else if (choice == 1) {
                exit(0);
            }
        }
    }
}
