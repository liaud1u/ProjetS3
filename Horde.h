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
  Horde(char const * adresse);
  
  //Liste des fonctions
  void move(int **mapix, int i, int j, int y, int x,int ho , int ve,int &vie,SDL_Surface *screen); //Mouvement de la horde
  void afficher(int frame,SDL_Surface *screen, int vertical, int horizontal) const; //toString()
  int getNb() const; // nombre d'ennemi dans la horde
  Ennemi * getTab();
  void load(char const * adresse);
  int getNbAlive() const;
  int collide(SDL_Rect &perso, int dir);
  
private:
  //Attributs
  Ennemi horde[30];
  int nb;
};

