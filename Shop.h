#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Shop {

public:
	Shop(SDL_Surface *screen); //Constructeur du menu d'achat

	void miseAJourPrix(SDL_Surface *screen, int frame,int money_current);
	int* gererAchats(int money, int life, int attaque, int posSourisX, int posSourisY,SDL_Surface *screen, int frame);
private://Attributs de la classe Shop

	int degat_price,potion_price;

};
