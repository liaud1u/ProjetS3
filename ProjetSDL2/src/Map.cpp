#include "Map.h"
#include "TextureManager.h"

#include <iostream>
#include <fstream>

using namespace std;

Map::Map(const char *NomFichierMap)
{
    //Charge toutes les texture pour la creation de la map
    sol = TextureManager::ChargerTexture("assets/floor_1.png");//0
    murBas = TextureManager::ChargerTexture("assets/wall_mid.png");//1
    murHaut = TextureManager::ChargerTexture("assets/wall_mid.png");//2
    murGauche = TextureManager::ChargerTexture("assets/wall_left.png");//3
    murDroit = TextureManager::ChargerTexture("assets/wall_right.png");//4
    murCoinGauche = TextureManager::ChargerTexture("assets/wall_corner_bottom_left.png");//5
    murCoinDroit = TextureManager::ChargerTexture("assets/wall_corner_bottom_right.png");//6

    ChargerMap(NomFichierMap);

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.h = 32;
    dstRect.w = 32;
}

Map::~Map()
{
    //dtor
}

void Map::ChargerMap(const char *NomFichierMap)//a remplacer par un chargement d'un fichier
{
    ifstream niveauFichier(NomFichierMap, ios::in);//Ouverture du fichier map en lecture

    if(niveauFichier)
    {
        int rangee = 0;

        string ligne;
        string tmp;//String temporaire pour stocker les int extrait des lignes

        while(getline(niveauFichier, ligne))//Tant qu'on lis des ligne dans le fichier
        {
            for(int colonne = 0; colonne < 25; colonne++)
            {
                tmp = ligne.substr(colonne, 1);//Decoupe la ligne caractere par caractere
                niveau[rangee][colonne] = stoi(tmp);//convertis la string en int
            }
            rangee ++;
        }
        niveauFichier.close();//Fermeture du fichier
    }
    else
    {
        cout << "Erreur a l'ouverture du niveau : " << NomFichierMap << endl;
    }
}

void Map::DessinerMap()
{
    int type = 0;

    for(int rangee = 0; rangee < 20; rangee++)//Boucle pour les rangees
    {
        for(int colone = 0; colone < 25; colone++)//Boucle pour les colones
        {
            type = niveau[rangee][colone];

            dstRect.x = colone * 32;//Multiplie par 32 car 1 case est de taille 32x32
            dstRect.y = rangee * 32;//Multiplie par 32 car 1 case est de taille 32x32

            switch(type)
            {
                case 0:
                    TextureManager::Dessiner(sol, srcRect, dstRect);
                    break;
                case 1:
                    TextureManager::Dessiner(murBas, srcRect, dstRect);
                    break;
                case 2:
                    TextureManager::Dessiner(murHaut, srcRect, dstRect);
                    break;
                case 3:
                    TextureManager::Dessiner(murGauche, srcRect, dstRect);
                    break;
                case 4:
                    TextureManager::Dessiner(murDroit, srcRect, dstRect);
                    break;
                case 5:
                    TextureManager::Dessiner(murCoinGauche, srcRect, dstRect);
                    break;
                case 6:
                    TextureManager::Dessiner(murCoinDroit, srcRect, dstRect);
                    break;
                default:
                    break;
            }
        }
    }
}

bool Map::collisionMap(int depla, GameObject joueur){ //Fonction gérant les collisions entre le personnage et la map
	bool collision = false; //Booleen retourné à la fin (true si collision, false sinon)
	int valX = joueur.getX()/32;
	int valY = joueur.getY()/32;
	switch(depla){ //Cet entier représente le déplacement du personnage, ce qui peut aussi représenter la touche que le joueur presse
		case 0: //Gauche
			cout << "Je suis dans le test collision gauche du mur, xPos : " << valX << " yPos : " << valY << "\nTruc à gauche : " << niveau[valX-1][valY] << endl;
			if (niveau[valX - 1][valY] == 3 || niveau[valX - 1][valY] == 5 || niveau[valX - 1][valY] == 4 || niveau[valX - 1][valY] == 1){ //Test des cases ne permettant pas le déplacement
				collision = true;
				cout << "Le booléen passe à true dans collisionMap" << endl;
			}
			break;
		case 1: //Haut
			cout << "Je suis dans le test collision vers le haut pour les murs" << endl;
			if (niveau[valX][valY - 1] == 3){
				collision = true;
			}
			break;
	}
	return collision;
}
