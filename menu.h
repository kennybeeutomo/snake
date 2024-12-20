#pragma once

#include <stdbool.h>
int showMenu(const char* text, int numChoices, const char* choices[]);
int inputNumber(const char* text, bool clear);
void inputString(const char* text, char* string, bool clear);
void showText(const char* text);
void showControls(const char* text, int lines);
