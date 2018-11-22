#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#define HAUTEUR 500
#define LARGEUR 900
#define D_SIZE 50
#define SPEED 2

void getPos(SDL_Rect &tilePosition, int &ho, int &ve, int &y, int &x, int &actualY, int &actualX, int &i, int &j,int **mapix, int vertical_decal, int horizontal_decal,SDL_Rect &elfPos){
    
  for (int jb=0;jb<j;jb++){ //récuperation des coord du perso
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
    elfImage.y = 56 * (who*2 +1) ; //activation du sprite de déplacement
    elfImage.x = 32 * frame+4*32; 
    int in_tab = actualX >= 0 && actualY >0 && actualX < i && actualY < j;
 getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,1,50,elfPos);
    //Incrementation si le perso est sur une case autorisée

    if(in_tab && (mapix[actualX][actualY-1]==49 || mapix[actualX][actualY]==49 )){
        ve +=SPEED;
    }
}

void rightK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect & elfPos){
    int in_tab = actualX >= 0 && actualY >=0 && actualX < i && actualY+1 < j;
    getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,32,32,elfPos);
if(in_tab && (mapix[actualX+1][actualY+1]!=100 || (mapix[actualX+1][actualY+1]==100 &&
    ((ho<0?50000+ho:ho)%50<30 || (abs(ve<0?50000+ve:ve)%50>10 &&
     (abs(ve<0?50000+ve:ve)%50)<35)))) && 
    ( mapix[actualX][actualY+1] == 49 ||abs(ve<0?50000+ve:ve)%50>15|| mapix[actualX][actualY+1] ==52|| mapix[actualX][actualY+1] ==56|| mapix[actualX][actualY+1] ==55 )){
        ve -=SPEED;//Incrementation si le joueur est sur une case autorisée


}
    elfImage.y = 56 * (who*2) ; //Mise a jour des sprites ( perso en mouvement ) 
    elfImage.x = 32 * frame+4*32;
}

void upK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect &elfPos){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,0,30,elfPos);
    int in_tab = actualX > 0 && actualY >=0 && actualX < i && actualY < j;
    elfImage.x = 32 * frame+4*32; // activation du sprite de déplacement
    if(in_tab &&((mapix[actualX][actualY] !=56&&(mapix[actualX-1][actualY] == 49||mapix[actualX-1][actualY] ==56||((mapix[actualX+1][actualY-1]!=97 || (mapix[actualX+1][actualY-1]==97&&((ho<0?50000+ho:ho)%50<40 ||( ((abs(ve<0?50000+ve:ve)%50>10))&&(abs(ve<0?50000+ve:ve)%50<40))) ))&&mapix[actualX-1][actualY] != 56 && (mapix[actualX-1][actualY] == 49 || mapix[actualX][actualY] == 49 ||mapix[actualX-1][actualY]==99||(mapix[actualX-1][actualY]==51 && abs(ve<0?50+ve:ve)%50-25>45)||mapix[actualX-1][actualY]==55|| mapix[actualX-1][actualY] ==51  )))))){
        ho -=SPEED;

    } // Incrementation si le perso est dans les cases autorisée
     
}

void downK(SDL_Rect &elfImage, int &who, int &frame, SDL_Rect &tilePosition, int &ho, int &y, int &ve, int &x, int &actualX, int &actualY, int & i, int &j,int **mapix, SDL_Rect & elfPos){
getPos(tilePosition, ho, ve, y, x, actualX, actualY, i, j,mapix,0,10,elfPos);
int in_tab = actualX >= 0 && actualY >=0 && actualX+1 < i && actualY < j;
       
 
  if(in_tab &&((mapix[actualX+1][actualY+1]!=100 || ( (mapix[actualX+1][actualY+1]==100 )&&((ho<0?50000+ho:ho)%50<30||( ((abs(ve<0?50000+ve:ve)%50>10))&&(abs(ve<0?50000+ve:ve)%50<=35))) ))&&(mapix[actualX+1][actualY] == 49 ||mapix[actualX+1][actualY]==51||mapix[actualX+1][actualY]==51||((ho<0?50000+ho:ho)%50<26&&mapix[actualX+1][actualY] == 52))/*||mapix[actualX+1][actualY]==99 && abs(ve<0?50000+ve:ve)%50>=35*/)){
        ho+=SPEED; //Si le joueur est sur une case autorisée on incremente


    }
        
    elfImage.x = 32 * frame + 4*32; //Mise a jour du sprite 
}
