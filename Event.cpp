#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50

void getPos(SDL_Rect &tilePosition, int &ho, int &ve, int &y, int &x, int &actualY, int &actualX, int &i, int &j,int **mapix){
    
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
    int in_tab = actualX > 0 && actualY >0 && actualX < i && actualY < j;
    if(in_tab)
        printf("^ %d v %d < %d > %d \n", mapix[actualY-1][actualX],mapix[actualY+1][actualX], mapix[actualY][actualX-1],mapix[actualY][actualX+1]);
}

void leftK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    elfImage.y = 56 * (who*2 +1) ; //activation du sprite de déplacement
    elfImage.x = 32 * frame+4*32; 
    int in_tab = actualX >= 0 && actualY >0 && actualX < i && actualY < j;
  getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix);
    //Incrementation si le perso est sur une case autorisée
  
    if(in_tab && (mapix[actualX][actualY-1] == 49 || mapix[actualX][actualY] == 49||mapix[actualX][actualY-1] == 52||mapix[actualX][actualY-1] == 57||mapix[actualX][actualY-1] == 54||mapix[actualX][actualY-1] == 55)){
        ve +=1;
    }
}

void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
    int in_tab = actualX >= 0 && actualY >=0 && actualX < i && actualY+1 < j;
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix);
    printf("ve: %d\n", abs(ve)%50);
if(in_tab && ( mapix[actualX][actualY+1] == 49 ||abs(ve)%50<35|| mapix[actualX][actualY+1] ==52|| mapix[actualX][actualY+1] ==56|| mapix[actualX][actualY+1] ==55 )){
        ve -=1;//Incrementation si le joueur est sur une case autorisée
   

}
    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
    elfImage.x = 32 * frame+4*32;
}

void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix);
    int in_tab = actualX > 0 && actualY >=0 && actualX < i && actualY < j;
    elfImage.x = 32 * frame+4*32; // activation du sprite de déplacement
    if(in_tab && (mapix[actualX-1][actualY] == 49 || mapix[actualX][actualY] == 49 ||mapix[actualX-1][actualY]==99||(mapix[actualX-1][actualY]==51 && abs(ve)%50-25>45)||mapix[actualX-1][actualY]==55|| mapix[actualX-1][actualY] ==51  )){
        ho -=1;

    } // Incrementation si le perso est dans les cases autorisée
     
}

void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix);
int in_tab = actualX >= 0 && actualY >=0 && actualX+1 < i && actualY < j;
    if(in_tab &&(mapix[actualX+1][actualY] == 49 ||mapix[actualX+1][actualY]==51||mapix[actualX+1][actualY]==51||abs(ho-25)%50<45||(abs(ho-25)%50<43&&mapix[actualX+1][actualY] == 52))){
        ho+=1; //Si le joueur est sur une case autorisée on incremente


    }
        
    elfImage.x = 32 * frame + 4*32; //Mise a jour du sprite 
}
