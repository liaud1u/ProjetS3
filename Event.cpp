#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>

#include "Define.h"
#include "stats.h"
#include "Ennemi.h"
#include "Fonction.h"


void attaqueHeros(int posSourisX, int posSourisY, int xHeros, int yHeros, int attaqueHeros, Ennemi* tabEnnemis, int tailleTab, int vertical, int horizontal, int ** map, int tailleX, int tailleY,int *stat){
    int i,valX,valY;
    for (i = 0; i < tailleTab; i++){
        if(!tabEnnemis[i].isDead()){
            SDL_Rect rectangleEnnemi = tabEnnemis[i].getPositionPrint(horizontal,vertical);//Get ennemy rectangle
            valX = tabEnnemis[i].getX() ;
            valY = tabEnnemis[i].getY() - 1;
            if (posSourisX >= rectangleEnnemi.x && posSourisX <= rectangleEnnemi.x + rectangleEnnemi.h && posSourisY >= rectangleEnnemi.y && posSourisY <= rectangleEnnemi.y + rectangleEnnemi.w) { //Check if the event is at the ennemy position
                int dist = mini(9999,distance(valX, valY, xHeros+1, yHeros, map,tailleX,tailleY));
                dist = mini(dist,distance(valX, valY, xHeros-1, yHeros, map,tailleX,tailleY));
                dist = mini(dist,distance(valX, valY, xHeros, yHeros+1, map,tailleX,tailleY));
                dist = mini(dist,distance(valX, valY, xHeros, yHeros-1, map,tailleX,tailleY));
                if ( dist <=1){ //Check if distance between ennemy and caracter is good
                    tabEnnemis[i].haveDamage(attaqueHeros,stat);//Ennemy take damage
                    saveStats("statistiques",stat);
                }
            }
        }
    }
}

void getPos(SDL_Rect &tilePosition, int &ho, int &ve, int &y, int &x, int &actualY, int &actualX, int &i, int &j,int **mapix, int vertical_decal, int horizontal_decal,SDL_Rect &elfPos){
    for (int jb=0;jb<j;jb++){ //Get caracter position
        tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x = ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x =  ve + D_SIZE * ib + x * D_SIZE;
            if(elfPos.x + vertical_decal> tilePosition.x+vertical_decal && elfPos.x < tilePosition.x +50 && elfPos.y +horizontal_decal	 < tilePosition.y + 50 && elfPos.y +horizontal_decal > tilePosition.y){ 
                actualY = jb;
                actualX = ib;
            }
        }
    }
}

void leftK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect & elfPos){
    elfImage.y = 56 * (who*2 +1) ; //activate moovement sprite
    elfImage.x = 32 * frame+4*32; 
    int in_tab = actualX >= 0 && actualY >0 && actualX < i && actualY < j;
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,1,50,elfPos); //move left if possible
    if(in_tab && (mapix[actualX][actualY-1]==49 || mapix[actualX][actualY]==49 )){
        ve +=SPEED_EVENT;
    }
}

void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect & elfPos){
    int in_tab = actualX >= 0 && actualY >=0 && actualX < i && actualY+1 < j;
    elfPos.x += 32;
    elfPos.y += 15;
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,32,32,elfPos);

    if(in_tab && (mapix[actualX][actualY+1]==49 || mapix[actualX][actualY]==49 )){
        ve -=SPEED_EVENT;//move right if possible

        }
         elfPos.x -= 32;
         elfPos.y -= 15;
        elfImage.y = 56 * (who*2) ; //activate moovement sprite
        elfImage.x = 32 * frame+4*32;
}

void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect &elfPos){
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,0,30,elfPos);
    int in_tab = actualX > 0 && actualY >=0 && actualX < i && actualY < j;
    elfImage.x = 32 * frame+4*32; // moove up if possible
    if(in_tab &&((mapix[actualX][actualY] !=56&&(mapix[actualX-1][actualY] == 49||mapix[actualX-1][actualY] ==56||((mapix[actualX+1][actualY-1]!=97 || (mapix[actualX+1][actualY-1]==97&&((ho<0?50000+ho:ho)%50<40 ||( ((abs(ve<0?50000+ve:ve)%50>10))&&(abs(ve<0?50000+ve:ve)%50<40))) ))&&mapix[actualX-1][actualY] != 56 && (mapix[actualX-1][actualY] == 49 || mapix[actualX][actualY] == 49 ||mapix[actualX-1][actualY]==99||(mapix[actualX-1][actualY]==51 && abs(ve<0?50+ve:ve)%50-25>45)||mapix[actualX-1][actualY]==55|| mapix[actualX-1][actualY] ==51  )))))){
        ho -=SPEED_EVENT;
    } // activate moovement sprite
}

void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect & elfPos){
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,0,10,elfPos);
    int in_tab = actualX >= 0 && actualY >=0 && actualX+1 < i && actualY < j;
    
    if(in_tab &&((mapix[actualX+1][actualY+1]!=100 || ( (mapix[actualX+1][actualY+1]==100 )&&((ho<0?50000+ho:ho)%50<30||( ((abs(ve<0?50000+ve:ve)%50>10))&&(abs(ve<0?50000+ve:ve)%50<=35))) ))&&(mapix[actualX+1][actualY] == 49 ||mapix[actualX+1][actualY]==51||mapix[actualX+1][actualY]==51||((ho<0?50000+ho:ho)%50<26&&mapix[actualX+1][actualY] == 52)))){
        ho+=SPEED_EVENT; //if it possible moove down
    }
    elfImage.x = 32 * frame + 4*32; //Moove sprite
}
