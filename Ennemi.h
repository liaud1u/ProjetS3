#ifndef DEF_ENNEMI
#define DEF_ENNEMI
#include <stdio.h>

class Ennemi
{
    public:
        //Constructeurs
        Ennemi();
        Ennemi(int x, int y, int vie, int cat, int size);
        //Liste des fonctions
        SDL_Rect getPosition() const;
        void afficher() const;
    
    private:
        //Attributs
        int e_x;
        int e_y;
        int e_vie;
        int e_cat;
        int e_size;
        int e_ve;
        int e_ho;
};

#endif
