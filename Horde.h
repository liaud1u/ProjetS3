#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <ctime>
#include "Fonction.h"

class Horde
{
public:
  //Constructeurs
  Horde();
  Horde(char * adresse);
  
  //Liste des fonctions
  void moove(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie); //Mouvement de la horde
  void afficher() const; //toString()
  void getNb() const; // nombre d'ennemi dans la horde
  
private:
  //Attributs
  Ennemi * horde;
  int nb;
};

