#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

void loadStats(char const * file,int *stats);
void resetStats(char const * file);
void saveStats(char const * file, int *stats);
void printStats(int * stats);
