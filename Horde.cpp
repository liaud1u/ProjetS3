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

Horde::Horde(char * adresse){
   FILE* ennemi_file;
   ennemi_file = fopen(adresse,"r"); //Chargement du fichier en lecture seulement
}

void Horde::moove(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie){
    for (int n = 0; n < nb; n++){

    }
}

void Horde::afficher() const{
}

void Horde::getNb() const{
}


