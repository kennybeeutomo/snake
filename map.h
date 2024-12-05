#pragma once

#include <stdbool.h>

typedef struct {
	int width;
	int height;
	char** data;
} Map;

Map initMap(int width, int height);
void displayMap(Map* map);
void freeMap(Map* map);
bool isInside(Map* map, int x, int y);

void clearScreen();
void home();
void reset();
