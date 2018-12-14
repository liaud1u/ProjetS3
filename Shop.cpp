#include "Define.h"
#include "Shop.h"
#include "stats.h"
#include "Fonction.h"

using namespace std;

/*CONSTRUCTOR*/
Shop::Shop(SDL_Surface *screen){
	degat_price = 5; //Setting up the price of the damage upgrade and the potion price.
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
	pos_degat_text.y = POSITION_SHOP_TEXTE_DEGAT_Y ;

	pos_potion_text.x = LARGEUR/2- potion_text->w/2;
	pos_potion_text.y = POSITION_SHOP_TEXTE_POTION_Y;

	//Set menu position
	pos_Menu.x = POSITION_SHOP_X;
	pos_Menu.y = POSITION_SHOP_Y;

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
	int *return_tab = new int[4];
	return_tab[3] = 1; 
	posSourisX -= POSITION_SHOP_X;
	posSourisY -= POSITION_SHOP_Y; //Synchronise shop and mouse pos
	if (posSourisX >= DEBUT_BOUTON_POTION_X && posSourisX <= FIN_BOUTON_POTION_X && posSourisY >= DEBUT_BOUTON_POTION_Y && posSourisY <= FIN_BOUTON_POTION_Y){
		if (money >= potion_price){ //if it's possible, buy the item
			money -= potion_price; //we pay=
			life += 5;
			return_tab[3] = 0; //to leave shop
			if (life > MAX_LIFE){ //check life
				life = MAX_LIFE;
			}
		}
	}

	if (posSourisX >= DEBUT_BOUTON_DEGAT_X && posSourisX <= FIN_BOUTON_DEGAT_X && posSourisY >= DEBUT_BOUTON_DEGAT_Y && posSourisY <= FIN_BOUTON_DEGAT_Y){
		if (money >= degat_price){ //if it's possible, buy the item
			money -= degat_price; //we pay
			return_tab[3] = 0; //to leave shop
			attack *= 1.2;
			degat_price += 3;
		}
	}
	return_tab[0] = life; //Adding all the modified things in a tab, to return it, and, edit the money, life, damage value of the playable character
	return_tab[1] = attack;
	return_tab[2] = money;
	return return_tab;
}

/*NO NEED OF DESTRUCTOR ( NO MALLOC ) */
