gcc -Wall -Wextra -std=c11 -c snake.c
gcc -Wall -Wextra -std=c11 -c map.c
gcc -Wall -Wextra -std=c11 -c game.c
gcc -Wall -Wextra -std=c11 -c menu.c
gcc -Wall -Wextra -std=c11 -c leaderboard.c
gcc -Wall -Wextra -std=c11 -c utils.c
gcc -Wall -Wextra -std=c11 -c main.c
gcc -Wall -Wextra -std=c11 snake.o map.o game.o menu.o leaderboard.o utils.o main.o -o snake.exe
