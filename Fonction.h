#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>


int mini(int x, int y); //Minimum entre deux valeurs
int distance(int x, int y,int xb, int yb, int** mapi, int maxX, int maxY); //Distance entre deux point das un tableau mapi
int collide(SDL_Rect A, SDL_Rect B); //Collision entre deux SDL_Rect A et B 1 Si oui 0 si non. 
SDL_Surface* load(char const* src);
void printMap(int horizontal, int vertical, int jb, int ib, int pos_y, int pos_x, int ** map, SDL_Surface * screen);
void printDeco(int horizontal, int vertical, int jb, int ib, int pos_y, int pos_x, int ** mapdeco, SDL_Surface * screen);
