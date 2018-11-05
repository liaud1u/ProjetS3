#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50

void leftK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    elfImage.y = 56 * (who*2 +1) ; //activation du sprite de déplacement
    elfImage.x = 32 * frame+4*32; 
    for (int jb=0;jb<j;jb++){ //récuperation des coord du perso
        tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x = 75 + ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x = 75 + ve + D_SIZE * ib + x * D_SIZE;
            if(tilePosition.x -40 -50<= LARGEUR/2 && tilePosition.x +50-50 -16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){ 
                actualX = jb;
                actualY = ib;
            }
        }
    }
    //Incrementation si le perso est sur une case autorisée
    if((mapix[actualX][actualY]==49  ||  mapix[actualX][actualY]==50) && mapix[actualX][actualY-1] != 55 && mapix[actualX][actualY-1] != 50 && mapix[actualX][actualY-1] != 52)
    {ve +=1;}
}

void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    for (int jb=0;jb<j;jb++){ //Detection de la case ou est le joueur
        tilePosition.y =  - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x =  ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y = 5 - ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x =  ve + D_SIZE * ib + x * D_SIZE;
            if(tilePosition.x -16+80 <= LARGEUR/2 && tilePosition.x +50 +80-16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 && tilePosition.y + 50 >= HAUTEUR /2){
                actualX = jb;
                actualY = ib;
            }
        }
    }
    if((mapix[actualX][actualY+1]==49||  mapix[actualX][actualY]==51 || mapix[actualX][actualY] == 49) && mapix[actualX][actualY+2] != 55 && mapix[actualX][actualY+2] != 51 && mapix[actualX][actualY+2] != 52 && mapix[actualX][actualY+1] != 50){
        ve -=1;//Incrementation si le joueur est sur une case autorisée
    }
    else{
        printf("Collision : %d",mapix[actualX][actualY]);
    }
    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
    elfImage.x = 32 * frame+4*32;
}

void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    elfImage.x = 32 * frame+4*32; // activation du sprite de déplacement
    for (int jb=0;jb<j;jb++){  // Detection de la case ou le joueur est 
        tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x = ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y =  - ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x =  ve + D_SIZE * ib + x * D_SIZE;
            if(tilePosition.x <= LARGEUR/2 && tilePosition.x +50 >= LARGEUR/2 && tilePosition.y -10 <= HAUTEUR/2 && tilePosition.y + 50-10>= HAUTEUR /2){
                actualX = jb;
                actualY = ib;
            }
        }
    }
    if(mapix[actualX-1][actualY]==49 ||  mapix[actualX-1][actualY] == 51||  mapix[actualX-1][actualY] == 50  )
    {ho -=1;} // Incrementation si le perso est dans les cases autorisée
}

void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    for (int jb=0;jb<j;jb++){ // Detection de la case ou le joueur est 
        tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x =  ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y =  5- ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x = ve + D_SIZE * ib + x * D_SIZE;
            if(tilePosition.x +16 <= LARGEUR/2 && tilePosition.x +50 +16 >= LARGEUR/2 && tilePosition.y +40 <= HAUTEUR/2 && tilePosition.y+40 + 50 >= HAUTEUR /2){
                actualX = jb;
                actualY = ib;
            }
        }
    }
    if(mapix[actualX+1][actualY]==49||  mapix[actualX+1][actualY] == 51||  mapix[actualX+1][actualY] == 50){
        ho+=1; //Si le joueur est sur une case autorisée on incremente
    }
    elfImage.x = 32 * frame + 4*32; //Mise a jour du sprite 
}
