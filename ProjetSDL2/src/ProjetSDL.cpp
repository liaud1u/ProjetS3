//============================================================================
// Name        : ProjetSDL.cpp
// Author      : theo
// Version     : 0.1
// Copyright   : Copyright theo
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SDL2/SDL.h>
#include "GameManager.h"

using namespace std;

GameManager *gameManager = nullptr;//Instancie un GameManager avec un pointeur null

int main()
{
    const int FPS = 60;//Constante pour fix les FPS a 60
    const int frameDelay = 1000 / FPS;//Constante qui definie le delay entre 2 frames

    Uint32 FrameStart;
    int frameTime;

	gameManager = new GameManager();//Instancie un nouveau GameManager

	gameManager->InitGM("Projet SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);//Initialisation de SDL, création de la fenetre et du 1er rendu

	while(gameManager->Running())//Tant que le jeu tourne
	{
        FrameStart = SDL_GetTicks();//Donne en millisecondes le temps ecoule depuis l'initialisation de SDL

        gameManager->HandleEvents();//On recupère tous les event
        gameManager->UpdateGM();//On met à jour nos gameobjects
        gameManager->RendererGM();//On creer le rendu de tous nos gameobjects à jour

        frameTime = SDL_GetTicks() - FrameStart;//Donne le temps ecoulé depuis la dernière frame

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);//On fait un delay si le delay entre 2 frames est plus grand que le temps depuis la derniere frame
        }
	}

	gameManager->CleanGM();//On détruit les fenetre, rendu, et l'instance SDL

	return EXIT_SUCCESS;
}
