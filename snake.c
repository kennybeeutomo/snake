#include <stdio.h>
#include <stdlib.h>

#include "snake.h"

Snake initSnake(int length, int x, int y) {
	if (length <= 1) length = 2;

	int capacity = 1024;
	Segment* segments = (Segment*)malloc(capacity * sizeof(Segment));

	int i = length-1;
	segments[i] = (Segment){x++, y, '.', &segments[i-1]};

	for (i--; i > 0; --i) {
		segments[i] = (Segment){x++, y, '#', &segments[i-1]};
	}

	segments[0] = (Segment){x, y, '@', NULL};

	Snake snake = {x, y, segments, right, length, capacity};

	return snake;
}

void moveSnake(Snake* snake, Direction direction) {
	Segment* sg;
	for (sg = &snake->segments[snake->length-1]; sg->next != NULL; --sg) {
		sg->x = sg->next->x;
		sg->y = sg->next->y;
	}

	switch (direction) {
		case right: snake->x++; break;
		case down: snake->y++; break;
		case left: snake->x--; break;
		case up: snake->y--; break;
	}

	sg->x = snake->x;
	sg->y = snake->y;
	snake->direction = direction;
}

void extendSnake(Snake* snake) {
	snake->length++;

	if (snake->length >= snake->capacity) {
		snake->capacity *= 2;
		Segment* newSegments = realloc(snake->segments, snake->capacity * sizeof(Segment));
		snake->segments = newSegments;
	}

	Segment* lastSegment = &snake->segments[snake->length-1];
	*lastSegment = *(lastSegment-1);
	lastSegment->type = '.';
	lastSegment->next = lastSegment-1;
	(lastSegment-1)->type = '#';
}

void freeSnake(Snake* snake) {
	free(snake->segments);
}

void printSnake(Snake* snake) {
	for (int i = 0; i < snake->length; ++i) {
		printf("%c", snake->segments[i].type);
	}
	puts("");
}
