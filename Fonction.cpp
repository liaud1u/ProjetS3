#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Fonction.h"

int mini(int x, int y){
    if (x>y)
        return y;
    return x;
}


int distance(int x, int y,int xb, int yb, int** mapi, int maxX, int maxY){
    return abs(xb-x)+abs(yb-y);
}

int collide(SDL_Rect A, SDL_Rect B){
    //Tests de collision
    if( A.y + A.h<= B.y )
    {
        return false;
    }
 
    if( A.y >= B.y + B.h )
    {
        return false;
    }
 
    if( A.x + A.w <= B.x )
    {
        return false;
    }
 
    if( A.x >= B.x + B.w )
    {
        return false;
    }
 
    //Si conditions collision detectee
    return true;
}
