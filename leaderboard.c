#include "leaderboard.h"
#include "ansicodes.h"
#include "game.h"
#include "menu.h"
#include "utils.h"

#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Leaderboard initLeaderboard() {
	Leaderboard leaderboard = {0};
	leaderboard.capacity = LEADERBOARD_CAPACITY;
	return leaderboard;
}

// File Handling
void writeLeaderboard(Leaderboard leaderboard) {
    FILE* file = fopen(LEADERBOARD_FILE, "wb");

    if (file == NULL) {
        perror("Error: Could not open leaderboard file for writing.\n");
		exit(1);
    }

	fwrite(&leaderboard.capacity, sizeof(int), 1, file);
	fwrite(&leaderboard.size, sizeof(int), 1, file);
	fwrite(&leaderboard.isSorted, sizeof(bool), 1, file);
	fwrite(leaderboard.records, sizeof(Record) * leaderboard.size, 1, file);

    fclose(file);
}

void loadLeaderboard(Leaderboard* leaderboard) {
    FILE* file = fopen(LEADERBOARD_FILE, "rb");
    if (file == NULL) {
		fclose(file);
		writeLeaderboard(initLeaderboard());
		loadLeaderboard(leaderboard);
    }

	fread(&leaderboard->capacity, sizeof(int), 1, file);
	fread(&leaderboard->size, sizeof(int), 1, file);
	fread(&leaderboard->isSorted, sizeof(bool), 1, file);

	if (leaderboard->records == NULL) {
		leaderboard->records = malloc(leaderboard->capacity * sizeof(Record));
	}

	fread(leaderboard->records, leaderboard->capacity * sizeof(Record), 1, file);

    fclose(file);
}

void freeLeaderboard(Leaderboard* leaderboard) {
	free(leaderboard->records);
}

// Management
void addRecord(Leaderboard* leaderboard, Record record) {
	if (leaderboard->records == NULL) {
		perror("Null leaderboard\n");
		exit(1);
	}
	if (leaderboard->capacity <= leaderboard->size) {
		leaderboard->capacity *= 2;
		Record* newRecords = realloc(leaderboard->records, leaderboard->capacity * sizeof(Record));
		leaderboard->records = newRecords;
	}
	memcpy(&leaderboard->records[leaderboard->size], &record, sizeof(Record));
	leaderboard->size++;
	leaderboard->isSorted = false;
}

void removeRecord(Leaderboard* leaderboard, int index) {
	leaderboard->size--;
	int i;
	for (i = index; i < leaderboard->size; ++i) {
		memcpy(&leaderboard->records[i], &leaderboard->records[i+1], sizeof(Record));
	}
	memset(&leaderboard->records[i], 0, sizeof(Record));
}

// Sorting
bool compareRecord(const Record* left, const Record* right) {
	if (left->seed != right->seed) return left->seed > right->seed;
	if (left->score != right->score) return left->score < right->score;
	if (left->steps != right->steps) return left->steps > right->steps;
	return false;
}

void swapRecord(Record* left, Record* right) {
	Record temp;
	memcpy(&temp, left, sizeof(Record));
	memcpy(left, right, sizeof(Record));
	memcpy(right, &temp, sizeof(Record));
}

void sortLeaderboard(Leaderboard* leaderboard) {
    for (int i = 0; i < leaderboard->size - 1; i++) {
        for (int j = i + 1; j < leaderboard->size; j++) {
			Record* left = &leaderboard->records[j-1];
			Record* right = &leaderboard->records[j];
            if (compareRecord(left, right)) {
				swapRecord(left, right);
            }
        }
    }
	leaderboard->isSorted = true;
}

// Searching
bool recordContains(Record* record, char search[MAX_NAME_LENGTH]) {
	char seedLeaderboard[SEED_LENGTH+1] = {0};
	itoa(record->seed, seedLeaderboard, 10);
	if (!strcmp(seedLeaderboard, search) || strstr(record->name, search)) {
		return true;
	}
	return false;
}

int searchNext(Leaderboard* leaderboard, char search[MAX_NAME_LENGTH], int from) {
	for (int i = from + 1; i < leaderboard->size; ++i) {
		if (recordContains(&leaderboard->records[i], search)) {
			return i;
		}
	}
	return from;
}

int searchPrev(Leaderboard* leaderboard, char search[MAX_NAME_LENGTH], int from) {
	for (int i = from - 1; i >= 0; --i) {
		if (recordContains(&leaderboard->records[i], search)) {
			return i;
		}
	}
	return from;
}

// UI
void showLeaderboardControls() {
	printf(
		"w/k = move up                 s/j = move down      d/u = move faster\n"
		"f   = search                  ESC = clear search\n"
		"n   = search next             N = search previous\n"
		"r   = remove selected record  q = quit\n"
	);
}

void printRecord(Record record) {
	printf("%-8u %-16s %-5d %-5d %9.2f%%\n",
	       record.seed, record.name, record.score, record.steps,
	       (float)record.score/record.steps * 100);
}

void showLeaderboard(Leaderboard* leaderboard, int height) {
	int choice = 0;
	int lower = 0;
	int upper = height - 1;

	char search[MAX_NAME_LENGTH] = {0};

	printf(CLEARSCREEN);

	int active = true;
	while (active) {
		printf(HOME);

		printf("======================================================\n");
		printf("            L  E  A  D  E  R  B  O  A  R  D            \n");
		printf("======================================================\n");

		if (leaderboard->size == 0) {
			puts("Empty...");
		} else {
			printf("   ");
			printf("%-8s %-16s %-5s %-5s %s\n",
			       "Seed", "Name", "Score", "Steps", "Efficiency");
			printf("======================================================\n");

			for (int i = lower; i <= upper; ++i) {
				if (i >= leaderboard->size) {
					printf("\n");
					continue;
				}
				if (choice == i) {
					printf(INVERSE);
				}

				if (search[0] != 0 && recordContains(&leaderboard->records[i], search)) {
					printf(CYANFG);
				}

				printf("   ");
				printRecord(leaderboard->records[i]);
				printf(RESET);
			}
		}

		printf("=================================================================\n");
		showLeaderboardControls();

		if (search[0] != 0) {
			printf("Searching: %s\n", search);
		}

		fflush(stdout);

		switch (getch()) {
			case 'k':
			case 'w':
				choice = mod(choice-1, leaderboard->size);
				break;
			case 'u':
				choice = mod(choice-5, leaderboard->size);
				break;
			case 'j':
			case 's':
				choice = mod(choice+1, leaderboard->size);
				break;
			case 'd':
				choice = mod(choice+5, leaderboard->size);
				break;
			case 'f':
				inputString("Search", search, 0);
				printf(CLEARSCREEN);
				choice = searchNext(leaderboard, search, choice);
				break;
			case 'n':
				choice = searchNext(leaderboard, search, choice);
				break;
			case 'N':
				choice = searchPrev(leaderboard, search, choice);
				break;
			case '\033':
				memset(search, 0, sizeof(search));
				printf(CLEARSCREEN);
				break;
			case 'r':
				printf("\nDo you want to delete this record? (y/n)\n");
				printRecord(leaderboard->records[choice]);
				fflush(stdout);
				switch (getch()) {
					case 'y': removeRecord(leaderboard, choice);
					case 'n': break;
				}
				printf(CLEARSCREEN);
				break;
			case 'q':
				active = false;
				break;
		}

		if (choice < lower) {
			lower = choice;
			upper = lower + height - 1;
		}
		if (choice > upper) {
			upper = choice;
			lower = upper - height + 1;
		}
	}
}
