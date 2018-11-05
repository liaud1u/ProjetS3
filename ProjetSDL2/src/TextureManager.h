#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "GameManager.h"

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        static SDL_Texture *ChargerTexture(const char *NomFichier);
        static void Dessiner(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect);

    private:
};

#endif // TEXTUREMANAGER_H
