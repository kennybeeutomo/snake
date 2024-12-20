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

// File handling
void writeLeaderboard(Leaderboard leaderboard);
void loadLeaderboard(Leaderboard* leaderboard);
void freeLeaderboard(Leaderboard* leaderboard);

// Management
void addRecord(Leaderboard* leaderboard, Record record);
void removeRecord(Leaderboard* leaderboard, int index);

// Sorting
bool compareRecord(const Record* left, const Record* right);
void swapRecord(Record* left, Record* right);
void sortLeaderboard(Leaderboard* leaderboard);

// Searching
bool recordContains(Record* record, char search[MAX_NAME_LENGTH]);
int searchNext(Leaderboard* leaderboard, char search[MAX_NAME_LENGTH], int from);
int searchPrev(Leaderboard* leaderboard, char search[MAX_NAME_LENGTH], int from);

// UI
void showLeaderboardControls();
void printRecord(Record record);
void showLeaderboard(Leaderboard* leaderboard, int height);
