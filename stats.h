#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

#include <SDL/SDL_ttf.h>

void loadStats(char const * file,int *stats);
void resetStats(char const * file);
void saveStats(char const * file, int *stats);
void printStats(int * stats);
void affichePiece(int money, SDL_Surface *screen,int frame);
void print(int * stats,SDL_Surface *screen);
