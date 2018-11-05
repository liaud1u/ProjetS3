#include "GameManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

using namespace std;

GameObject *joueur;
GameObject *echelle;

Map *niveau;

SDL_Renderer *GameManager::renderer = nullptr;
SDL_Event GameManager::event;

list<GameObject> listeGameObject;

GameManager::GameManager()
{
	// cotr

}

GameManager::~GameManager()
{
	//dtor
}

void GameManager::InitGM(const char* titre, int xpos, int ypos, int width, int height, bool pleinecran)//Fonction qui initialiser SDL, crer une fenetre et un 1er rendu
{
    this->width = width;
    this->height = height;

    int flag = 0;//Flag pour définir le plein ecran ou non

    if(pleinecran)
    {
        flag = SDL_WINDOW_FULLSCREEN;//On passe le flag sur plein ecran
    }

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0)//Si l'initialisation reussi
	{
		cout << "SDL Intialiser" << endl;

		window = SDL_CreateWindow(titre, xpos, ypos, width, height, flag);//Création de la fenetre
		if(window)//Si la fenetre est creer
		{
            cout << "Fenetre creer" << endl;
		}
		else
		{
            SDL_Log("Impossible de creer la fenetre: %s", SDL_GetError());
            isRunning = false;//Le programme ne tourne pas
            exit(EXIT_FAILURE);
		}

        renderer = SDL_CreateRenderer(window, -1, 0);//Création du rendu
        if(renderer)//Si le rendu est creer
        {
            cout << "Rendu creer" << endl;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//Définie la couleur du rendu
        }
        else
        {
            SDL_Log("Impossible de creer le rendu: %s", SDL_GetError());
            isRunning = false;//Le programme ne tourne pas
            exit(EXIT_FAILURE);
        }

		isRunning = true;//On met le bool sur true car le jeu tourne

        CreerGameObject(joueur, "assets/player.png" ,50 ,50, 6);//Creer le joueur avec la texture player.png aux positions x:50 et y:50
        CreerGameObject(echelle, "assets/floor_ladder.png", 115, 155, 0);

        niveau = new Map("maps/niveau1.map");//Charge le niveau
	}
	else
	{
        SDL_Log("Impossible d'initialiser SDL: %s", SDL_GetError());
        isRunning = false;//Le programme ne tourne pas
        exit(EXIT_FAILURE);//On quitte le programme
	}
}

void GameManager::HandleEvents()//Fonction qui permet de faire une action lorsqu'il y a un certain evenement
{
    SDL_PollEvent(&event);

    if(event.type == SDL_KEYDOWN)//Quand on presse une touche
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE://Quand on ferme la fenetre avec escape on genere un evenement SDL_Quit
                isRunning = false;//On passe isRunning a false car on ferme le programme
                break;
            case SDLK_UP://Quand on appuie sur la fleche du haut
                if(CheckCollision(listeGameObject.begin()))
                {
                    cout << "Collision en haut" << endl;
                }
                listeGameObject.begin()->setVelocityGO(0);
                break;
            case SDLK_DOWN://Quand on appuie sur la fleche du bas
                if(CheckCollision(listeGameObject.begin()))
                {
                    cout << "Collision en bas" << endl;
                }
                listeGameObject.begin()->setVelocityGO(1);
                break;
            case SDLK_LEFT://Quand on appuie sur la fleche de gauche
                if(CheckCollision(listeGameObject.begin()))
                {
                    cout << "Collision a gauche" << endl;
                }
                listeGameObject.begin()->setVelocityGO(2);
                break;
            case SDLK_RIGHT://Quand on appuie sur la fleche de droite
                if(CheckCollision(listeGameObject.begin()))
                {
                    cout << "Collision a droite" << endl;
                }
                listeGameObject.begin()->setVelocityGO(3);
                break;
            default:
                break;
        }
    }
    else if(event.type == SDL_KEYUP)//Quand on relache une touche
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP://Quand on relache la fleche du haut
                listeGameObject.begin()->setVelocityGO(4);
                break;
            case SDLK_DOWN://Quand on relache la fleche du bas
                listeGameObject.begin()->setVelocityGO(5);
                break;
            case SDLK_LEFT://Quand on relache la fleche de gauche
                listeGameObject.begin()->setVelocityGO(6);
                break;
            case SDLK_RIGHT://Quand on relache la fleche de droite
                listeGameObject.begin()->setVelocityGO(7);
                break;
            default:
                break;
        }
    }

    switch(event.type)
    {
        case SDL_QUIT://Quand on ferme la fenetre avec la croix on genere un evenement SDL_Quit
            isRunning = false;//On passe isRunning a false car on ferme le programme
            break;
        default:
            break;
    }
}

void GameManager::UpdateGM()
{
    for(auto gameObject = listeGameObject.rbegin(); gameObject != listeGameObject.rend(); gameObject++)//Parcours la liste pour mettre a jour les GameObjects instancie
    {
        gameObject->UpdateGO();//Mise a jour du gameobject
    }
}

void GameManager::RendererGM()//Fonction qui permet de créer un nouveau rendu
{
    if(renderer)
    {
        SDL_RenderClear(renderer);//On nettoye le rendu en premier

        niveau->DessinerMap();//On dessine la map

        for(auto gameObject = listeGameObject.rbegin(); gameObject != listeGameObject.rend(); gameObject++)//Parcours la liste pour rendre les GameObjects instancie
        {
            gameObject->RendererGO();//Rendu du gameobject
        }

        SDL_RenderPresent(renderer);//On affiche le rendu
    }
    else
    {
        cout << "Erreur ! Pas de rendu creer" << endl;
    }
}

void GameManager::CleanGM()//Fonction qui permet de detruire la fenetre, le rendu, et l'instance SDL
{
    if(window && renderer)//Si il y a une fenetre et un rendu
    {
        listeGameObject.clear();//Supprime la liste
        cout << "Liste vide" << endl;
        SDL_DestroyRenderer(renderer);
        cout << "Rendu detruit" << endl;
        SDL_DestroyWindow(window);
        cout << "Fenetre detruite" << endl;
        SDL_Quit();
        cout << "Instance SDL detruite" << endl;
        cout << "Fin du programme" << endl;
    }
    else
    {
        cout << "Erreur ! Pas de fenetre ou pas de rendu creer" << endl;
    }
}

void GameManager::CreerGameObject(GameObject *gameObject, const char *NomTexture, int xPos, int yPos, int life)
{
    gameObject = new GameObject(NomTexture, xPos, yPos, life);//Creer une echelle comme point de sortie

    if(gameObject)
    {
        cout << gameObject << " creer" << endl;
        listeGameObject.push_back(*gameObject);
    }
    else
    {
        isRunning = false;
        exit(EXIT_FAILURE);
    }
}

bool GameManager::Running()//Fonction qui permet de savoir si le jeu est en cour d'execution ou non
{
	return isRunning;
}

bool GameManager::CheckCollision(auto iterateur)
{
        for(auto gameObjectDst = listeGameObject.begin(); gameObjectDst != listeGameObject.end(); gameObjectDst++)//Parcours la liste pour check les collisions
        {
            if(gameObjectDst != iterateur)//On ne veux peut pas test la collision avec le joueur lui meme
            {
                if(iterateur->Collision(*gameObjectDst))//Test de la collision
                {
                    return true;
                }
            }
        }
        return false;
}
