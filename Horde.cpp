#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Ennemi.h"
#include "Fonction.h"
#include "Horde.h"

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
      horde[n].afficher();
  }
}

void Horde::moove(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie){
    for (int n = 0; n < nb; n++){
      
    }
}

void Horde::afficher() const{
}

int Horde::getNb() const{
  return nb;
}


