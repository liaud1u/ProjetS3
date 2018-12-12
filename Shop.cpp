#include "Shop.h"
#include "stats.h"
#include "Fonction.h"

#define HAUTEUR 750
#define LARGEUR 1200

using namespace std;

Shop::Shop(SDL_Surface *screen){

	prixDegats = 5;
	prixPotion = 3;



}

void Shop::miseAJourPrix(SDL_Surface *screen, int frame, int money_current){
	TTF_Init(); //Init ttf
    
	SDL_Rect posMenu,posTexteDegats,posTextePotion;
    	SDL_Surface *menu,*texteDegats,*textePotion, *back;
        
	TTF_Font *police;

    back = load("ressources/screen.bmp");
    menu = load("ressources/shop.bmp");
    
	SDL_Color couleurTexte = {0,0,0}; //Couleur noire pour le texte
	char degatsCarac[50];
	sprintf(degatsCarac,"x%d Pieces",prixDegats);
	char potionCarac[50];
	sprintf(potionCarac,"x%d Pieces",prixPotion);
	police = TTF_OpenFont("ressources/Dungeons.ttf",55); //Police + taille

TTF_SetFontStyle(police, TTF_STYLE_BOLD);

	texteDegats = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	textePotion = TTF_RenderText_Blended(police,potionCarac,couleurTexte);

	//Position du texte
	posTexteDegats.x = LARGEUR/2 - texteDegats->w/2;
	posTexteDegats.y = 235 ;

	posTextePotion.x = LARGEUR/2- textePotion->w/2;
	posTextePotion.y = 415;

	//Position du menu
	posMenu.x = 300;
	posMenu.y = 70;

	//Ajout du menu à la fenêtre
    SDL_BlitSurface(back,NULL,screen,NULL    );
	SDL_BlitSurface(menu,NULL,screen,&posMenu);
	SDL_BlitSurface(texteDegats,NULL,screen,&posTexteDegats);
	SDL_BlitSurface(textePotion,NULL,screen,&posTextePotion);
	SDL_UpdateRect(screen,0,0,0,0);
    SDL_FreeSurface(textePotion);
    SDL_FreeSurface(texteDegats);
        SDL_FreeSurface(menu);
    SDL_FreeSurface(back);
    TTF_CloseFont(police);
    TTF_Quit();
}

int* Shop::gererAchats(int money, int life, int attaque, int posSourisX, int posSourisY, SDL_Surface *screen,int frame){
	//x = 140 / 440 , y = 330 / 390 --> potion
	// x = 140 / 440 , y = 150 / 210 --> arme
	int *tabVieEtDegats = new int[4];
	tabVieEtDegats[3] = 1; 
	posSourisX -= 300;
	posSourisY -= 70; //Pour que le X et le Y correspondent à ceux de la boutique
	if (posSourisX >= 140 && posSourisX <= 440 && posSourisY >= 330 && posSourisY <= 390){
		if (money >= prixPotion){ //SI on a l'argent, on achète
			money -= prixPotion; //On paye
			life += 5;
			tabVieEtDegats[3] = 0; //Pour quitter le shop, on retourne un booleen.
			if (life > 10){ //Pour éviter de trop se heal
				life = 10;
			}
		}
	}

	if (posSourisX >= 140 && posSourisX <= 440 && posSourisY >= 150 && posSourisY <= 210){
		if (money >= prixDegats){ //SI on a l'argent, on achète
		  
			money -= prixDegats; //On paye
			
			tabVieEtDegats[3] = 0; //Pour quitter le shop, on retourne un booleen.
			
			attaque *= 1.2;
			
			prixDegats += 3;
			
		}
	}
	tabVieEtDegats[0] = life;
	tabVieEtDegats[1] = attaque;
	tabVieEtDegats[2] = money;
	return tabVieEtDegats;


}

