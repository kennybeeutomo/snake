#pragma once

#include <stdbool.h>

#define LEADERBOARD_FILE "leaderboard"
#define MAX_NAME_LENGTH 16
#define LEADERBOARD_CAPACITY 1024

typedef struct {
	unsigned seed;
    int score;
	int steps;
    char name[MAX_NAME_LENGTH];
} Record;

typedef struct {
	int capacity;
	int size;
	Record* records;
	bool isSorted;
} Leaderboard;

Leaderboard initLeaderboard();
void writeLeaderboard(Leaderboard leaderboard);
void loadLeaderboard(Leaderboard* leaderboard);
void freeLeaderboard(Leaderboard* leaderboard);
void addRecord(Leaderboard* leaderboard, Record record);
bool compareRecord(const Record* left, const Record* right);
void swapRecord(Record* left, Record* right);
void sortLeaderboard(Leaderboard* leaderboard);
void printRecord(Record record);
int searchRecordSeedNext(Leaderboard* leaderboard, unsigned seed, int from);
int searchRecordSeedPrev(Leaderboard* leaderboard, unsigned seed, int from);
int searchRecordNameNext(Leaderboard* leaderboard, char name[MAX_NAME_LENGTH], int from);
int searchRecordNamePrev(Leaderboard* leaderboard, char name[MAX_NAME_LENGTH], int from);
void showLeaderboard(Leaderboard* leaderboard, int height);
