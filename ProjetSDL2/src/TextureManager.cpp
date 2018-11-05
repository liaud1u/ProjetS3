#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

SDL_Texture *TextureManager::ChargerTexture(const char *NomFichier)
{
		SDL_Surface *tempSurface = IMG_Load(NomFichier);//On créer une surface temporaire avec l'image passée en paramètre
		if(tempSurface)//Si la surface n'a pas bien été crée
		{
            cout << "Surface temporaire cree" << endl;
            SDL_Texture *texture = SDL_CreateTextureFromSurface(GameManager::renderer, tempSurface);//On applique la surface temporaire a notre texture
            if(!texture)//Si la texture n'est pas crée
            {
                SDL_Log("Impossible de creer la texture : %s", SDL_GetError());
                exit(EXIT_FAILURE);
            }
            cout << "Texture crée : " << NomFichier << endl;
            SDL_FreeSurface(tempSurface);//On libère notre surface
            cout << "Surface temporaire liberée" << endl;
            return texture;
        }
        else
        {
            SDL_Log("Impossible de charger l'image: %s\n", IMG_GetError());
            exit(EXIT_FAILURE);
        }
}

void TextureManager::Dessiner(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect)
{
    SDL_RenderCopy(GameManager::renderer, texture, &srcRect, &dstRect);
}
