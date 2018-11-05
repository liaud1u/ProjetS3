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
    return sqrt((x-xb)*(x-xb) + (y-yb)*(y-yb));
}

