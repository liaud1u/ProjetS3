#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Ennemi.h"
#include "Fonction.h"
#include "Horde.h"

#define MONSTER_SIZE 32 

using namespace std;

Horde::Horde()
{
  
}

Horde::Horde(char const * adresse){
  FILE* ennemi_file;
  int x,y,vie,cat,size;
  ennemi_file = fopen(adresse,"r"); //Chargement du fichier en lecture seulement
  fscanf(ennemi_file,"%d",&nb);
  for(int n = 0; n < nb; n++){
    
    fscanf(ennemi_file,"%d",&x);
    fscanf(ennemi_file,"%d",&y);
    fscanf(ennemi_file,"%d",&vie);
    fscanf(ennemi_file,"%d",&cat);
    fscanf(ennemi_file,"%d",&size);
    
    horde[n] = Ennemi(n,x,  y,  vie,  cat, size);
  }
}

void Horde::move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie){
        for(int k = 0; k < nb; k++){
	if(!horde[k].isDead() && SDL_GetTicks()%4==0)
	  
	  horde[k].move(mapix,i,j,y,x,ho,ve,vie);
      }
}

void Horde::load(char const * adresse){
  FILE* ennemi_file;
  int x,y,vie,cat,size;
  ennemi_file = fopen(adresse,"r"); //Chargement du fichier en lecture seulement
  fscanf(ennemi_file,"%d",&nb);
  for(int n = 0; n < nb; n++){
    
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
  
  int colorkey; // Couleur pour transparence des bmp 
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  
  SDL_SetColorKey(zombie, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  
  /* Define the source rectangle (elf)for the BlitSurface */
  zombieImage.y = 0 ;
  zombieImage.w = MONSTER_SIZE;
  zombieImage.h = 40;
  zombieImage.x = MONSTER_SIZE*frame;
  
  //Affichage des monstres ( ici seulement zombie ) 
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

