#pragma once

typedef enum {right, down, left, up} Direction;

typedef struct Segment Segment;
typedef struct Segment {
	int x;
	int y;
	Segment* next;
} Segment;

typedef struct {
	int x;
	int y;
	Segment* segments;
	Direction direction;
	int length; // minimal 6
} Snake;

Snake initSnake(int length, int x, int y);
void moveSnake(Snake* snake, Direction direction);
void extendSnake(Snake* snake);
void printSnake(Snake* snake);
void freeSnake(Snake* snake);
