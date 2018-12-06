#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Shop {

public:
	Shop(SDL_Surface *screen); //Constructeur du menu d'achat

	void miseAJourPrix(SDL_Surface *screen);
	void gererAchats(int money, int life, int attaque, int posSourisX, int posSourisY,SDL_Surface *screen);
	void quitterMenu();

private://Attributs de la classe Shop
	SDL_Surface *menu,*texteDegats,*textePotion,*temp;
	SDL_Rect posMenu,posTexteDegats,posTextePotion;
	TTF_Font *police;
	int prixDegats,prixPotion;

};