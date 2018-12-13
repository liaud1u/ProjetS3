#include "Shop.h"
#include "stats.h"
#include "Fonction.h"

#define HAUTEUR 750
#define LARGEUR 1200

using namespace std;

/*CONSTRUCTOR*/
Shop::Shop(SDL_Surface *screen){
	degat_price = 5;
	potion_price = 3;
}

/*METHOD */
void Shop::miseAJourPrix(SDL_Surface *screen, int frame, int money_current){
	TTF_Init(); //Init ttf
	SDL_Rect pos_Menu,pos_degat_text,pos_potion_text;
    	SDL_Surface *menu,*degat_text,*potion_text, *back;
        
	TTF_Font *police;

    back = load("ressources/screen.bmp");
    menu = load("ressources/shop.bmp");
    
	SDL_Color couleurTexte = {0,0,0}; //Black color for font
	char degatsCarac[50];
	sprintf(degatsCarac,"x%d Pieces",degat_price);
	char potionCarac[50];
	sprintf(potionCarac,"x%d Pieces",potion_price);
	police = TTF_OpenFont("ressources/Dungeons.ttf",55); //Set font size

TTF_SetFontStyle(police, TTF_STYLE_BOLD);

	degat_text = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	potion_text = TTF_RenderText_Blended(police,potionCarac,couleurTexte);

	//Set text position
	pos_degat_text.x = LARGEUR/2 - degat_text->w/2;
	pos_degat_text.y = 235 ;

	pos_potion_text.x = LARGEUR/2- potion_text->w/2;
	pos_potion_text.y = 415;

	//Set menu position
	pos_Menu.x = 300;
	pos_Menu.y = 70;

	//Add menu to the windows
    SDL_BlitSurface(back,NULL,screen,NULL    );
	SDL_BlitSurface(menu,NULL,screen,&pos_Menu);
	SDL_BlitSurface(degat_text,NULL,screen,&pos_degat_text);
	SDL_BlitSurface(potion_text,NULL,screen,&pos_potion_text);
	SDL_UpdateRect(screen,0,0,0,0);
    SDL_FreeSurface(potion_text);
    SDL_FreeSurface(degat_text);
        SDL_FreeSurface(menu);
    SDL_FreeSurface(back);
    TTF_CloseFont(police);
    TTF_Quit();
}

int* Shop::gererAchats(int money, int life, int attack, int posSourisX, int posSourisY, SDL_Surface *screen,int frame){
	//x = 140 / 440 , y = 330 / 390 --> potion
	// x = 140 / 440 , y = 150 / 210 --> weapon
	int *return_tab = new int[4];
	return_tab[3] = 1; 
	posSourisX -= 300;
	posSourisY -= 70; //Synchronise shop and mouse pos
	if (posSourisX >= 140 && posSourisX <= 440 && posSourisY >= 330 && posSourisY <= 390){
		if (money >= potion_price){ //if it's possible, buy the item
			money -= potion_price; //we pay
			life += 5;
			return_tab[3] = 0; //to leave shop
			if (life > 10){ //check life
				life = 10;
			}
		}
	}

	if (posSourisX >= 140 && posSourisX <= 440 && posSourisY >= 150 && posSourisY <= 210){
		if (money >= degat_price){ //if it's possible, buy the item
			money -= degat_price; //we pay
			return_tab[3] = 0; //to leave shop
			attack *= 1.2;
			degat_price += 3;
		}
	}
	return_tab[0] = life;
	return_tab[1] = attack;
	return_tab[2] = money;
	return return_tab;
}

/*NO NEED OF DESTRUCTOR ( NO MALLOC ) */
