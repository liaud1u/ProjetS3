#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>

class GameObject;

class GameManager
{
    public:
        GameManager();
        ~GameManager();

        void InitGM(const char* titre, int xpos, int ypos, int width, int height, bool pleinecran);
        void HandleEvents();
        void UpdateGM();
        void RendererGM();
        void CleanGM();
        void CreerGameObject(GameObject *gameObject, const char *NomTexture, int xPos, int yPos, int life);

        bool Running();
        bool CheckCollision(auto iterateur);

        static SDL_Renderer *renderer;
        static SDL_Event event;

        int height, width;

    private:
        int count = 0;

        bool isRunning;

        SDL_Window *window;
};

#endif /* GAMEMANAGER_H_ */
