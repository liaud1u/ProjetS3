#include "Shop.h"
#include "stats.h"


using namespace std;

Shop::Shop(SDL_Surface *screen){

	prixDegats = 5;
	prixPotion = 3;

	menu = load("ressources/shop.bmp");
	back = load("ressources/screen.bmp");

	TTF_Init(); //Init ttf

	police = TTF_OpenFont("ressources/Dungeons.ttf",55); //Police + taille

	SDL_Color couleurTexte = {255,255,255}; //Couleur blanche pour le texte
	char degatsCarac[50];
	sprintf(degatsCarac,"x%d",prixDegats);
	char potionCarac[50];
	sprintf(potionCarac,"x%d",prixPotion);
	texteDegats = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	textePotion = TTF_RenderText_Blended(police,potionCarac,couleurTexte);
    
    TTF_Quit();
	

}

void Shop::miseAJourPrix(SDL_Surface *screen, int frame, int money_current){

	TTF_Init(); //Init ttf

	SDL_Color couleurTexte = {0,0,0}; //Couleur noire pour le texte
	char degatsCarac[50];
	sprintf(degatsCarac,"x%d",prixDegats);
	char potionCarac[50];
	sprintf(potionCarac,"x%d",prixPotion);
	texteDegats = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	textePotion = TTF_RenderText_Blended(police,potionCarac,couleurTexte);

	//Position du texte
	posTexteDegats.x = 280;
	posTexteDegats.y = 165;

	posTextePotion.x = 280;
	posTextePotion.y = 345;

	//Position du menu
	posMenu.x = 300;
	posMenu.y = 70;

	//Ajout du menu à la fenêtre
    SDL_BlitSurface(back,NULL,screen,NULL    );
	SDL_BlitSurface(menu,NULL,screen,&posMenu);
	SDL_BlitSurface(texteDegats,NULL,menu,&posTexteDegats);
	SDL_BlitSurface(textePotion,NULL,menu,&posTextePotion);
    affichePiece(money_current,screen,frame);
	SDL_UpdateRect(screen,0,0,0,0);
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
			this->miseAJourPrix(screen,money,frame);
		}
	}
	tabVieEtDegats[0] = life;
	tabVieEtDegats[1] = attaque;
	tabVieEtDegats[2] = money;
	return tabVieEtDegats;


}

Shop::~Shop()
{
    SDL_FreeSurface(menu);
    SDL_FreeSurface(texteDegats);
    SDL_FreeSurface(textePotion);
    SDL_FreeSurface(back);
}
