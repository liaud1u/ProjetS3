#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameManager.h"

class GameObject
{
    public:
        GameObject(const char *nomTexture, int posX, int posY, int life);
        virtual ~GameObject();

        void UpdateGO();
        void RendererGO();
        void setVelocityGO(int direction);

        bool Collision(GameObject secondGO);

        int getX();
        int getY();

    private:
        int xPos;
        int yPos;
        int xVel;
        int yVel;
        int life;

        const int vitesse = 5;

        bool coll;

        SDL_Texture *textureObjet;
        SDL_Rect srcRect, dstRect;
};

#endif // GAMEOBJECT_H
