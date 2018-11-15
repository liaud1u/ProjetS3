#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

void leftK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix , SDL_Rect & elfPos);
void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix , SDL_Rect &elfPos);
void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix , SDL_Rect & elfPos);
void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix , SDL_Rect & elfPos);
void getPos(SDL_Rect &tilePosition, int &ho, int &ve, int &y, int &x, int &actualX, int &actualY, int &i, int &j,int**mapix, int vertical_decal, int horizontal_decal,SDL_Rect &elfPos);
