#include "Shop.h"

using namespace std;

Shop::Shop(SDL_Surface *screen){

	prixDegats = 5;
	prixPotion = 3;

	SDL_Init(SDL_INIT_VIDEO);
	temp = SDL_LoadBMP("ressources/cadre.bmp");
	menu = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	TTF_Init(); //Init ttf

	police = TTF_OpenFont("ressources/Dungeons.ttf",55); //Police + taille

	SDL_Color couleurTexte = {255,255,255}; //Couleur blanche pour le texte
	char degatsCarac[50];
	sprintf(degatsCarac,"Augmenter les Degats : %d",prixDegats);
	char potionCarac[50];
	sprintf(potionCarac,"Se soigner : %d",prixPotion);
	texteDegats = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	textePotion = TTF_RenderText_Blended(police,potionCarac,couleurTexte);

	//Position du texte
	posTexteDegats.x = 60;
	posTexteDegats.y = 60;

	posTextePotion.x = 60;
	posTextePotion.y = 130;

	//Ajout du texte au shop
	SDL_BlitSurface(texteDegats,NULL,menu,&posTexteDegats);
	SDL_BlitSurface(textePotion,NULL,menu,&posTextePotion);

	SDL_FreeSurface(texteDegats);
	SDL_FreeSurface(textePotion);

	//Position du menu
	posMenu.x = 30;
	posMenu.y = 90;

	//Ajout du menu à la fenêtre
	cout << "Je crée le menu" << endl;
	SDL_BlitSurface(menu,NULL,screen,&posMenu);
	SDL_UpdateRect(screen,0,0,0,0);

}

void Shop::miseAJourPrix(SDL_Surface *screen){
	SDL_Init(SDL_INIT_VIDEO);
	temp = SDL_LoadBMP("ressources/cadre.bmp");
	menu = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	TTF_Init(); //Init ttf

	SDL_Color couleurTexte = {255,255,255}; //Couleur blanche pour le texte
	char degatsCarac[50];
	sprintf(degatsCarac,"Augmenter les Degats : %d",prixDegats);
	char potionCarac[50];
	sprintf(potionCarac,"Se soigner : %d",prixPotion);
	texteDegats = TTF_RenderText_Blended(police,degatsCarac,couleurTexte);
	textePotion = TTF_RenderText_Blended(police,potionCarac,couleurTexte);

	//Position du texte
	posTexteDegats.x = 60;
	posTexteDegats.y = 60;

	posTextePotion.x = 60;
	posTextePotion.y = 130;

	//Ajout du texte au shop
	SDL_BlitSurface(texteDegats,NULL,menu,&posTexteDegats);
	SDL_BlitSurface(textePotion,NULL,menu,&posTextePotion);

	SDL_FreeSurface(texteDegats);
	SDL_FreeSurface(textePotion);

	//Position du menu
	posMenu.x = 30;
	posMenu.y = 90;

	//Ajout du menu à la fenêtre
	cout << "Je modifie le menu" << endl;
	SDL_BlitSurface(menu,NULL,screen,&posMenu);
	SDL_UpdateRect(screen,0,0,0,0);
}

void Shop::gererAchats(int money, int life, int attaque, int posSourisX, int posSourisY, SDL_Surface *screen){
	if (posSourisX >= posTextePotion.x && posSourisX <= posTextePotion.x + posTextePotion.h && posSourisY >= posTextePotion.y && posSourisY <= posTextePotion.y + posTextePotion.w){
		if (money >= prixPotion){ //SI on a l'argent, on achète
			money -= prixPotion; //On paye
			life += 5;
			cout << "Vous êtes soigné !" << endl;
			if (life > 10){ //Pour éviter de trop se heal
				life = 10;
			}
		}
	}

	if (posSourisX >= posTexteDegats.x && posSourisX <= posTexteDegats.x + posTexteDegats.h && posSourisY >= posTexteDegats.y && posSourisY <= posTexteDegats.y + posTexteDegats.w){
		if (money >= prixDegats){ //SI on a l'argent, on achète
			money -= prixDegats; //On paye
			attaque *= 1.2;
			prixDegats += 3;
			this->miseAJourPrix(screen);
			cout << "Attaque modifiée !" << endl;
		}
	}


}

void Shop::quitterMenu(){

}

