#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "ansicodes.h"

Map initMap(int width, int height) {
	char** data = (char**)malloc(height * sizeof(char*));

	for (int i = 0; i < height; ++i) {
		data[i] = (char*)malloc(width * sizeof(char));
		memset(data[i], '.', width * sizeof(char));
	}

	Map map = {width, height, data};

	return map;
}

void displayMap(Map* map) {
	printf(HOME);

	for (int y = 0; y < map->height; ++y) {
		for (int x = 0; x < map->width; ++x) {
			char ch = map->data[y][x];
			switch (ch) {
				case '#': case '@':
					printf(GREENFG);
					break;
				case ' ':
					printf(REDBG);
					break;
				case '*':
					printf(YELLOWFG);
					break;
			}
			printf("%c ", ch);
			printf(RESET);
		}
		printf("\n");
	}

	fflush(stdout);
}

void freeMap(Map* map) {
	for (int i = 0; i < map->height; ++i) {
		free(map->data[i]);
	}
	free(map->data);
}

bool isInside(Map* map, int x, int y) {
	return x >= 0 && x < map->width && y >= 0 && y < map->height;
}

int mapSetChar(Map* map, int x, int y, char ch) {
	if (isInside(map, x, y)) {
		map->data[y][x] = ch;
		return 0;
	} else {
		return 1;
	}
}

int mapReplaceChar(Map* map, int x, int y, char ch, const char* charList) {
	char c = mapGetChar(map, x, y);
	if (strchr(charList, c) != NULL && c != 0) {
		map->data[y][x] = ch;
		return 0;
	} else {
		return 1;
	}
}

char mapGetChar(Map* map, int x, int y) {
	if (isInside(map, x, y)) {
		return map->data[y][x];
	} else {
		return 0;
	}
}

char mapRandomCharPos(Map* map, int* x, int* y, const char* chars, int timeout, const char* excludeChars) {
	int newX, newY, i = 0;
	char ch;

	do {
		newX = rand() % map->width;
		newY = rand() % map->height;
		ch = mapGetChar(map, newX, newY);
		if (strchr(excludeChars, ch) != NULL) i++;
		if (i >= timeout) return ch;
	} while (strchr(chars, ch) == NULL);

	*x = newX;
	*y = newY;
	return 0;
}
