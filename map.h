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

int mapSetChar(Map* map, int x, int y, char ch);
int mapReplaceChar(Map* map, int x, int y, char ch, const char* charList);
char mapGetChar(Map* map, int x, int y);
int mapRandomCharPos(Map* map, int* x, int* y, const char* chars);
