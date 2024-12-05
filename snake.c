#include <stdio.h>
#include <stdlib.h>

#include "snake.h"

Snake initSnake(int length, int x, int y) {
	Segment* segments = (Segment*)malloc((length) * sizeof(Segment));

	for (int i = length-1; i > 0; --i) {
		segments[i] = (Segment){x++, y, &segments[i-1]};
	}
	segments[0] = (Segment){x, y, NULL};

	Snake snake = {x, y, segments, right, length};

	return snake;
}

void moveSnake(Snake* snake, Direction direction) {
	for (int i = snake->length-1; i > 0; --i) {
		snake->segments[i].x = snake->segments[i].next->x;
		snake->segments[i].y = snake->segments[i].next->y;
	}

	switch (direction) {
		case right:
			snake->x++;
			break;
		case down:
			snake->y++;
			break;
		case left:
			snake->x--;
			break;
		case up:
			snake->y--;
			break;
		default:
			break;
	}

	snake->segments[0].x = snake->x;
	snake->segments[0].y = snake->y;
	snake->direction = direction;
}

void extendSnake(Snake* snake) {
	snake->segments = (Segment*)realloc(snake->segments, (++snake->length) * sizeof(Segment));
	Segment* lastSegment = &snake->segments[snake->length-1];
	*lastSegment = (Segment){(lastSegment-1)->x, (lastSegment-1)->y, lastSegment-1};
}

void printSnake(Snake* snake) {
	printf("Snake %p:\n", snake);
	printf("At (%d,%d), %d long\n", snake->x, snake->y, snake->length);
	for (int i = snake->length-1; i > 0; --i) {
		printf("Segment %d (%p) at (%d,%d) -> %p\n", i, &snake->segments[i],
		 snake->segments[i].x, snake->segments[i].y, snake->segments[i].next);
	}
	printf("Head %p at (%d,%d) -> %p\n", &snake->segments[0],
		snake->segments[0].x, snake->segments[0].y, snake->segments[0].next);
}

void freeSnake(Snake* snake) {
	free(snake->segments);
}
