#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50

void getPos(SDL_Rect &tilePosition, int &ho, int &ve, int &y, int &x, int &actualY, int &actualX, int &i, int &j){
	for (int jb=0;jb<j;jb++){ //récuperation des coord du perso
        tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
        tilePosition.x = ve + x * D_SIZE;
        for(int ib=0;ib<i;ib++){
            tilePosition.y = - ho + D_SIZE * jb + y * D_SIZE;
            tilePosition.x =  ve + D_SIZE * ib + x * D_SIZE;
            if(tilePosition.x  <= LARGEUR/2 +16 && tilePosition.x +50 +16 >= LARGEUR/2 && tilePosition.y <= HAUTEUR/2 -28	&& tilePosition.y  >= HAUTEUR /2 +20 -28){ 
                actualY = jb;
                actualX = ib;
            }
        }
    }
    printf("x: %d y: %d\n", actualX, actualY);
}

void leftK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    elfImage.y = 56 * (who*2 +1) ; //activation du sprite de déplacement
    elfImage.x = 32 * frame+4*32; 
  getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j);
    //Incrementation si le perso est sur une case autorisée
  
    if(actualY > 0 && (mapix[actualX][actualY-1] == 49 || mapix[actualX][actualY] == 49)){
        ve +=1;
    }
}

void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j);
if(actualY < j &&( mapix[actualX][actualY+1] == 49 || mapix[actualX][actualY] == 49)){
        ve -=1;//Incrementation si le joueur est sur une case autorisée
   

}
    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
    elfImage.x = 32 * frame+4*32;
}

void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j);
    elfImage.x = 32 * frame+4*32; // activation du sprite de déplacement
    if(actualX > 0 && (mapix[actualX-1][actualY] == 49 || mapix[actualX][actualY] == 49)){
        ho -=1;

    } // Incrementation si le perso est dans les cases autorisée
     
}

void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j);
    if(actualX < i && (mapix[actualX+1][actualY] == 49 || mapix[actualX][actualY] == 49)){
        ho+=1; //Si le joueur est sur une case autorisée on incremente


    }
    elfImage.x = 32 * frame + 4*32; //Mise a jour du sprite 
}
