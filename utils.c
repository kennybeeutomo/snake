#include "utils.h"

#include <stdlib.h>

int mod(const int a, const int b) {
	if (b == 0) return 0;
	return (a % b + b) % b;
}

int randint(const int min, const int max) {
	return min + rand() % (max-min+1);
}

long long powInt(const long long a, const unsigned long long b) {
	long long c = 1;
	for (unsigned long long i = 0; i < b; ++i) {
		c *= a;
	}
	return c;
}
