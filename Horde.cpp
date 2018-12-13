#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Define.h"
#include "Ennemi.h"
#include "Fonction.h"
#include "Horde.h"

using namespace std;

/*CONSTRUCOR*/
Horde::Horde(){
    nb = 0;
}

/*METHOD*/
Horde::Horde(char const * adresse){
    FILE* ennemi_file;
    int x,y,vie,cat,size;
    ennemi_file = fopen(adresse,"r"); //Load file
    fscanf(ennemi_file,"%d",&nb);
    for(int n = 0; n < nb; n++){ //Get constructor argument in the file
        
        fscanf(ennemi_file,"%d",&x);
        fscanf(ennemi_file,"%d",&y);
        fscanf(ennemi_file,"%d",&vie);
        fscanf(ennemi_file,"%d",&cat);
        fscanf(ennemi_file,"%d",&size);
        
        horde[n] = Ennemi(n,x,  y,  vie,  cat, size);
    }
}

void Horde::move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie,SDL_Surface *screen){
      for(int k = 0; k < nb; k++){
        if(!horde[k].isDead())
          horde[k].move(mapix,i,j,y,x,ho,ve,vie,screen);
      }
}

void Horde::load(char const * adresse){
    FILE* ennemi_file;
    int x,y,vie,cat,size;
    ennemi_file = fopen(adresse,"r"); //Load file
    fscanf(ennemi_file,"%d",&nb);
    for(int n = 0; n < nb; n++){//Get constructor argument in the file
        
        fscanf(ennemi_file,"%d",&x);
        fscanf(ennemi_file,"%d",&y);
        fscanf(ennemi_file,"%d",&vie);
        fscanf(ennemi_file,"%d",&cat);
        fscanf(ennemi_file,"%d",&size);
	
        
        horde[n] = Ennemi(n,x,  y,  vie,  cat, size);
    }
}

void Horde::afficher(int frame,SDL_Surface *screen, int vertical, int horizontal) const{
    
    SDL_Rect zombiePos,zombieImage;
    SDL_Surface *temp,*zombie;
    
    temp = SDL_LoadBMP("ressources/zombie.bmp");
    zombie= SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    int colorkey; // Colorkey for transparancy
    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    
    SDL_SetColorKey(zombie, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    
    /*DEFINE THE SORUCE RECTANGLE FOR ENNEMY*/
    zombieImage.y = 0 ;
    zombieImage.w = MONSTER_SIZE;
    zombieImage.h = 40;
    zombieImage.x = MONSTER_SIZE*frame;
    
    /*PRINT ALL ENNEMY*/
    for (int z = 0; z<nb; z++){
        if(!horde[z].isDead()){
            zombiePos = horde[z].getPositionPrint(horizontal,vertical);
	    zombieImage.y = horde[z].getDir() * 40  + 40 * horde[z].getSize();
            zombieImage.x = horde[z].getCat() * MONSTER_SIZE * 4 + MONSTER_SIZE * frame;
            SDL_BlitSurface(zombie, &zombieImage, screen, &zombiePos);
        }
    }
   
    SDL_FreeSurface(zombie);
}

int Horde::getNb() const{
    return nb;
}

int Horde::getNbAlive() const{
    int n = 0;
    for (int z = 0; z<nb; z++){
        if(!horde[z].isDead()){
            n++;
        }
    }
    return n;
}

Ennemi * Horde::getTab(){
    return horde;
}

int Horde::collide(SDL_Rect &perso, int dir,int ve, int ho){
    int res = 0;

    SDL_Rect ennemi;
    switch (dir){ 
        case 0:
            for (int z = 0; z<nb; z++){
                ennemi = horde[z].getPositionPrint(ho,ve);
                if(!horde[z].isDead() && res != 1){
                    if(!(ennemi.x + ennemi.w +10< perso.x|| perso.y > ennemi.y || perso.y + perso.h < ennemi.y|| ennemi.x  > perso.x + perso.w)){
                        res ++;
                    }
                }
            }
            return res;
            break;
        case 1:
            for (int z = 0; z<nb; z++){
                
                ennemi = horde[z].getPositionPrint(ho,ve);
                if(!horde[z].isDead() && res != 1){
                    if(!(ennemi.y  - 32> perso.y  || ennemi.y - 32+ ennemi.h < perso.y|| ennemi.x + ennemi.w < perso.x || ennemi.x  > perso.x + perso.w)){
                        res ++;
                    }
                }
            }
            return res;
            break;
        case 2:
            for (int z = 0; z<nb; z++){
                
                ennemi = horde[z].getPositionPrint(ho,ve);
                if(!horde[z].isDead() && res != 1){
                    
                    if(!(ennemi.y < perso.y  || ennemi.y  > perso.y + perso.h + 10|| ennemi.x + ennemi.w < perso.x || ennemi.x  > perso.x + perso.w)){
                        res ++;
                    }
                }
            }
            return res;
            break;
        case 3:
            for (int z = 0; z<nb; z++){
                ennemi = horde[z].getPositionPrint(ho,ve);
                if(!horde[z].isDead() && res != 1){
                    if(!(ennemi.x + ennemi.w < perso.x|| perso.y > ennemi.y || perso.y + perso.h < ennemi.y|| ennemi.x  -10> perso.x + perso.w)){
                        res ++;
                    }
                }
            }
            return res;
            break;
        default:
            return 1;
            break;
    }
}

/*NO NEED OF DESTRUCTOR ( NO MALLOC ) */
