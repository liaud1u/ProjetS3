#ifndef MAP_H
#define MAP_H

#include "GameManager.h"
#include "GameObject.h"


class Map
{
    public:
        Map(const char *NomFichierMap);
        virtual ~Map();

        void ChargerMap(const char *nomFichierMap);
        void DessinerMap();
        bool collisionMap(int depla, GameObject joueur);

    private:
        SDL_Rect srcRect, dstRect;

        SDL_Texture *sol;
        SDL_Texture *murBas;
        SDL_Texture *murHaut;
        SDL_Texture *murGauche;
        SDL_Texture *murDroit;
        SDL_Texture *murCoinGauche;
        SDL_Texture *murCoinDroit;

        FILE *niveauFichier;

        int niveau[20][25];
};

#endif // MAP_H
