#include "utils.h"

#include <stdlib.h>

int mod(const int a, const int b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}

int randint(const int min, const int max) {
	return min + rand() % (max-min+1);
}
